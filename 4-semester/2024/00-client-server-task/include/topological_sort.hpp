/**
 * @file topological_sort.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация алгоритма топологической сортировки ориентированного
 * ациклического графа.
 */

#ifndef INCLUDE_TOPOLOGICAL_SORT_HPP_
#define INCLUDE_TOPOLOGICAL_SORT_HPP_

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "oriented_graph.hpp"

namespace graph {

void dfs(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, std::string>& visited,
  std::vector<size_t>& result_order
);

bool isCyclic(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, std::string>& visited
);

/**
 * @brief Алгоритм топологической сортировки.
 *
 * @param graph На вход подаётся ссылка на объект типа graph::OrientedGraph,
 * описанный в файле @sa oriented_graph.hpp
 *
 * @return Алгоритм возвращает отсортированный вектор вершин такой, что
 * для любого ребра (U, V) вершина U в этом векторе находится раньше 
 * вершины V, или пустой вектор, если в графе есть цикл.
 *
 * Функция инициализирует словарь посещённых вершин, алгоритмом 
 * обхода в глубину проверяет граф на ацикличность, переупорядочивает вершины 
 * и кладёт их в итоговый вектор.
 */
std::vector<size_t> TopologicalSort(OrientedGraph& graph) {
  std::unordered_map<size_t, std::string> visited;

  std::cout  << std::endl << "in TopologicalSort graph.Vertices(): ";

  for (auto vertex : graph.Vertices()) {
    visited[vertex] = "white";
    std::cout << vertex << " ";
  }
  std::cout << std::endl;

  std::vector<size_t> result_order;

  for (auto vertex : graph.Vertices()) {
    if (isCyclic(graph, vertex, visited)) {
      std::cout << "is cyclic!" << std::endl;
      return result_order;
    }
  }

  for (auto vertex : graph.Vertices()) {
    visited[vertex] = "white";
  }
  
  for (auto vertex : graph.Vertices()) {
    if (visited[vertex] == "white") {
      dfs(graph, vertex, visited, result_order);
    }
  }

  std::reverse(result_order.begin(), result_order.end());

  return result_order;
}

/**
 * @brief Алгоритм обхода в глубину для топологической сортировки.
 *
 * @param graph Объект типа graph::OrientedGraph, описанный в файле:
 * @sa oriented_graph.hpp
 * @param vertex Итерируемая вершина графа.
 * @param visited Словарь пройденных вершин.
 * @param result_order Вектор, куда будут добавляться вершины по мере сортировки.
 *
 * Функция отмечает вершину, в которую мы попали, и для всех исходящих из неё
 * рёбер применяет рекурсию, если их ещё не обработали. В конце добавляет
 * в итоговый вектор вершину.
 */
void dfs(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, std::string>& visited,
  std::vector<size_t>& result_order
) {
  visited[vertex] = "grey";

  for (auto destination : graph.Edges(vertex))
    if (visited[destination] == "white")
      dfs(graph, destination, visited, result_order);

  result_order.push_back(vertex);
}

/**
 * @brief Алгоритм проверки на ацикличность ориентированного графа 
 * с помощью обхода в глубину.
 *
 * @param graph Объект типа graph::OrientedGraph, описанный в файле:
 * @sa oriented_graph.hpp
 * @param vertex Итерируемая вершина графа.
 * @param visited Словарь пройденных вершин.
 *
 * Функция рекурсивно проходит по всем исходящим рёбрам до тех пор, пока
 * не дойдёт до вершины, из которой не исходит ребро, или до тех пор,
 * пока цикл не замкнётся.
 */
bool isCyclic(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, std::string>& visited
) {
  visited[vertex] = "grey";

  std::cout << std::endl << "in isCyclic vertex: " << vertex << std::endl;

  for (auto destination : graph.Edges(vertex)) {

    std::cout << "destination: " << destination << " is visited?: " << visited[destination] << std::endl;

    if (visited[destination] == "white")
      return isCyclic(graph, destination, visited);
    if (visited[destination] == "grey")
      return true;
  }

  visited[vertex] = "black";
  
  return false;
}

}  // namespace graph

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_