from collections import OrderedDict


class gNode():

    def __init__(self, name):
        self.name = name
        self.adjMap = {}

    def addAdjNode(self, node):
        self.adjMap[node.name] = node


class Graph():

    def __init__(self):
        self.nodes = {}

    def addNode(self, node: gNode):
        self.nodes[node.name] = node

    @classmethod
    def fromDict(cls, dict: {}):
        new_graph = Graph()
        for k in dict.keys():
            new_node = gNode(k)
            new_graph.addNode(new_node)

        for k in dict.keys():
            for n in dict[k]:
                try:
                    new_graph.nodes[k].addAdjNode(new_graph.nodes[n])
                except KeyError:
                    pass

        return new_graph

    def print(self):
        for n in self.nodes:
            print(self.nodes[n].name, end=': ')
            for an in self.nodes[n].adjMap:
                print(self.nodes[n].adjMap[an].name, end=' ')
            print("")

    def BFS(self):
        visited = OrderedDict()

    def DFS(self):
        pass
