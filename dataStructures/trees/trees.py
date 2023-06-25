from Libtree.Libtree import Tree as tree
from Libtree.Libtree import Node as node


def main() -> int:
    print("Manually initialized tree")
    potato = tree(node(3, 1, node(6, 1, node(-2, 1, node(
        1, 1, None, None), None), node(10, 1, None, None)), None), False)
    potato.print_values()
    potato.pretty_print()
    print(f"Tree depth: {potato.get_depth()}")
    print(f"Node Count: {potato.get_node_count()}")
    print(f"Min val: {potato.get_min()}")
    print(f"Max val: {potato.get_max()}")
    print(f"Is binary tree: {potato.is_binary_search_tree()}")
    print("Converting tree to array...")
    arrayFromTree = potato.IntoArray()
    print(f"As array: {arrayFromTree}")
    print("Converting back into tree...")
    treeFromArray = tree.FromArray(arrayFromTree)
    treeFromArray.print_values()
    print(f"Root Value: {treeFromArray.root.value}")
    print(f"Is binary tree: {treeFromArray.is_binary_search_tree()}")
    array = [1, 2, 3, 5, 8, 13, 21, 34, 55]
    treeFromArray = tree.FromArray(array)
    treeFromArray.print_values()
    print(f"Is binary tree: {treeFromArray.is_binary_search_tree()}")
    print("Inserting unbalanced node under value 2...")
    treeFromArray.root.left.left.right = node(4, 1, None, None)
    treeFromArray.print_values()
    print(f"Is binary tree: {treeFromArray.is_binary_search_tree()}")

    print("Constructing tree from individual insertions...")
    insertion_tree = tree(None, True)
    for e in array:
        print(f"Inserting value: {e}")
        insertion_tree.insert(e)
    insertion_tree.print_values()
    print(f"Is binary tree: {insertion_tree.is_binary_search_tree()}")
    print(f"Is the value 77 in the tree? {insertion_tree.is_in_tree(77)}")
    print(f"Is the value 13 in the tree? {insertion_tree.is_in_tree(13)}")
    insert_t_array = insertion_tree.IntoArray()
    print(insert_t_array)
    insert_t_array.sort()
    insert_t_from_array = tree.FromArray(insert_t_array)
    value = 34
    print(
        f"Find value: {value}, found value: {insert_t_from_array.find_value(value).value}")
    print("Balanced tree by sorting corresponding array...")
    insert_t_from_array.pretty_print()
    insert_t_from_array.delete_value(34)
    insert_t_from_array.pretty_print()


if __name__ == "__main__":
    main()
