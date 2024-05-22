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
#include "weighted_oriented_graph.hpp"
#include "methods.hpp"

namespace graph {

template <typename Weight>
static int TopologicalSortMethodHelper(
  const nlohmann::json& input,
  nlohmann::json* output
);

int TopologicalSortMethod(
  const nlohmann::json& input,
  nlohmann::json* output
) {
  std::string weight_type = input.at("weight_type");

  /* Пока реализована только поддержка целых чисел и чисел типа double. */
  if (weight_type == "int") {
    return TopologicalSortMethodHelper<int>(input, output);
  } else if (weight_type == "float") {
    return TopologicalSortMethodHelper<float>(input, output);
  } else if (weight_type == "double") {
    return TopologicalSortMethodHelper<double>(input, output);
  } else if (weight_type == "long double") {
    return TopologicalSortMethodHelper<long double>(input, output);
  } else if (weight_type == "") {
    (*output)["id"] = input.at("id");
    (*output)["order"] = std::vector<size_t>();
    (*output)["max_weight"] = "";
    return 0;
  }

  return 0;
}

template <typename Weight>
static int TopologicalSortMethodHelper(
  const nlohmann::json& input,
  nlohmann::json* output
) {
  std::cout <<
    std::endl <<
    "-------------------------------------------------|" <<
    std::endl;

  std::cout << 
    std::endl << 
    "input:" << 
    std::endl;

  std::cout << 
    "id " << 
    input.at("id") << 
    std::endl;

  graph::WeightedOrientedGraph<Weight> graph;

  for (auto vertex : input.at("vertices")) {
    graph.AddVertex(vertex);
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  for (auto edge : input.at("edges")) {
    graph.AddEdge(edge.at("start"), edge.at("end"), edge.at("weight"));
    std::cout << edge << std::endl;
  }
  std::cout << input.at("weight_type") << std::endl;

  TSortOutput<Weight> result = TopologicalSort<Weight>(graph);

  std::cout << std::endl << "result order: " << std::endl;
  for (auto vertex : result.order) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  std::cout << 
    "max weight: " << 
    std::endl << 
    result.max_weight << 
    std::endl;
  
  std::cout <<
    std::endl <<
    "-------------------------------------------------|" <<
    std::endl;

  (*output)["id"] = input.at("id");
  (*output)["order"] = result.order;
  (*output)["max_weight"] = result.max_weight;

  return 0;
}

} // namespace graph