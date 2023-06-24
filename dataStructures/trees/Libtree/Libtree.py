from dataclasses import dataclass
from typing import List
from math import ceil

LNODE = 0
RNODE = 1


class Node:
    def __init__(self, value, count, left, right):
        self.value = value
        self.count = count
        self.left = left
        self.right = right

    def traverse_depth(self, func):
        if self.left != None:
            self.left.traverse_depth(func)
        func(self)
        if self.right != None:
            self.right.traverse_depth(func)

    def traverse_preOrder(self, func):
        func(self)
        if self.left != None:
            self.left.traverse_preOrder(func)
        if self.right != None:
            self.right.traverse_preOrder(func)

    def traverse_postOrder(self, func):
        if self.left != None:
            self.left.traverse_postOrder(func)
        if self.right != None:
            self.right.traverse_postOrder(func)
        func(self)

    def get_depth(self):
        depths = [0, 0]
        if self.left is not None:
            depths[0] = self.left.get_depth()
        if self.right is not None:
            depths[1] = self.right.get_depth()
        return 1 + max(depths)


@ dataclass
class Tree:
    root: Node
    is_bin_tree: bool

    def insert(self, value):
        node = self.root
        if node is None:
            self.root = Node(value, 1, None, None)
            return
        while (True):
            if (value < node.value):
                if node.left is None:
                    node.left = Node(value, 1, None, None)
                    return
                else:
                    node = node.left
            elif (value > node.value):
                if node.right is None:
                    node.right = Node(value, 1, None, None)
                    return
                else:
                    node = node.right
        self.is_bin_tree = self.is_binary_search_tree()

    def get_node_count(self):
        counter = 0

        def counter_func(node):
            nonlocal counter
            counter = counter + 1

        self.root.traverse_depth(counter_func)
        return counter

    def get_depth(self):
        return self.root.get_depth()

    def print_values(self):
        def print_value(node):
            print(node.value, end=' ')
        self.root.traverse_depth(print_value)
        print("")

    def delete_tree(self):
        self.root = None

    def is_in_tree(self, value):
        return self.find_value(value) is not None

    def get_max(self):
        max = -999999999

        def rec_max(node):
            nonlocal max
            if node.value > max:
                max = node.value
        self.root.traverse_depth(rec_max)
        return max

    def get_min(self):
        min = 999999999

        def rec_min(node):
            nonlocal min
            if node.value < min:
                min = node.value
        self.root.traverse_depth(rec_min)
        return min

    def is_binary_search_tree(self):
        result = True

        def is_ordered(value, hi, lo):
            result = (value.value < hi) and (value.value > lo)
            if value.left is not None:
                result = result and is_ordered(value.left, value.value, lo)
            if value.right is not None:
                result = result and is_ordered(value.right, hi, value.value)
            return result

        return is_ordered(self.root, 999999999, -999999999)

    def delete_value(self, value):
        pass  # TODO: Complete this function

    def get_successor(self, value):
        pass  # TODO: Complete this function

    def find_value(self, value):
        node = self.root
        location = ""
        if node is None:
            return None
        while (True):
            if (value < node.value):
                if node.left is None:
                    return None
                else:
                    location += "l"
                    node = node.left

            elif (value > node.value):
                if node.right is None:
                    return None
                else:
                    location += "r"
                    node = node.right
            else:
                return location

    def IntoArray(self):
        array = []

        def append_leaf(node):
            nonlocal array
            array.append(node.value)
        self.root.traverse_depth(append_leaf)
        return array

    @classmethod
    def FromArray(cls, array: []):
        if len(array) == 0:
            return Tree(None, True)

        def node_init(value):
            return Node(value, 1, None, None)

        def binary_recursion(array: []):
            if len(array) == 0:
                return None
            lo = 0
            hi = len(array)
            mid = round(len(array)/2)

            local_root = node_init(array[mid])
            local_root.left = binary_recursion(array[lo:mid])
            local_root.right = binary_recursion(array[mid+1:hi])
            return local_root

        # array.sort()
        result = Tree(binary_recursion(array), False)
        result.is_bin_tree = result.is_binary_search_tree()

        return result
