#define TREE_BINARY__TEST_1


#ifdef TREE_BINARY__TEST_1

#include <iostream>
#include "BNode.h"
#include "BinaryTree.h"

int main() {
	Tree::BNode<int> node = Tree::BNode<int>(NULL);

	node.setValue(150);
	node.setLeftChild(10);
	node.setRightChild(20);
	node.left()->setRightChild(33);
	node.getRightChild()->setLeftChild(999);

	std::cout << node.toString() << std::endl;

	std::cout << std::endl;

	Tree::BinaryTree<int> btree = Tree::BinaryTree<int>(2);

	btree.insert(105);
	btree.insert(105);
	btree.insert(101);
	btree.insert(101);
	btree.insert(10101);

	btree.printTree();
	btree.printLevelOrder();
	btree.printVisual(true);
	btree.printVisual(false);

	//~node();
}

#endif