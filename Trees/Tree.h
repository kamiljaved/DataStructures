
#include <vector>
#include <map>

namespace Tree {

	template<typename NodeData> class Tree {

	protected:
		Node<NodeData>* root;

	public:
		// constructors & destructors
		Tree();
		Tree(Node<NodeData>* root);
		Tree(NodeData rootVal);
		virtual ~Tree();

		// getters and setters
		// override in child classes to return a specific child-class node
		virtual Node<NodeData>* getRootNode();

		// utility methods
		
		// level-order list of nodes
		std::vector<Node<NodeData>*> getNodeList();
		std::vector<NodeData> getDataList();

		// in-order, pre-order, post-order make sense only in BT
		
		// calls toString() (in-order string)
		virtual void printTree();

		// returns in-order node-values in string form
		virtual std::string toString();

		// --- > should be in a Tree class
		void printLevelOrder();
		virtual void printVisual(bool ignoreNULL = false);
	
	private: 
		void printVisual(Node<NodeData>* node, int traversal, std::map<int, bool>& td, bool ignoreNULL = false);

	};

	template<typename NodeData> Tree<NodeData>::Tree() {
		root = NULL;
	}	
	
	template<typename NodeData> Tree<NodeData>::Tree(Node<NodeData>* root) {
		this.root = root;
	}

	template<typename NodeData> Tree<NodeData>::Tree(NodeData rootVal) {
		this.root = new Node<NodeData>(rootVal);
	}
	
	template<typename NodeData> Tree<NodeData>::~Tree() {
		std::cout << "Tree Cleanup: deleting root and all subnodes" << std::endl;
		delete root;
	}

	// getters and setters

	template<typename NodeData> Node<NodeData>* Tree<NodeData>::getRootNode() {
		return root;
	}


	// utility methods

	template<typename NodeData> std::string Tree<NodeData>::toString() {
		return root->toString();
	}

	template<typename NodeData> void Tree<NodeData>::printTree() {
		std::cout << root->toString() << std::endl;
	}		
	
	template<typename NodeData> void Tree<NodeData>::printLevelOrder() {

		// if tree empty
		if (Tree<NodeData>::root == NULL) {
			std::cout << "Tree Empty" << std::endl;
			return;
		}

		// current level nodes
		std::vector<Node<NodeData>*> levelNodes;
		levelNodes.push_back(root);
		int level = 0;					// stores info about what level the node was inserted in

		// level-order search for NULL node
		while (!levelNodes.empty()) {

			// which nodes entail this search
			// 0 -> size()
			int levelSize = levelNodes.size();

			std::cout << "[" << level << "]";

			for (int i = 0; i < levelSize; i++) {

				BNode<NodeData>* n = (BNode<NodeData>*) levelNodes.at(i);

				if (n != NULL) {
					std::cout << " " << std::to_string(n->getValue());

					// getSubNodes() returns a "copy" of the vector!
					// equality "=" operator copies right-side vector to left-side vector
					std::vector<Node<NodeData>*> subNodes = n->getSubNodes();

					// push all children to end of vector
					levelNodes.insert(levelNodes.end(), subNodes.begin(), subNodes.end());
				}
				else std::cout << " -";
			}

			// which nodes to remove (level just done)
			// 0 -> levelSize
			levelNodes.erase(levelNodes.begin(), levelNodes.begin() + levelSize);

			level += 1;
			std::cout << std::endl;
		}

		levelNodes.clear();		// not necessary, as called upon leaving scope
	}	


	template<typename NodeData> void Tree<NodeData>::printVisual(bool ignoreNULL) {
		int traversal = 0;
		std::map<int, bool> td;
		// map is passed by reference here
		printVisual(root, traversal, td, ignoreNULL);
	}

	template<typename NodeData> void Tree<NodeData>::printVisual(Node<NodeData>* node, int traversal, std::map<int, bool>& td, bool ignoreNULL) {
		
		
		if (node == NULL) {
			std::cout << "NULL" << std::endl;
			return;
		}

		std::cout << node->getValue() << std::endl;
		traversal += 1;
		std::vector<Node<NodeData>*> subNodes;

		if (ignoreNULL) subNodes = node->getValidSubNodes();
		else subNodes = node->getSubNodes();
		
		int count = subNodes.size();

		for (int i = 0; i < count; i++) {

			td[traversal] = true;
			
			for (int e = 0; e < traversal - 1; e++) {
				if (td[e + 1] == true) std::cout << "|   ";
				else std::cout << "    ";
			}
			if ((i + 1) == count) {
				std::cout << "\\---";
				td[traversal] = false;
			}
			else {
				std::cout << "|---";
			}

			printVisual(subNodes.at(i), traversal, td, ignoreNULL);
		}
		traversal -= 1;

	}

}