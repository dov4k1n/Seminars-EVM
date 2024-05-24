/**
 * @file topological_sort_test.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация набора тестов для алгоритма топологической сортировки.
 */

#include <vector>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include "topological_sort.hpp"
#include "weighted_oriented_graph.hpp"
#include "test_core.hpp"
#include "test.hpp"

static void SimpleLinearTest(httplib::Client* client);
static void EmptyTest(httplib::Client* client);
static void LinearTest(httplib::Client* client);
static void ReverseLinearTest(httplib::Client* client);
static void CyclicTest(httplib::Client* client);
static void NonLinearTest(httplib::Client* client);
static void RandomTest(httplib::Client* cli);

template <typename Weight>
static void RandomIntegerHelperTest(
  httplib::Client* client, 
  const std::string& weight_type
);

template <typename Weight>
static void RandomFloatingPointHelperTest(
  httplib::Client* client, 
  const std::string& weightType
);

void TestTopologicalSort(httplib::Client* client) {
  TestSuite suite("TestTopologicalSort");

  RUN_TEST_REMOTE(suite, client, SimpleLinearTest);
  RUN_TEST_REMOTE(suite, client, EmptyTest);
  RUN_TEST_REMOTE(suite, client, LinearTest);
  RUN_TEST_REMOTE(suite, client, ReverseLinearTest);
  RUN_TEST_REMOTE(suite, client, CyclicTest);
  RUN_TEST_REMOTE(suite, client, NonLinearTest);
  RUN_TEST_REMOTE(suite, client, RandomTest);
}

/** 
 * @brief Функция, проверяющая топологический порядок.
 *
 * @param order Вектор, в котором записан топологический порядок.
 * @param input Исходный входной JSON, в котором записан граф.
 *
 * В словарь добавляется позиция каждой вершины, затем для каждого ребра 
 * проверяется, что позиция начала не больше позиции конца.
 */
bool isTopologicallySorted(
  const std::vector<size_t>& order,
  const nlohmann::json& input
) {
  std::unordered_map<int, size_t> position;

  for (int i = 0; i < order.size(); ++i) {
    position[order[i]] = i;
  }

  for (auto edge : input.at("edges")) {
    size_t start = edge.at("start");
    size_t end = edge.at("end");

    if (position[start] >= position[end])
      return false;
  }

  return true;
}

/** 
 * @brief Простой статический тест.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void SimpleLinearTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 1,
  "vertices": [ 1, 2, 3 ],
  "edges": [ 
    {
      "start": 2,
      "end":  1,
      "weight": 1
    },
    {
      "start": 1,
      "end": 3,
      "weight": 2
    }
  ],
  "weight_type": "int"
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);

  /* Проверка результатов сортировки. */
  REQUIRE_EQUAL(1, output.at("id"));
  REQUIRE_EQUAL(2, output.at("max_weight"));

  REQUIRE_EQUAL(output.at("order")[0], 2);
  REQUIRE_EQUAL(output.at("order")[1], 1);
  REQUIRE_EQUAL(output.at("order")[2], 3);
}

/**
 * @brief Тест для сортировки пустого графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void EmptyTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 2,
  "vertices": [ ],
  "edges": [ ],
  "weight_type": ""
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);

  REQUIRE_EQUAL(2, output.at("id"));
  REQUIRE_EQUAL("", output.at("max_weight"));
  REQUIRE_EQUAL(std::vector<size_t>(), output.at("order"));
}

/**
 * @brief Тест для сортировки линейного графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void LinearTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 3,
  "vertices": [ 1, 2, 3, 4 ],
  "edges": [ 
    {
      "start": 1,
      "end": 2,
      "weight": 1.1
    },
    {
      "start": 2,
      "end": 3,
      "weight": 1.2
    },
    {
      "start": 3,
      "end": 4,
      "weight": 1.3
    } 
  ],
  "weight_type": "double"
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  REQUIRE_EQUAL(3, output.at("id"));
  REQUIRE_EQUAL(1.3, output.at("max_weight"));

  REQUIRE_EQUAL(output.at("order")[0], 1);
  REQUIRE_EQUAL(output.at("order")[1], 2);
  REQUIRE_EQUAL(output.at("order")[2], 3);
  REQUIRE_EQUAL(output.at("order")[3], 4);
}

/**
 * @brief Тест для сортировки обратного линейного графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void ReverseLinearTest(httplib::Client* client)  {
  nlohmann::json input = R"(
{
  "id": 4,
  "vertices": [ 1, 2, 3, 4 ],
  "edges": [ 
    {
      "start": 4,
      "end": 3,
      "weight": 4.0
    },
    {
      "start": 3,
      "end": 2,
      "weight": 3.0
    },
    {
      "start": 2,
      "end": 1,
      "weight": 2.0
    }
  ],
  "weight_type": "long double"
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);
  REQUIRE_EQUAL(4, output.at("id"));
  REQUIRE_EQUAL(4.0, output.at("max_weight"));

  REQUIRE_EQUAL(output.at("order")[0], 4);
  REQUIRE_EQUAL(output.at("order")[1], 3);
  REQUIRE_EQUAL(output.at("order")[2], 2);
  REQUIRE_EQUAL(output.at("order")[3], 1);
}

/**
 * @brief Тест для сортировки графа с циклом.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void CyclicTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 5,
  "vertices": [ 1, 2, 3 ],
  "edges": [ 
    {
      "start": 1,
      "end": 2,
      "weight": 5.0
    },
    {
      "start": 2,
      "end": 3,
      "weight": 3.0
    }, 
    {
      "start": 3,
      "end": 1,
      "weight": 1.0
    } 
  ],
  "weight_type": "float"
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);

  REQUIRE_EQUAL(5, output.at("id"));
  REQUIRE_EQUAL(int(), output.at("max_weight"));
  REQUIRE_EQUAL(std::vector<size_t>(), output.at("order"));
}

/**
 * @brief Тест для сортировки нелинейного графа.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void NonLinearTest(httplib::Client* client) {
  nlohmann::json input = R"(
{
  "id": 6,
  "vertices": [ 1, 2, 3, 4, 5, 6 ],
  "edges": [ 
    {
      "start": 1,
      "end": 2,
      "weight": 5.0
    },
    {
      "start": 1,
      "end": 3,
      "weight": 3.0
    },
    {
      "start": 2,
      "end": 4,
      "weight": 1.0
    },
    {
      "start": 3,
      "end": 4,
      "weight": 3.0
    },
    {
      "start": 5,
      "end": 6,
      "weight": 11.0
    }
  ],
  "weight_type": "double"
}
)"_json;

  httplib::Result result = client->Post(
    "/TopologicalSort",
    input.dump(),
    "application/json"
  );

  nlohmann::json output = nlohmann::json::parse(result->body);

  REQUIRE_EQUAL(6, output.at("id"));
  REQUIRE_EQUAL(11.0, output.at("max_weight"));
  REQUIRE_EQUAL(true, isTopologicallySorted(output.at("order"), input));
}

/** 
 * @brief Простейший случайный тест.
 *
 * @param cli Указатель на HTTP клиент.
 */
static void RandomTest(httplib::Client* client) {
  RandomIntegerHelperTest<int>(client, "int");

  RandomFloatingPointHelperTest<float>(client, "float");
  RandomFloatingPointHelperTest<double>(client, "double");
  RandomFloatingPointHelperTest<long double>(client, "long double");
}

/** 
 * @brief Простейший случайный тест для целых чисел.
 *
 * @tparam Weight Тип данных для весов.
 *
 * @param client Указатель на HTTP клиент.
 * @param weightType Строковое представление типа данных весов вершин.
 *
 * Функция используется для сокращения кода, необходимого для поддержки
 * различных типов данных.
 * 
 * Рёбра добавляются в топологическом порядке, чтобы не образовались циклы.
 */
template <typename Weight>
static void RandomIntegerHelperTest(
  httplib::Client* client, 
  const std::string& weightType
) {
  const int numTries = 100;
  std::random_device rd;
  std::mt19937 generate(rd());
  std::uniform_int_distribution<size_t> randVerticesNum(1, 40);
  std::uniform_int_distribution<Weight> randWeights(1, 10'000);

  for (int id = 0; id < numTries; id++) {
    size_t numVertices = randVerticesNum(generate);

    size_t maxEdges = numVertices * (numVertices - 1) / 2;
    std::uniform_int_distribution<size_t> randEdgesNum(0, maxEdges);
    size_t numEdges = randEdgesNum(generate);

    std::uniform_int_distribution<size_t> randIndexes(0, numVertices - 1);

    nlohmann::json input;
    input["id"] = id;
    input["weight_type"] = weightType;
    input["number_of_vertices"] = numVertices;
    input["number_of_edges"] = numEdges;
    input["vertices"] = std::vector<size_t>(numVertices);
    input["edges"] = std::vector<nlohmann::json>(numEdges);

    std::vector<size_t> vertices(numVertices);

    for (size_t i = 0; i < numVertices; i++) {
      vertices[i] = i + 1;
    }

    std::shuffle(vertices.begin(), vertices.end(), generate);

    for (size_t i = 0; i < numVertices; i++) {
      input["vertices"][i] = vertices[i];
    }

    Weight maxWeight = std::numeric_limits<Weight>::min();

    std::set<std::pair<size_t, size_t>> edges;

    for (size_t i = 0; i < numEdges; i++) {
      std::uniform_int_distribution<size_t> startDist(0, numVertices - 2);
      size_t start = startDist(generate);

      std::uniform_int_distribution<size_t> endDist(start + 1, numVertices - 1);
      size_t end = endDist(generate);

      while (edges.find({start, end}) != edges.end()) {
        std::uniform_int_distribution<size_t> startDist(0, numVertices - 2);
        start = startDist(generate);

        std::uniform_int_distribution<size_t> endDist(start + 1, numVertices - 1);
        end = endDist(generate);
      }

      edges.insert({start, end});

      Weight weight = randWeights(generate);

      input["edges"][i] = {
        {"start", vertices[start]},
        {"end", vertices[end]},
        {"weight", weight}
      };

      if (weight > maxWeight) maxWeight = weight;
    }

    httplib::Result result = client->Post(
      "/TopologicalSort", 
      input.dump(),
      "application/json"
    );

    nlohmann::json output = nlohmann::json::parse(result->body);

    REQUIRE_EQUAL(id, output.at("id"));
    REQUIRE_EQUAL(weightType, output.at("weight_type"));
    REQUIRE_EQUAL(maxWeight, output.at("max_weight"));
    REQUIRE_EQUAL(true, isTopologicallySorted(output.at("order"), input));
  }
}

/** 
 * @brief Простейший случайный тест для чисел с плавающей точкой.
 *
 * @tparam Weight Тип данных для весов.
 *
 * @param client Указатель на HTTP клиент.
 * @param weightType Строковое представление типа данных весов вершин.
 *
 * Функция используется для сокращения кода, необходимого для поддержки
 * различных типов данных.
 * 
 * Рёбра добавляются в топологическом порядке, чтобы не образовались циклы.
 */
template <typename Weight>
static void RandomFloatingPointHelperTest(
  httplib::Client* client, 
  const std::string& weightType
) {
  const int numTries = 100;
  std::random_device rd;
  std::mt19937 generate(rd());
  std::uniform_int_distribution<size_t> randVerticesNum(1, 40);
  std::uniform_real_distribution<Weight> randWeights(
    Weight(1), 
    Weight(10'000)
  );

  for (int id = 0; id < numTries; id++) {
    size_t numVertices = randVerticesNum(generate);

    size_t maxEdges = numVertices * (numVertices - 1) / 2;
    std::uniform_int_distribution<size_t> randEdgesNum(0, maxEdges);
    size_t numEdges = randEdgesNum(generate);

    std::uniform_int_distribution<size_t> randIndexes(0, numVertices - 1);

    nlohmann::json input;
    input["id"] = id;
    input["weight_type"] = weightType;
    input["number_of_vertices"] = numVertices;
    input["number_of_edges"] = numEdges;
    input["vertices"] = std::vector<size_t>(numVertices);
    input["edges"] = std::vector<nlohmann::json>(numEdges);

    std::vector<size_t> vertices(numVertices);

    for (size_t i = 0; i < numVertices; i++) {
      vertices[i] = i + 1;
    }

    std::shuffle(vertices.begin(), vertices.end(), generate);

    for (size_t i = 0; i < numVertices; i++) {
      input["vertices"][i] = vertices[i];
    }

    Weight maxWeight = std::numeric_limits<Weight>::min();

    std::set<std::pair<size_t, size_t>> edges;

    for (size_t i = 0; i < numEdges; i++) {
      std::uniform_int_distribution<size_t> startDist(0, numVertices - 2);
      size_t start = startDist(generate);

      std::uniform_int_distribution<size_t> endDist(start + 1, numVertices - 1);
      size_t end = endDist(generate);

      while (edges.find({start, end}) != edges.end()) {
        std::uniform_int_distribution<size_t> startDist(0, numVertices - 2);
        start = startDist(generate);

        std::uniform_int_distribution<size_t> endDist(start + 1, numVertices - 1);
        end = endDist(generate);
      }

      edges.insert({start, end});

      Weight weight = randWeights(generate);

      input["edges"][i] = {
        {"start", vertices[start]},
        {"end", vertices[end]},
        {"weight", weight}
      };

      if (weight > maxWeight) maxWeight = weight;
    }

    httplib::Result result = client->Post(
      "/TopologicalSort", 
      input.dump(),
      "application/json"
    );

    nlohmann::json output = nlohmann::json::parse(result->body);

    REQUIRE_EQUAL(id, output.at("id"));
    REQUIRE_EQUAL(weightType, output.at("weight_type"));
    REQUIRE_EQUAL(maxWeight, output.at("max_weight"));
    REQUIRE_EQUAL(true, isTopologicallySorted(output.at("order"), input));
  }
}