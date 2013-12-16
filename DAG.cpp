// DAG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <sstream>
#include "DAGNode.h"

// Test with perfect DAG
void topologicalSortTest1();
void traverseTest3();

// Test if a DAG is wrong and has a cylce
void topologicalSortTest2();
void traverseTest4();


int _tmain(int argc, _TCHAR* argv[])
{
	topologicalSortTest1();
	topologicalSortTest2();	
	traverseTest3();
	traverseTest4();
	return 0;
}

// Should process perfectly fine as input is a perfect DAG...
void topologicalSortTest1()
{
	printf("Performing Test: %s \n","topologicalSortTest1");

	Node node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9);

	node0.addDependent(&node1);
	node0.addDependent(&node2);

	node1.addDependent(&node3);
	node2.addDependent(&node3);

	node3.addDependent(&node4);

	node4.addDependent(&node5);
	node8.addDependent(&node5);

	node3.addDependent(&node6);
	node4.addDependent(&node6);

	node3.addDependent(&node7);
	node4.addDependent(&node7);

	node6.addDependent(&node8);
	node7.addDependent(&node8);

	node1.addDependent(&node9);
	node8.addDependent(&node9);

	std::vector<Node*> unsortedNodes;
	unsortedNodes.push_back(&node5);
	unsortedNodes.push_back(&node3);
	unsortedNodes.push_back(&node0);
	unsortedNodes.push_back(&node6);
	unsortedNodes.push_back(&node8);
	unsortedNodes.push_back(&node1);
	unsortedNodes.push_back(&node4);
	unsortedNodes.push_back(&node2);
	unsortedNodes.push_back(&node9);
	unsortedNodes.push_back(&node7);

	try
	{
		std::vector<Node*> topoSort = topologicalSort(unsortedNodes);
		std::stringstream output;

		for(int i = 0 ; i < topoSort.size() ; i++)
		{
			output << topoSort[i]->getID();
		}

		if(output.str() == "0123467859")
			printf("Result : PASSED\n");
		else
			printf("Result : FAILED\n");
	}
	catch(...)
	{
		printf("Result : FAILED\n");
	}	
}

// Input data constains cycle so topological sort should throw exception
void topologicalSortTest2()
{
	printf("Performing Test: %s \n","topologicalSortTest2");

	Node node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9);

	node0.addDependent(&node1);
	node0.addDependent(&node2);

	node1.addDependent(&node3);
	node2.addDependent(&node3);

	node3.addDependent(&node4);
	//Putting a cycle here
	node6.addDependent(&node2);

	node4.addDependent(&node5);
	node8.addDependent(&node5);

	node3.addDependent(&node6);
	node4.addDependent(&node6);

	node3.addDependent(&node7);
	node4.addDependent(&node7);

	node6.addDependent(&node8);
	node7.addDependent(&node8);

	node1.addDependent(&node9);
	node8.addDependent(&node9);

	std::vector<Node*> unsortedNodes;

	unsortedNodes.push_back(&node5);
	unsortedNodes.push_back(&node3);
	unsortedNodes.push_back(&node0);
	unsortedNodes.push_back(&node8);
	unsortedNodes.push_back(&node6);
	unsortedNodes.push_back(&node9);
	unsortedNodes.push_back(&node1);
	unsortedNodes.push_back(&node4);
	unsortedNodes.push_back(&node7);
	unsortedNodes.push_back(&node2);

	try
	{
		std::vector<Node*> topoSort = topologicalSort(unsortedNodes);
		printf("Result : FAILED\n");
	}
	catch(char* err)
	{
		printf("Result : PASSED\n");
	}
	catch(...)
	{
		printf("Result : FAILED\n");
	}
}

// Function that prints the id of node.
std::stringstream visitTest;

void Visited( const Node& node )
{
	visitTest << node.getID();
	printf("%d  ", node.getID());
}


void traverseTest3()
{
	printf("Performing Test: %s \n","traverseTest3");

	Node node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9);

	node0.addDependent(&node1);
	node0.addDependent(&node2);

	node1.addDependent(&node3);
	node2.addDependent(&node3);

	node3.addDependent(&node4);

	node4.addDependent(&node5);
	node8.addDependent(&node5);

	node3.addDependent(&node6);
	node4.addDependent(&node6);

	node3.addDependent(&node7);
	node4.addDependent(&node7);

	node6.addDependent(&node8);
	node7.addDependent(&node8);

	node1.addDependent(&node9);
	node8.addDependent(&node9);

	try
	{
		visitTest.clear();
		traverse(node0, Visited);
		if(visitTest.str() == "0123946758")
			printf("Result : PASSED\n");
		else
			printf("Result : FAILED\n");
	}
	catch(...)
	{
		printf("Result : FAILED\n");
	}	
}

void traverseTest4()
{
	printf("Performing Test: %s \n","traverseTest4");

	Node node0(0), node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7), node8(8), node9(9);

	node0.addDependent(&node1);
	node0.addDependent(&node2);

	node1.addDependent(&node3);
	node2.addDependent(&node3);

	node3.addDependent(&node4);
	//Putting a cycle here
	node6.addDependent(&node2);

	node4.addDependent(&node5);
	node8.addDependent(&node5);

	node3.addDependent(&node6);
	node4.addDependent(&node6);

	node3.addDependent(&node7);
	node4.addDependent(&node7);

	node6.addDependent(&node8);
	node7.addDependent(&node8);

	node1.addDependent(&node9);
	node8.addDependent(&node9);

	try
	{
		visitTest.clear();
		traverse(node0, Visited);
		if(visitTest.str() == "0123946758")
			printf("Result : PASSED\n");
		else
			printf("Result : FAILED\n");
	}
	catch(...)
	{
		printf("Result : FAILED\n");
	}
}