from dataclasses import dataclass


@dataclass
class Node:
    value,
    left: Node
    right: Node


@dataclass
class Tree:
    root: Node

    def insert(self, val):
        pass

    def get_node_count(self):
        pass

    def print_values(self):
        pass

    def delete_tree(self):
        pass

    def is_in_tee(self, value):
        pass

    def get_height(self):
        pass

    def get_min(self):
        pass

    def get_max(self):
        pass

    def is_binary_search_tree(self):
        pass

    def delete_value(self, value):
        pass

    def get_succsesor(self, value):
        pass

    def find_value(self, value):
        pass

    def flatten(self):
        pass
