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
    graph.print()


if __name__ == "__main__":
    main()
