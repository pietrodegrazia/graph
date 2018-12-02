#ifndef __NODE_H__
#define __NODE_H__

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Edge.h"

class Node {
	public:
	Edge* mstEdge = NULL;
	int identifier;
	std::vector<Edge*> edges;
	

	Node(int identifier, std::vector<int> line) {
		this->identifier = identifier;
		auto i = 0;
		std::for_each(line.begin(), line.end(), [&i, this](int cost) {
			i++;
			if (cost > 0) {
				this->edges.push_back(new Edge(this->identifier,i, cost));
			}
    	});
    	// std::sort(this->edges.begin(), this->edges.end(), Edge::ascendingOrder);
	}

	void print() {
		// std::cout << "Node identifier: " << this->identifier << std::endl;
		// std::cout << "(A)";
		if (this->mstEdge != NULL) {
			// std::cout << "MST Edge: ";
			this->mstEdge->print();
		}
		// std::cout << "(B)";
		std::for_each(this->edges.begin(), this->edges.end(), [](Edge *edge) {
			// std::cout << "(C)";
    		edge->print();
    	});
	}

	Edge* cheapestEdgeExcludingNodes(std::vector<Node*> excludingNodes, std::vector<int> firstOrderRouterIds) {
		// std::cout << std::endl << "cheapestEdgeExcludingNodes called" << std::endl;
		Edge *cheapest = NULL;
		std::vector<int> excludingIds = firstOrderRouterIds;
		std::for_each(excludingNodes.begin(), excludingNodes.end(), [&excludingIds](Node *node) {
			excludingIds.push_back(node->identifier);
			// std::cout << std::endl << "Exclude id: " << node->identifier << std::endl;
		});
		std::for_each(this->edges.begin(), this->edges.end(), [&excludingIds, &cheapest](Edge *edge) {
			// std::cout << std::endl << "Testing edge" << std::endl;
			edge->print();
			if(std::find(excludingIds.begin(), excludingIds.end(), edge->to) != excludingIds.end()) {
			    // std::cout << "Should be ignored: " << edge->to << std::endl;
			} else {
			    // std::cout << "Should be considered: " << edge->to << std::endl;
			    if (cheapest == NULL || cheapest->cost > edge->cost) {
			    	// std::cout << "new cheapest" << std::endl;
			    	cheapest = edge;
			    }
			}
		});
		return cheapest;
	}
};

#endif