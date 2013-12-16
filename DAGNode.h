// DAGNode.cpp
#include <set>
#include <vector>

class Node
{
	int m_inDegree;
    int m_id;
	std::vector<Node*> m_dependents;

public:
    explicit Node( int id )
	{
		m_id = id;
		m_inDegree = 0;
	}

    void addDependent( Node* node )
	{
		// adding dependent in the given vector
		m_dependents.push_back(node);

		// incrementing the in degree of added dependency
		node->m_inDegree++;	
	}

	// used to know is the node visited or not.
	int currentTraverseSeed;

	int getID()const { return m_id; }

	int getInDegree()const { return m_inDegree ; }

	int getOutDegree()const { return m_dependents.size(); }

	Node* getDependent(unsigned int index)
	{
		if(index >= m_dependents.size())
			return NULL;

		return m_dependents[index];
	}
};

typedef void (*VisitFn)( const Node& node );
void traverse( const Node& root, VisitFn visit );

// Node to store degree and node data to be used as Topological Sort.
struct TopoSortNode
{
	int m_degree;
	Node* m_node;
	TopoSortNode()
	{
		m_degree = 0;
		m_node = NULL;
	}

	TopoSortNode(int degree, Node* node)
	{
		m_degree = degree;
		m_node = node;
	}
};

// Refer Indegree topological sort for documentation.
// input - list of nodes in arbitary order
// output - list sorted such that all the dependent nodes are before the node
std::vector<Node*> topologicalSort(std::vector<Node*> input)
{
	// vector to store the list...
	std::vector<Node*> topoList;

	// Queue to store the zero degree nodes to perform topological sort
	std::queue<Node*> Q;
	int nodeCount = input.size();

	if(nodeCount > 0)
	{
		topoList.resize(nodeCount);

		// Vector that is working as a unordered_map... if possible to use C++11 then use unordered_map
		std::vector<TopoSortNode> inDegree;

		// Pushing all nodes with indegree 0 to Queue and storing the indegree in temporary vector of degrees.
		for(int n = 0; n < nodeCount; n++) 
		{			
			Node* node = input[n];
			if(node->getInDegree() == 0) 
				Q.push(node);


			// implementation to store node at it's id so that we can access it with constant time
			if(inDegree.size() <= node->getID())
				inDegree.resize(node->getID() + 1);
			inDegree[node->getID()].m_degree = node->getInDegree();
			inDegree[node->getID()].m_node = node;
		}

		// Counter to store value final output at it's index
		int insertIndex = 0;

		// Continue untill Q is not empty.
		while( !Q.empty()) 
		{ 
			// get the top node in the queue and push to the output list
			Node* frontNode = Q.front(); 
			Q.pop();
			topoList[insertIndex] = frontNode;
			insertIndex++;

			// get all the dependent of the current node and decrement the indegree count.
			int index = 0;
			Node *dependent = frontNode->getDependent(index);
			while(dependent)
			{
				// decrement the degree
				inDegree[dependent->getID()].m_degree--;

				// push the node to Queue if the indegree has become 0.
				if(inDegree[dependent->getID()].m_degree == 0)
					Q.push(dependent);
				index++;

				dependent = frontNode->getDependent(index);
			}
		}

		// Queue got empty without sorting all elements as there was a cycle in the sent vector of nodes.
		if(insertIndex < nodeCount)
		{
			topoList.clear();
			throw "List of Node passed has a cycle";
		}
	}
	return topoList;
}



// Performing Breath First Search Traversal
void traverse( const Node& root, VisitFn visit )
{
	if(visit != NULL)
		visit(root);

	Node* rootPtr = (Node*)&root;
	std::queue<Node*> Q;
	Q.push(rootPtr);

	// List the node id already visited
	std::set<int> visited;

	// Until Q is empty
	while(!Q.empty())
	{
		// Pop the top on queue
		Node* frontNode = Q.front();
		Q.pop();

		// get all edges and push to queue
		int index = 0;
		Node* dependent = frontNode->getDependent(index);
		while(dependent)
		{
			// if inDegree is 1 then we don't need to check for revisit. 
			// If indegree is more than one, only then node can be visited more than once and we check if it is visited earlier
			// If not visited only then we proceed. We also restrict the adding of visited node again.
			if((dependent->getInDegree() <= 1) || (dependent->getInDegree() > 1 && visited.find(dependent->getID()) == visited.end()))
			{
				if(visit != NULL)
					visit(*dependent);

				Q.push(dependent);

				if(dependent->getInDegree() > 1)
					visited.insert(dependent->getID());
			}

			index++;
			dependent = frontNode->getDependent(index);
		}
	}
}