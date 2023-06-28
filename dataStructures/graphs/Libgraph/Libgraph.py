from collections import OrderedDict


class gNode():

    def __init__(self, name):
        self.name = name
        self.adjMap = OrderedDict()

    def addAdjNode(self, node):
        self.adjMap[node.name] = node


class Graph():

    def __init__(self):
        self.nodes = OrderedDict()

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

    def BFS_print(self):
        visited = OrderedDict()
        breadth_queue = OrderedDict()

        for node in self.nodes.keys():
            if node not in visited:
                breadth_queue[node] = node
                visited[node] = node

            while len(breadth_queue) > 0:
                item = breadth_queue.pop(list(breadth_queue.keys())[0])
                print(self.nodes[item].name, end=' ')
                for n in self.nodes[item].adjMap.keys():
                    if n not in visited:
                        breadth_queue[n] = n
                        visited[n] = n
                if len(breadth_queue) == 0:
                    print("")

    def BFS_traverse(self, func):
        # TODO: add datastructure to track minimum paths
        visited = OrderedDict()
        breadth_queue = OrderedDict()

        for node in self.nodes.keys():
            if node not in visited:
                breadth_queue[node] = node
                visited[node] = node

            while len(breadth_queue) > 0:
                item = breadth_queue.pop(list(breadth_queue)[0])
                func(self.nodes[item])
                for n in self.nodes[item].adjMap:
                    if n not in visited:
                        breadth_queue[n] = n
                        visited[n] = n

    def DFS_print(self):
        visited = OrderedDict()

        def recurs_DFS(node):
            nonlocal visited
            if node not in visited:
                visited[node] = node
                print(self.nodes[node].name, end=' ')
                for n in self.nodes[node].adjMap:
                    if n not in visited:
                        recurs_DFS(n)

        for n in self.nodes:
            if n not in visited:
                recurs_DFS(n)
                print("")

    def DFS_traverse(self, func):
        visited = OrderedDict()
        # TODO: Leverage datastruct to draw minimum spanning tree

        def recurs_DFS(node):
            nonlocal visited
            if node not in visited:
                visited[node] = node
                func(self.nodes[node])
                for n in self.nodes[node].adjMap:
                    if n not in visited:
                        recurs_DFS(n)

        for n in self.nodes:
            recurs_DFS(n)
