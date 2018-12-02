#ifndef __EDGE_H__
#define __EDGE_H__

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Edge {
	public:
	int from = 0;
	int to = 0;
	int cost = 0;
	Edge(int from, int to, int cost) {
		this->from = from;
		this->to = to;
		this->cost = cost;
	}

	void print() {
		// std::cout << this->from << " •--- " << this->cost << " ---> " << this->to << std::endl;
	}
	
	static bool ascendingOrder(Edge *e1, Edge *e2) {
		return e1->cost < e2->cost;
	}

};

#endif