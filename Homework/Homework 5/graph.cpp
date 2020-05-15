/*
	Name: Humza Salman
	NET ID: MHS180007
	Name: Zach Foster
	NET ID: ZWF180000
	Name: Ryan Radloff
	NET ID: RJR180002
*/

#include "graph.h"

void graph::dfsTraversal(int n, std::vector<bool>& visited)
{
	visited[n] = true;

	for (int i : adjList[n]) {
		if (!visited[i])
			dfsTraversal(i, visited);
	}
}

bool graph::isConnected()
{
	std::vector<bool> visited(totalNodes+1);
	for (int i = 0; i < totalNodes; i++) {
		visited[i] = false;
	}
	visited[0] = true;
	dfsTraversal(1, visited);
	for (int i = 0; i < totalNodes; i++) {
		if (!visited[i])
			return false;
	}
	return true;
}

bool graph::isBipartite(int vertex)
{
	std::vector<int> colorValues(totalNodes + 1);
	for (int i = 0; i < colorValues.size(); i++) {
		colorValues[i] = -1;
	}
	std::queue<int> q;
	q.push(vertex);
	colorValues[vertex] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int neighbor : adjList[current]) {
			if (colorValues[neighbor] == -1) {
				if (colorValues[current] == 1)
					colorValues[neighbor] = -1;
				else
					colorValues[neighbor] = 1;
				q.push(neighbor);
			}
			if (colorValues[neighbor] != -1 && colorValues[neighbor] == colorValues[current])
				return false;
		}
	}
	return true;
}

void graph::createGraph(std::string filename)
{
	std::ifstream input(filename);
	input >> totalNodes;
	while (!input.eof()) {
		std::string line;
		int vertex;
		input >> vertex;
		std::getline(input, line);

		for (char c : line) {
			if (c != ' ') {
				int n = c - 48;
				adjList[vertex].push_back(n);
				std::cout << "";
			}
		}
	}
}

void graph::print() {
	for (int i = 1; i <= totalNodes; i++) {
		std::cout << i << ":\t";
		
		for (int n : adjList[i])
			std::cout << n << " ";
		std::cout << "\n";
	}
}