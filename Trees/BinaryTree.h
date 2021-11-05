
#include "Tree.h"
//#include "BNode.h"
#include <string>
#include <iostream>

namespace Tree {
	
	template<typename NodeData> class BinaryTree : public Tree<NodeData> {


	public:
		// constructors & destructors
		BinaryTree();
		BinaryTree(BNode<NodeData>* root);
		BinaryTree(NodeData rootVal);
		~BinaryTree();

		// utility functions
		// override of base class getRootNode (VIRTUAL)
		// BUT TYPE IS DIFFERENT!!?
		BNode<NodeData>* getRootNode();

		// inserts at the first empty-child-node 
		// in left-to-right, level-order
		virtual BNode<NodeData>* insert(NodeData val);
		virtual BNode<NodeData>* insert(BNode<NodeData>* node);

		static BNode<NodeData>* toBinaryNode(Node<NodeData>* node);

		// does not differentiate between L & R nodes for single-child nodes
		virtual void printVisual(bool ignoreNULL = true) {
			Tree<NodeData>::printVisual(ignoreNULL);
		};

		// A pure virtual function or pure virtual method is a virtual function that is 
		// required to be implemented by a derived class if the derived class is not abstract.

		// --- > should be in a BT class
		// void printInOrder();
		// void printPreOrder();
		// void printPostOrder();
	
		// should be for BBST (AVL)
		// bool isLeftHeavy();

	};

	template<typename NodeData> BinaryTree<NodeData>::BinaryTree() : Tree<NodeData>() {
	};

	template<typename NodeData> BinaryTree<NodeData>::BinaryTree(BNode<NodeData>* root) 
	: Tree<NodeData>(root) {
	}

	template<typename NodeData> BinaryTree<NodeData>::BinaryTree(NodeData rootVal) {
		BinaryTree<NodeData>::root = new BNode<NodeData>(rootVal);
	}

	template<typename NodeData> BinaryTree<NodeData>::~BinaryTree() {
		std::cout << "Binary Tree Cleanup" << std::endl;
	}

	// getters and setters

	template<typename NodeData> BNode<NodeData>* BinaryTree<NodeData>::getRootNode() {
		return (BNode<NodeData>*) BinaryTree<NodeData>::root;
	}


	// inserts at the first empty-child-node 
	// in left-to-right, level-order
	template<typename NodeData> BNode<NodeData>* BinaryTree<NodeData>::insert(BNode<NodeData>* node) {

		// if tree empty
		if (BinaryTree<NodeData>::root == NULL) {
			return BinaryTree<NodeData>::toBinaryNode(BinaryTree<NodeData>::root = node);
		}

		// current level nodes
		std::vector<Node<NodeData>*> levelNodes;
		levelNodes.push_back(BinaryTree<NodeData>::getRootNode());
		int level = 0;					// stores info about what level the node was inserted in

		// level-order search for NULL node
		while (!levelNodes.empty()) {

			// which nodes entail this search
			// 0 -> size()
			int levelSize = levelNodes.size();

			for (int i = 0; i < levelSize; i++) {

				BNode<NodeData>* n = (BNode<NodeData>*) levelNodes.at(i);

				if (n == NULL) continue;

				if (!n->hasLeftChild()) {
					return n->setLeftChild(node);
				}

				if (!n->hasRightChild()) {
					return n->setRightChild(node);
				}

				// getSubNodes() returns a "copy" of the vector!
				// equality "=" operator copies right-side vector to left-side vector
				std::vector<Node<NodeData>*> subNodes = n->getSubNodes();

				// push all children to end of vector
				levelNodes.insert(levelNodes.end(), subNodes.begin(), subNodes.end());
			}

			// which nodes to remove (level just done)
			// 0 -> levelSize
			levelNodes.erase(levelNodes.begin(), levelNodes.begin() + levelSize);

			level += 1;
		}

		levelNodes.clear();		// not necessary, as called upon leaving scope

		// insertion failed? for whatever reason?
		return NULL;

	}
	
	template<typename NodeData> BNode<NodeData>* BinaryTree<NodeData>::insert(NodeData val) {

		BNode<NodeData>* newNode = new BNode<NodeData>(val);
		if (insert(newNode) == NULL) {
			// insertion failed for some reason, delete created node
			delete newNode;
		}
		return newNode;		// NULL if insertion failed
	}



	template<typename NodeData> BNode<NodeData>* BinaryTree<NodeData>::toBinaryNode(Node<NodeData>* node) {
		return (BNode<NodeData>*) node;
	}
}