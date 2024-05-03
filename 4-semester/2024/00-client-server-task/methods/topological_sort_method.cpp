/**
 * @file methods/topological_sort_method.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация функции для серверной части алгоритмов. Эта функция
 * считывает JSON, который прислал клиент, выполняет алгоритм и отправляет клиенту
 * JSON с результатом работы алгоритма.
 */

#include <topological_sort.hpp>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include "methods.hpp"



int graph::TopologicalSortMethod(
  const nlohmann::json &input,
  nlohmann::json *output
) {
  graph::Graph graph;

  for (auto vertex : input["vertices"]) {
    graph.AddVertex(vertex);
  }

  for (auto edge : input["edged"]) {
    graph.AddEdge(edge[0], edge[1]);
  }

  (*output) = {
    {
      "result",
      TopologicalSort(
        graph,
        input["vertices_first_part"],
        input["vertices_second_part"]
      )
    }
  };

  return 0;
}