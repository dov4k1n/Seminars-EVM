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
  "id": 5,
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

  REQUIRE_EQUAL(5, output.at("id"));
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

  // RandomFloatingPointHelperTest<float>(client, "float");
  // RandomFloatingPointHelperTest<double>(client, "double");
  // RandomFloatingPointHelperTest<long double>(client, "long double");
}

/** 
 * @brief Простейший случайный тест для целых чисел.
 *
 * @tparam T Тип данных сортируемых элементов.
 *
 * @param cli Указатель на HTTP клиент.
 * @param type Строковое представление типа данных сортируемых элементов.
 *
 * Функция используется для сокращения кода, необходимого для поддержки
 * различных типов данных.
 */
template <typename Weight>
static void RandomIntegerHelperTest(
  httplib::Client* client, 
  const std::string& weight_type
) {
  // Число попыток.
  const int numTries = 100;
  // Используется для инициализации генератора случайных чисел.
  std::random_device rd;
  // Генератор случайных чисел.
  std::mt19937 gen(rd());
  // Распределение для количества вершин.
  std::uniform_int_distribution<size_t> numVertices(10, 50);
  // Распределение для вершин.
  std::uniform_int_distribution<size_t> randVertices(-10'000, 10'000);

  for (int it = 0; it < numTries; it++) {
    // Получаем случайное кол-во вершин, используя функцию распределения.
    size_t size = numVertices(gen);

    nlohmann::json input;

    input["id"] = it;
    input["weight_type"] = weight_type;
    input["size"] = size;

    std::vector<size_t> vertices(size);

    for (size_t i = 0; i < size; i++) {
      // Получаем случайную вершину, используя функцию распределения.
      vertices[i] = randVertices(gen);

      // Записываем элемент в JSON.
      input["vertices"][i] = vertices[i];
    }

    //
    //
    // Нужно добавить рёбра и веса !
    // В случайном графе almost certainly есть цикл?
    //

    /* Отправляем данные на сервер POST запросом. */
    httplib::Result result = client->Post(
      "/TopologicalSort", 
      input.dump(),
      "application/json"
    );

    /* Используем метод parse() для преобразования строки ответа сервера
    (res->body) в объект JSON. */
    nlohmann::json output = nlohmann::json::parse(result->body);

    /* Проверка результатов сортировки. */

    REQUIRE_EQUAL(size, output.at("size"));
    REQUIRE_EQUAL(it, output.at("id"));
    REQUIRE_EQUAL(weight_type, output.at("weight_type"));
    REQUIRE_EQUAL(true, isTopologicallySorted(output.at("order"), input));
  }
}