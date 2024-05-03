/**
 * @file topological_sort.hpp
 * @author Ayzat Rizatdinov
 *
 * Реализация топологической сортировки.
 */

#ifndef INCLUDE_TOPOLOGICAL_SORT_HPP_
#define INCLUDE_TOPOLOGICAL_SORT_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <graph.hpp>

#define Edge std::pair<size_t, size_t>

template<class Graph>
void dfs(
  const Graph &graph,
  std::unordered_map<size_t, bool> *used,
  size_t root, 
  size_t dest,
  std::vector<Edge> *result
) {

  (*used)[root] = true;

  for (size_t way : graph.Edges(root)) {
    if (!(*used)[way]) {
      dfs(
        graph, 
        used, 
        root, 
        way, 
        result
      );
    }

    if (way > root) {
      (*result).push_back({root, way});
    } else {
      (*result).push_back({way, root});
    }
  }
}


/**
 * @brief Алгоритм топологической сортировки.
 *
 * @param graph На вход подаётся ссылка на объект типа graph::Graph,
 * описанный в файле: 
 * @sa graph.cpp
 *
 * @return Алгоритм возвращает отсортированный список вершин в виде пар:
 * (id одной вершины, id второй вершины).
 */
template<class Graph>
std::vector<Edge> TopologicalSort(const Graph &graph) {
  
  std::unordered_map<size_t, bool> used;

  std::vector<Edge> result;

  for (auto vertex : graph.Vertices()) {
    used[vertex] = false;
  }

  result.clear();

  for (auto vertex : graph.Vertices()) {
    if (!used[vertex]) {
      dfs(graph, &used, vertex, &result);
    }
  }

  reverse (result.begin(), result.end());

  return result;
}

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_