/**
 * @file methods/topological_sort_method.cpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Файл содержит функцию, которая вызывает алгоритм топологической сортировки.
 * Функция принимает и возвращает данные в JSON формате.
 */

#include <iostream>
#include <nlohmann/json.hpp>
#include "topological_sort.hpp"
#include "oriented_graph.hpp"
#include "methods.hpp"

namespace graph {

int TopologicalSortMethod(
  const nlohmann::json& input,
  nlohmann::json* output
) {
  (*output)["id"] = input.at("id");

  graph::OrientedGraph graph;

  for (auto vertex : input.at("vertices")) {
    graph.AddVertex(vertex);
    std::cout << vertex << std::endl;
  }

  for (auto edge : input.at("edges")) {
    graph.AddEdge(edge.at("start"), edge.at("end"));
    std::cout << edge << std::endl;
    std::cout << edge.at("start") << std::endl;
    std::cout << edge.at("end") << std::endl;
  }

  std::vector<size_t> result_order = TopologicalSort(graph);

  for (auto vertex : result_order) {
    std::cout << vertex << " " << std::endl;
  }

  (*output)["result"] = result_order;

  return 0;
}

} // namespace graph