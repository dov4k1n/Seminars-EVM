/**
 * @file topological_sort.hpp
 * @author Ayzat Rizatdinov (dov4k1n)
 *
 * Реализация алгоритма топологической сортировки ориентированного
 * ациклического графа.
 */

#ifndef INCLUDE_TOPOLOGICAL_SORT_HPP_
#define INCLUDE_TOPOLOGICAL_SORT_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <oriented_graph.hpp>

namespace graph {

/**
 * @brief Алгоритм топологической сортировки.
 *
 * @param graph На вход подаётся ссылка на объект типа graph::OrientedGraph,
 * описанный в файле @sa oriented_graph.hpp
 *
 * @return Алгоритм возвращает отсортированный список рёбер в виде пар:
 * (id вершины с меньшим номером, id вершины с большим номером), или
 * пустой вектор, если в графе есть цикл.
 *
 * Функция инициализирует словарь посещённых вершин, алгоритмом 
 * обхода в глубину проверяет граф на ацикличность, переупорядочивает вершины 
 * и кладёт их в итоговый вектор.
 */
std::vector<std::pair<size_t, size_t>> TopologicalSort(OrientedGraph& graph) {
  std::unordered_map<size_t, bool> visited;
  for (auto vertex : graph.Vertices()) {
    visited[vertex] = false;
  }

  std::vector<std::pair<size_t, size_t> result_order;

  for (auto vertex : graph.Vertices()) {
    if (isCyclic(graph, visited, vertex)) {
      return result_order;
    }
  }

  for (auto vertex : graph.Vertices()) {
    visited[vertex] = false;
  }
  
  for (auto vertex : graph.Vertices()) {
    if (!visited[vertex]) {
      dfs(graph, visited, vertex, result_order);
    }
  }

  return result;
}

/**
 * @brief Алгоритм обхода в глубину для топологической сортировки.
 *
 * @param graph Объект типа graph::OrientedGraph, описанный в файле:
 * @sa oriented_graph.hpp
 * @param vertex Итерируемая вершина графа.
 * @param visited Словарь пройденных вершин.
 * @param result_order Вектор, куда будут добавляться рёбра по мере сортировки.
 *
 * Функция отмечает вершину, в которую мы попали, и для всех исходящих из неё
 * рёбер применяет рекурсию, если их ещё не обработали. В конце добавляет
 * в итоговый вектор рёбер переупорядочённые пары вершин.
 */
void dfs(
  const OrientedGraph& graph,
  const size_t& vertex,
  std::unordered_map<size_t, bool>& visited,
  std::vector<std::pair<size_t, size_t>>& result_order
) {
  visited[vertex] = true;

  for (auto destination : graph.Edges(vertex)) {
    if (!visited[destination])
      dfs(graph, destination, visited, result_order);

    if (destination > vertex) {
      result_order.push_back({vertex, destination});
    } else {
      result_order.push_back({destination, vetex});
    }
  }
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
  std::unordered_map<size_t, bool>& visited
) {
  visited[vertex] = true;

  for (auto destination : graph.Edges(vertex)) {
    if (visited[destionation])
      return true;
    if (!visited[destination])
      return isCyclic(graph, destination, visited);
  }
  
  return false;
}

}  // namespace graph

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_