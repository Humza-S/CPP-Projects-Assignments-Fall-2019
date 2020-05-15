/*
	Name: Humza Salman
	NET ID: MHS180007
	Name: Zach Foster
	NET ID: ZWF180000
	Name: Ryan Radloff
	NET ID: RJR180002
*/

#include <iostream>
#include "graph.h"

int main()
{
	graph* g = new graph();
	std::cout << std::boolalpha;
	std::cout << "empty? " << g->isEmpty() << "\n";
	g->createGraph("graph1.txt");
	g->print();
	std::cout << "connected graph? " << g->isConnected();
	std::cout << "\nbipartite graph? " << g->isBipartite(1);
	delete g;
	std::cout << "\n-----------------------------------------------------------\n";
	g = new graph();
	std::cout << "empty? " << g->isEmpty() << "\n";
	g->createGraph("graph2.txt");
	g->print();
	std::cout << "connected graph? " << g->isConnected();
	std::cout << "\nbipartite graph? " << g->isBipartite(1);
}
