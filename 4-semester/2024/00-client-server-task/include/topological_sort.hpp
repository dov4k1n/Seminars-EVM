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
#include "weighted_oriented_graph.hpp"

namespace graph {

/**
 * @brief Перечисление состояний вершины графа при обходе в глубину. 
 */
enum DFSVertexState {
  NotVisited,
  Processing,
  Processed
};

/**
 * @brief Массив для печати состояния вершины графа при обходе в глубину
 * в читаемом виде.
 */
const char* DFSVertexState_txt[] = {
  "not visited",
  "processing",
  "processed"
};

/**
 * @brief Возвращаемая структура для алгоритма топологической сортировки
 * с максимальным весом. 
 */
template <typename Weight>
struct TSortOutput {
  std::vector<size_t> order;
  Weight max_weight;
};

template <typename Weight>
void dfs(
  const WeightedOrientedGraph<Weight>& graph,
  const size_t& vertex,
  std::unordered_map<size_t, DFSVertexState>& visited,
  TSortOutput<Weight>& result,
  bool& is_cyclic
);

/**
 * @brief Алгоритм топологической сортировки.
 *
 * @param graph На вход подаётся ссылка на объект типа 
 * graph::WeightedOrientedGraph, описанный в файле 
 * @sa weighted_oriented_graph.hpp
 *
 * @return Алгоритм возвращает вектор вершин такой, что
 * для любого ребра (U, V) вершина U в этом векторе находится раньше 
 * вершины V, или пустой вектор, если в графе есть цикл. А также
 * максимальный вес ребра.
 *
 * Функция инициализирует словарь посещённых вершин, алгоритмом 
 * обхода в глубину проверяет граф на ацикличность и кладёт их в 
 * итоговый вектор, начиная с листьев. В самом конце вектор разворачивается.
 */
template <typename Weight>
TSortOutput<Weight> TopologicalSort(WeightedOrientedGraph<Weight>& graph) {
  std::unordered_map<size_t, DFSVertexState> visited;
  TSortOutput<Weight> result;
  result.max_weight = std::numeric_limits<Weight>::min();
  bool is_cyclic = false;

  std::cout << 
    std::endl << 
    "in TopologicalSort graph.Vertices():" << 
    std::endl;

  for (auto vertex : graph.Vertices()) {
    visited[vertex] = DFSVertexState::NotVisited;
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  
  for (auto vertex : graph.Vertices()) {
    if (is_cyclic) {
      std::cout << "is cyclic!" << std::endl;
      result.order = std::vector<size_t>();
      result.max_weight = Weight();
      return result;
    }
    
    if (visited[vertex] == DFSVertexState::NotVisited) {
      dfs<Weight>(graph, vertex, visited, result, is_cyclic);
    }
  }

  std::reverse(result.order.begin(), result.order.end());

  return result;
}

/**
 * @brief Алгоритм обхода в глубину для топологической сортировки.
 *
 * @param graph Объект типа graph::WeightedOrientedGraph, описанный в файле:
 * @sa weighted_oriented_graph.hpp
 * @param vertex Итерируемая вершина графа.
 * @param visited Словарь пройденных вершин.
 * @param result_order Вектор, куда будут добавляться вершины 
 * по мере сортировки.
 * @param is_cyclic Булевая переменная (по умолчанию false), в которую
 * записывается true, если по ходу работы выяснилось, что граф циклический.
 *
 * Функция отмечает вершину, в которую мы попали, и для всех исходящих из неё
 * рёбер применяет рекурсию, если их ещё не обработали. В конце добавляет
 * в итоговый вектор вершину.
 */
template <typename Weight>
void dfs(
  const WeightedOrientedGraph<Weight>& graph,
  const size_t& vertex,
  std::unordered_map<size_t, DFSVertexState>& visited,
  TSortOutput<Weight>& result,
  bool& is_cyclic
) {
  visited[vertex] = DFSVertexState::Processing;

  std::cout << 
    std::endl << 
    "in dfs vertex: " << vertex 
    << std::endl;

  for (auto destination : graph.Edges(vertex)) {
    std::cout << 
      "destination " << destination << 
      " is visited?: " << DFSVertexState_txt[visited[destination]] << 
      std::endl;

    if (visited[destination] == DFSVertexState::NotVisited)
      dfs<Weight>(graph, destination, visited, result, is_cyclic);
    if (visited[destination] == DFSVertexState::Processing) {
      is_cyclic = true;
      return;
    }

    Weight current_weight = graph.EdgeWeight(vertex, destination);
    if (current_weight > result.max_weight) {
      result.max_weight = current_weight;
      std::cout <<
        "max weight is now " << current_weight <<
        std::endl;
    }
  }

  visited[vertex] = DFSVertexState::Processed;
  std::cout << 
    vertex << 
    " is now " << DFSVertexState_txt[visited[vertex]] << 
    std::endl;

  result.order.push_back(vertex);
}

}  // namespace graph

#endif  // INCLUDE_BRIDGE_SEARCH_HPP_