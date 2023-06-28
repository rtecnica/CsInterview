from Libgraph.Libgraph import *


def main():
    graph_dict = {1: [2],
                  2: [3],
                  3: [4, 5],
                  4: [6],
                  5: [6],
                  6: [7],
                  7: [],
                  # 8: [],
                  # 9: [],
                  }

    graph = Graph.fromDict(graph_dict)
    print("Print values using BFS:")
    graph.BFS_print()
    print("Print values using DFS:")
    graph.DFS_print()
    print("")
    graph_dict = {1: [2, 4],
                  2: [3],
                  3: [4, 5],
                  4: [6, 8],
                  5: [6],
                  6: [7],
                  7: [5],
                  8: [],
                  9: [10],
                  10: [12],
                  11: [10],
                  12: [11],
                  }

    graph = Graph.fromDict(graph_dict)
    print("Print values using BFS:")
    graph.BFS_print()
    print("Print values using DFS:")
    graph.DFS_print()
    print("")
    graph_dict = {1: [2],
                  2: [3],
                  3: [1],
                  }

    graph = Graph.fromDict(graph_dict)
    print("Print values using BFS:")
    graph.BFS_print()
    print("Print values using DFS:")
    graph.DFS_print()
    print("")


if __name__ == "__main__":
    main()
