#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// With Visual C++ (and most other C++ compilers) template definitions need to go completely 
// in header files so that the definition is available everywhere that the template is referenced.
// 
// Templated classesand functions are not instantiated until they are used, typically in a 
// separate.cpp file(e.g.the program source).When the template is used, the compiler needs 
// the full code for that function to be able to build the correct function with the appropriate type.
// However, in this case the code for that function is detailed in the template's source file and 
// hence unavailable.
// As a result of all this the compiler just assumes that it's defined elsewhere and only inserts the 
// call to the templated function. When it comes to compile the template's source file, 
// the specific template type that is being used in the program source isn't used there so it still 
// won't generate the code required for the function.This results in the unresolved external symbol.
//
// The solutions available for this are to :
//		include the full definition of the member function in the template's header file 
//		and not have a source file for the template


namespace Tree {

	template<typename NodeData> class Node {

	protected:
		std::vector<Node<NodeData>*> subNodes;
		NodeData value;

	public:
		// constructors and destructors
		Node(NodeData val);		// value = val, subNodes = empty
		Node(NodeData val, std::vector<Node<NodeData>*> subNodes);

		// set to virtual so the most-derived destructor is called
		// in case of base-pointer-to-child
		// > base destructor is still called, but after child one
		// > if not virtual and you delete base-pointer-to-child,
		//   only base class destructor called
		virtual ~Node();

		// getters and setters
		std::vector<Node*> getSubNodes();
		std::vector<Node*> getValidSubNodes();
		int getSubNodeCount();
		Node* getSubNode(int index);
		NodeData getValue();

		void setSubNodes(std::vector<Node*> nodes);
		void setSubNode(int index, Node<NodeData>* node);
		void addSubNode(Node* node);
		void removeSubNode(int index);
		Node popSubNode();
		void setValue(NodeData value);

		// utility methods
		virtual std::string toString();

		int getNodeLevel(Node<NodeData>* root);		// from root to node n
		int getNodeHeight();						// from node n to lowest-leaf

		// class witha virtual function can be instantiated,
		// but a class with a pure virtual function (void func(args)=0)
		// cannot be instantiated
	};


	//
	// class function definitions
	//

	template<typename NodeData> Node<NodeData>::Node(NodeData val) {
		value = val;
	}

	template<typename NodeData> Node<NodeData>::Node(NodeData val, std::vector<Node<NodeData>*> subNodes) {
		value = val;
		Node<NodeData>::subNodes = subNodes;
	}

	// check if needed or not
	// desired behaviour: upon deletion of node, 
	// all its subnodes should also be destroyed (destructor called) and so on
	template<typename NodeData> Node<NodeData>::~Node() {
		std::cout << "Deleting Node with value " << getValue()
			<< " and " << subNodes.size() << " sub-nodes." << std::endl;
		for (Node<NodeData>* p : subNodes) {
			delete p;
		}
		subNodes.clear();
	}

	// getters and setters

	template<typename NodeData> std::vector<Node<NodeData>*> Node<NodeData>::getSubNodes() {
		return Node<NodeData>::subNodes;
	}	
	
	template<typename NodeData> std::vector<Node<NodeData>*> Node<NodeData>::getValidSubNodes() {
		std::vector<Node<NodeData>*> validSubNodes;
		std::copy_if(
			subNodes.begin(), subNodes.end(), 
			std::back_inserter(validSubNodes),
			[](Node<NodeData>* n) {
				return n != NULL; 
			}
		);
		return validSubNodes;
	}

	template<typename NodeData> int Node<NodeData>::getSubNodeCount() {
		return Node<NodeData>::subNodes.size();
	}

	template<typename NodeData> Node<NodeData>* Node<NodeData>::getSubNode(int index) {
		return Node<NodeData>::subNodes.at(index);
	}

	template<typename NodeData> NodeData Node<NodeData>::getValue() {
		return Node<NodeData>::value;
	}

	template<typename NodeData> void Node<NodeData>::setSubNodes(std::vector<Node<NodeData>*> nodes) {
		for (Node<NodeData>* p : subNodes) {
			delete p;
		}
		subNodes.clear();
		subNodes = nodes;
	}

	template<typename NodeData> void Node<NodeData>::setSubNode(int index, Node<NodeData>* node) {
		delete subNodes.at(index);
		subNodes.at(index) = node;
	}

	template<typename NodeData> void Node<NodeData>::addSubNode(Node<NodeData>* node) {
		subNodes.push_back(node);
	}

	// O(n) time complexity (to maintain order of nodes)
	template<typename NodeData> void Node<NodeData>::removeSubNode(int index) {
		if (index < subNodes.size())
		{
			// C++ language guarantees that delete p will do nothing if p is null
			delete subNodes.at(index);
			subNodes.erase(subNodes.begin() + index);
		}
	}

	template<typename NodeData> Node<NodeData> Node<NodeData>::popSubNode() {
		if (subNodes.empty()) return NULL;
		Node lastNode = subNodes.back();		// back/last element
		subNodes.pop_back();					// no return. undefined behaviour on empty vector
		delete lastNode;
		return lastNode;
	}

	template<typename NodeData> void Node<NodeData>::setValue(NodeData value) {
		Node<NodeData>::value = value;
	}

	template<typename NodeData> std::string Node<NodeData>::toString() {
		// do something
		// return level order tree string?

		return "";
	}

	template<typename NodeData> int Node<NodeData>::getNodeLevel(Node<NodeData>* root) {
		
		// current level nodes
		std::vector<Node<NodeData>*> levelNodes;
		int level = 0;
		levelNodes.push_back(root);

		// not like BFS
		while (!levelNodes.empty()) {

			
			// which nodes entail this search
			// 0 -> size()
			int levelSize = levelNodes.size();

			for (int i = 0; i < levelSize; i++) {

				Node<NodeData>* n = levelNodes.at(i);
				
				if (n == NULL) continue;

				// compare pointer with self address?
				if (n == this) {
					return level;
				}

				// push all children to end of vector
				levelNodes.insert(levelNodes.end(), n->subNodes.begin(), n->subNodes.end());
			}

			// which nodes to remove (level just done)
			// 0 -> levelSize
			levelNodes.erase(levelNodes.begin(), levelNodes.begin() + levelSize);

			level += 1;
		}

		levelNodes.clear();		// not necessary, as called upon leaving scope

		return NULL;
	}
}