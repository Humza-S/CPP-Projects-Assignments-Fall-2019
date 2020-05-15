/*
	Name: Humza Salman
	NET ID: MHS180007
	Name: Zach Foster
	NET ID: ZWF180000
	Name: Ryan Radloff
	NET ID: RJR180002
*/

#pragma once
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

class graph
{
	private:
		std::list<int>* adjList;
		int totalNodes = 0;
		void dfsTraversal(int n, std::vector<bool>& visited);
	public:
		graph() {
			adjList = new std::list<int>[10];
		}

		graph(const int& size) {
			adjList = new std::list<int>[size];
		}

		bool isEmpty() { return adjList->empty(); };
		bool isConnected();
		bool isBipartite(int vertex);

		void createGraph(std::string filename);
		void print();
};

