#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Node.h"
#include "Edge.h"

class Graph {
	public:
	int identifier;
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	std::vector<int> firstOrderRouters;
	
	Graph(int identifier) {
		this->identifier = identifier;
	}

	Graph(int identifier, std::vector<std::vector<int>> matrix) {
		this->identifier = identifier;
		auto i = 0;
		std::for_each(matrix.begin(), matrix.end(), [&i, this](std::vector<int> line) {
			i++;
    		this->nodes.push_back(new Node(i, line));
    	});
	}

	Edge* cheapestEdgeFromNode(Node* node) {
		Edge* edge = NULL;
		std::for_each(node->edges.begin(), node->edges.end(), [&node, this, &edge](Edge* possibleEdge) {
    		if (!this->isFirstOrder(possibleEdge->to)) {
    			if (edge == NULL || edge->cost > possibleEdge->cost) {
    				edge = possibleEdge;	
    			}
    		}
    	});
    	return edge;
	}

	Node* getNode(int id) {
		Node* node = NULL;
		std::for_each(this->nodes.begin(), this->nodes.end(), [&node, this, id](Node* possibleNode) {
    		if (possibleNode->identifier == id) {
    			node = possibleNode;
    		}
    	});
    	return node;
	}

	std::vector<Node*> higherOrderNodes() {
		std::vector<Node*> nodes;
		std::for_each(this->nodes.begin(), this->nodes.end(), [&nodes, this](Node* node) {
    		if (!this->isFirstOrder(node->identifier)) {
    			nodes.push_back(node);
    		}
    	});
    	return nodes;
	}

	bool isFirstOrder(int routerId) {
		auto foundId = false;
		std::for_each(this->firstOrderRouters.begin(), this->firstOrderRouters.end(), [routerId, &foundId](int id) {
    		if (id == routerId) {
    			foundId = true;
    		}
    	});
    	return foundId;
	}

	void print() {
		// std::cout << std::endl << "Graph identifier: " << this->identifier << std::endl;
		// std::for_each(this->nodes.begin(), this->nodes.end(), [](Node *node) {
  //   		node->print();
  //   	});
  //   	std::cout << std::endl << "Graph identifier(EDGES) " << this->identifier << std::endl;
  //   	std::for_each(this->edges.begin(), this->edges.end(), [](Edge *edge) {
  //   		edge->print();
  //   	});
		// std::cout << std::endl << "Graph first order routers " << this->identifier << std::endl;
  //   	std::for_each(this->firstOrderRouters.begin(), this->firstOrderRouters.end(), [](int id) {
  //   		std::cout << " ; " << id;
  //   	});
  //   	std::cout << std::endl;
	}

	void printCost() {
		auto cost = 0;
		std::for_each(this->edges.begin(), this->edges.end(), [&cost](Edge *edge) {
    		cost += edge->cost;
    	});
		std::cout << "Campus "<< this->identifier << ": " << cost;
		std::cout << std::endl;
	}

	void getMST() {
		// std::cout << std::endl << "Generating MST" << std::endl;

		auto remaining = this->higherOrderNodes();
		auto mst = Graph(this->identifier+1);

		//Pick first node and it's cheapest edge to start MST
		auto node = remaining.front();

		//remove the node we picked from the remaining nodes to be added later
		remaining.erase(remaining.begin());

		//define its mst edge as its cheapest edge
		node->mstEdge = this->cheapestEdgeFromNode(node);
		//add this edge to our mst's edges
		mst.edges.push_back(this->cheapestEdgeFromNode(node));
		//add this node to our mst's nodes
		mst.nodes.push_back(node);
		
		{
			//Find the node the selected edge connects it to and add that node to the MST as well
			auto otherNodeId = node->mstEdge->to;
			auto i = 0;
			//look for the node in the remaining nodes
			std::for_each(remaining.begin(), remaining.end(), [&i, &mst, &remaining, &otherNodeId](Node *node) {
				if (node->identifier == otherNodeId) {
					//add it to our mst's nodes
					mst.nodes.push_back(node);
					//remove it from the remaining nodes
					remaining.erase(remaining.begin() + i);
				}
				i++;
	    	});
	    }

	    //while there are nodes to be added to our mst
		while(remaining.size() > 0) {
			Edge* cheapest = NULL;
			Node* originatingNode = NULL;

			//for each node already in our mst
			std::for_each(mst.nodes.begin(), mst.nodes.end(), [&mst, &cheapest, &originatingNode, this](Node *node) {
				//we will look for their cheapest edge not in the mst and that doesn't connect to a node in the mst
				auto candidateEdge = node->cheapestEdgeExcludingNodes(mst.nodes, this->firstOrderRouters);
				if (candidateEdge == NULL || this->isFirstOrder(candidateEdge->to)) {
					return;
				}
				// std::cout << std::endl << "Candidate Found: ";
				candidateEdge->print();
				//if this node is the cheapest we found so far
				if (cheapest == NULL || (cheapest->cost > candidateEdge->cost) ) {
					// std::cout << std::endl << "NEW cheapest\n";
					cheapest = candidateEdge;
					originatingNode = node;
				}
    		});
    		//assign the edge as the node's mst edge 
    		originatingNode->mstEdge = cheapest;
    		//add the edge to our mst
    		mst.edges.push_back(cheapest);
    		// std::cout << std::endl << "New edge Found: ";
			// cheapest->print();
			
			{
				//Find the node the selected edge connects it to and add that node to the MST as well
				auto otherNodeId = cheapest->to;
				auto i = 0;
				std::for_each(remaining.begin(), remaining.end(), [&i, &mst, &remaining, &otherNodeId](Node *node) {
					if (node->identifier == otherNodeId) {
						mst.nodes.push_back(node);
						remaining.erase(remaining.begin() + i);
					}
					i++;
		    	});
	    	}
		}

		//for each first order router, we have to get their cheapest edge
		//(excluding edges to other first order routers) and add them to our mst

		std::for_each(this->firstOrderRouters.begin(), this->firstOrderRouters.end(), [&mst, this](int id) {
			auto node = this->getNode(id);
			auto edge = this->cheapestEdgeFromNode(node);
			mst.nodes.push_back(node);
			mst.edges.push_back(edge);
	    });

		// mst.print();
		mst.printCost();
		
		// return mst;
	}
};

#endif