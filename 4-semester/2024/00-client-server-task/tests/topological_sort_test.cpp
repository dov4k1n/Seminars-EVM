/**
 * @file topological_sort_test.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Тесты для алгоритма TopologicalSort.
 */

#include "test_core.hpp"
#include <topological_sort.hpp>
#include <oriented_graph.hpp>

#include <httplib.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using graph::OrientedGraph;
using graph::TopologicalSort;

static void SimpleTest();
static void AnotherSimpleTest();

void TestTopologicalSort() {
  TestSuite suite("TestTopologicalSort");

  RUN_TEST(suite, SimpleTest);
  RUN_TEST(suite, AnotherSimpleTest);
}

static void SimpleTest() {
  OrientedGraph graph;

  graph.AddVertex(1);

  REQUIRE(graph.HasVertex(1));

  graph.AddVertex(2);

  REQUIRE(graph.HasVertex(2));

  graph.AddEdge(1, 2);

  REQUIRE(graph.HasEdge(1, 2));
}

static void AnotherSimpleTest() {
  OrientedGraph graph;

  graph.AddVertex(1);

  REQUIRE(graph.HasVertex(1));

  graph.AddVertex(2);

  REQUIRE(graph.HasVertex(2));

  graph.AddEdge(1, 2);

  REQUIRE(graph.HasEdge(1, 2));

  graph.RemoveVertex(2);

  REQUIRE(!graph.HasEdge(1, 2));
}

/**
  * @brief Основная функция для теста класса TopologicalSort.
  *
  * @param client Клиент, отправляющий запросы.
  *
  * Функция тестирует алгоритм, отправляя JSON-ы с клиента 
  * и проверяя выходные JSON-ы на корректность.
*/
void TestTopologicalSort(httplib::Client *client) {
  TestSuite suite("TestTopologicalSort");

  RUN_TEST_REMOTE(suite, client, TestTopologicalSortCore);
}

void TestTopologicalSortCore(httplib::Client *client) {
  std::map<std::string, std::pair<nlohmann::json, nlohmann::json>> cases;
  std::vector<std::pair<size_t, size_t>> empty_list;

  /**
   * @brief Тест для сортировки пустого графа.
   */
  cases["Empty"] = {
    {
      {"vertices", empty_list},
      {"edges", empty_list}
    },
    {
      {"result", empty_list}
    }
  };

  /**
   * @brief Тест для сортировки линейного графа.
   */
  cases["One line"] = {
    {
      {"vertices", {1, 2, 3, 10}},
      {"edges", {{1, 2}, {2, 3}, {3, 10}}}
    },
    {
      {"result", {{1, 2}, {2, 3}, {3, 10}}}
    }
  };

  /**
   * @brief Тест для сортировки графа без рёбер.
   */
  cases["No edges"] = {
    {
      {"vertices", {1, 2, 3, 4}},
      {"edges", empty_list}
    },
    {
      {"result", empty_list}
    }
  };

  /**
   * @brief Тест для сортировки полного графа.
   */
  cases["All connected"] = {
    {
      {"vertices", {1, 2, 3}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}}}
    },
    {
      {"result", empty_list}
    }
  };

  /**
   * @brief Тест для сортировки графа с тремя компонентами связности.
   */
  cases["Multiple connectivity components"] = {
    {
      {"vertices", {1, 2, 3, 4, 5}},
      {"edges", {{1, 2}, {4, 3}}}
    },
    {
      {"result", {{1, 2}, {3, 4}}}
    }
  };

  /**
   * @brief Чуть сложнее тест сортировки графа с тремя компонентами связности.
   */
  cases["Complex case"] = {
    {
      {"vertices", {1, 2, 3, 4, 5, 6, 7, 8}},
      {"edges", {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 6}, {6, 7}}}
    },
    {
      {"result", empty_list}
    }
  };

  for (const auto &[name, value] : cases) {
    std::cout << name << "... ";

    auto output = client->Post(
      "/TopologicalSort",
      value.first.dump(), 
      "application/json"
    );

    REQUIRE(output->body == value.second.dump());
    REQUIRE_EQUAL(output->body, value.second.dump());

    std::cout << "OK!\n";
  }

  /**
   * @brief Случайные тесты.
   */
  std::cout << "Random test... ";

  int vertices_num = 100;

  int edges_num = 150;

  std::vector<size_t> vertices(vertices_num);

  std::iota(vertices.begin(), vertices.end(), 0);

  std::bernoulli_distribution bern(0.5);

  // Служит для инициализации генератора случайных чисел.
  std::random_device rd;
  // Генератор случайных чисел.
  std::mt19937 generator(rd());
  // Функция распределения случайных целых чисел 
  // от 1 до vertices_num - 1 включительно.
  std::uniform_int_distribution<int> dist(1, vertices_num - 1);

  for (int j = 0; j < 100; ++j) {
    std::vector<
      std::pair<size_t, size_t>
    > edges;

    int threshold = dist(generator);

    std::uniform_int_distribution first_part(0, threshold - 1);
    std::uniform_int_distribution second_part(threshold, vertices_num - 1);

    for (int i = 0; i < edges_num; ++i) {
      size_t vert1;
      size_t vert2;

      if (bern(generator)) {
        vert1 = first_part(generator);
        vert2 = first_part(generator);
      } else {
        vert1 = second_part(generator);
        vert2 = second_part(generator);
      }

      if (vert1 > vert2) {
        std::swap(vert1, vert2);
      }

      edges.push_back({vert1, vert2});
    }

    edges.push_back({threshold - 1, threshold});
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    nlohmann::json random_graph = {
      {"vertices", vertices},
      {"edges", edges}
    };

    auto output = client->Post(
      "/TopologicalSort",
      random_graph.dump(), 
      "application/json"
    );

    std::stringstream ss;
    ss << threshold - 1 << "," << threshold;
    std::string res = ss.str();

    REQUIRE(output->body.find(res) != std::string::npos);
  }
  
  std::cout << "OK!\n";
}