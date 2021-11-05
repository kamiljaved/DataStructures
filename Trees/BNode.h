#include "Node.h"
#include <iostream>
#include <string>

namespace Tree {

	// Binary Tree Node
	template<typename NodeData> class BNode : public Node<NodeData> {

	public:
		BNode(NodeData val);		// value = val, subNodes = empty
		BNode(NodeData val, BNode<NodeData>* left, BNode<NodeData>* right);
		BNode(NodeData val, NodeData leftVal, NodeData rightVal);
		~BNode();

		// getters and setters
		BNode<NodeData>* getLeftChild();
		BNode<NodeData>* getRightChild();
		BNode<NodeData>* left();
		BNode<NodeData>* right();

		BNode<NodeData>* setLeftChild(BNode<NodeData>* node);
		BNode<NodeData>* setRightChild(BNode<NodeData>* node);
		BNode<NodeData>* setLeftChild(NodeData value);
		BNode<NodeData>* setRightChild(NodeData value);

		// utility methods
		bool isLeafNode();
		bool hasChildren();
		bool hasLeftChild();
		bool hasRightChild();
		bool hasBothChildren();

		int getChildrenCount();

		static BNode<NodeData>* toBinaryNode(Node<NodeData>* node);

		// base-class function override
		std::string toString();

	};


	//
	// class function definitions
	//

	template<typename NodeData> BNode<NodeData>::BNode(NodeData val) : Node<NodeData>(val) {
		BNode<NodeData>::subNodes.push_back(NULL);		// left child
		BNode<NodeData>::subNodes.push_back(NULL);		// right child
	}

	template<typename NodeData> BNode<NodeData>::BNode(NodeData val, BNode<NodeData>* left, BNode<NodeData>* right) : Node<NodeData>(val) {
		BNode<NodeData>::subNodes.push_back(left);		// left child
		BNode<NodeData>::subNodes.push_back(right);		// right child
	}

	template<typename NodeData> BNode<NodeData>::BNode(NodeData val, NodeData leftVal, NodeData rightVal) : Node<NodeData>(val) {
		BNode<NodeData>::subNodes.push_back(new BNode<NodeData>(leftVal));		// left child
		BNode<NodeData>::subNodes.push_back(new BNode<NodeData>(rightVal));		// right child
	}

	template<typename NodeData> BNode<NodeData>::~BNode() {
		std::cout << "Binary node destructor" << std::endl;
	};

	// getters and setters

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::getLeftChild() {
		return toBinaryNode(BNode<NodeData>::subNodes.at(0));
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::getRightChild() {
		return toBinaryNode(BNode<NodeData>::subNodes.at(1));
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::left() {
		return toBinaryNode(BNode<NodeData>::subNodes.at(0));
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::right() {
		return toBinaryNode(BNode<NodeData>::subNodes.at(1));
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::setLeftChild(BNode<NodeData>* node) {
		// C++ language guarantees that delete p will do nothing if p is null
		delete BNode<NodeData>::subNodes.at(0);
		return toBinaryNode(BNode<NodeData>::subNodes.at(0) = node);
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::setRightChild(BNode<NodeData>* node) {
		delete BNode<NodeData>::subNodes.at(1);
		return toBinaryNode(BNode<NodeData>::subNodes.at(1) = node);
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::setLeftChild(NodeData value) {
		// create a new node on HEAP, else is destroyed (stack) once we return from here
		// the new operator returns a unique pointer, and creates data on HEAP
		delete BNode<NodeData>::subNodes.at(0);
		return toBinaryNode(BNode<NodeData>::subNodes.at(0) = new BNode<NodeData>(value));
	}

	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::setRightChild(NodeData value) {
		delete BNode<NodeData>::subNodes.at(1);
		return toBinaryNode(BNode<NodeData>::subNodes.at(1) = new BNode<NodeData>(value));
	}

	// utility methods

	template<typename NodeData> bool BNode<NodeData>::isLeafNode() {
		return BNode<NodeData>::left() == NULL && BNode<NodeData>::right() == NULL;
	}

	template<typename NodeData> bool BNode<NodeData>::hasChildren() {
		return BNode<NodeData>::left() != NULL || BNode<NodeData>::right() != NULL;
	}

	template<typename NodeData> bool BNode<NodeData>::hasLeftChild() {
		return BNode<NodeData>::left() != NULL;
	}

	template<typename NodeData> bool BNode<NodeData>::hasRightChild() {
		return BNode<NodeData>::right() != NULL;
	}

	template<typename NodeData> bool BNode<NodeData>::hasBothChildren() {
		return BNode<NodeData>::left() != NULL && BNode<NodeData>::right() != NULL;
	}

	template<typename NodeData> int BNode<NodeData>::getChildrenCount() {
		int children;
		(BNode<NodeData>::left() == NULL ?
			(BNode<NodeData>::right() == NULL ? children = 0 : children = 1) :
			(BNode<NodeData>::right() == NULL ? children = 1 : children = 2)
			);
		return children;
	}

	//template<typename NodeData> void BNode<NodeData>::printInOrder() {

	//}

	//template<typename NodeData> void BNode<NodeData>::printPreOrder() {

	//}

	//template<typename NodeData> void BNode<NodeData>::printPostOrder() {

	//}

	//template<typename NodeData> void BNode<NodeData>::printLevelOrder() {

	//}

	//template<typename NodeData> void BNode<NodeData>::printVisual() {

	//}

	// base-class virtual functions

	template<typename NodeData> std::string BNode<NodeData>::toString() {
		// override of base-class virtual function
		std::string left = "";
		std::string right = "";
		if (BNode<NodeData>::hasLeftChild()) left = BNode<NodeData>::left()->toString() + " ";
		if (BNode<NodeData>::hasRightChild()) right = " " + BNode<NodeData>::right()->toString();
		return left + std::to_string(BNode<NodeData>::value) + right;
	}


	template<typename NodeData> BNode<NodeData>* BNode<NodeData>::toBinaryNode(Node<NodeData>* node) {
		return (BNode<NodeData>*) node;
	}
}