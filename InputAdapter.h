#ifndef __INPUTADAPTER_H__
#define __INPUTADAPTER_H__

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Graph.h"

class InputAdapter {
public:
	static int getNumberInput() {
		int number;
		std::cin >> number;
		if (std::cin.fail()) {
			return -1;
		}
		return number;
	}

	std::vector<Graph*> getInput() {
		std::vector<Graph*> campuses;

		//Reading number of campus
		auto campusCount = InputAdapter::getNumberInput();
		// std::cout << std::endl << "Campus count: " << campusCount;

		//Reading each campus
		for (auto campusIndex = 0; campusIndex < campusCount; campusIndex++) {			
			std::vector< std::vector<int> > matrix;

			// std::cout << std::endl << "campus index: " << campusIndex;
			auto routers = InputAdapter::getNumberInput();
			if ( routers < 0 ) {
				continue;
			}
			// std::cout << std::endl << "Routers count: " << routers;

			//Reading cost matrix
			for (auto lineIndex = 0; lineIndex < routers; lineIndex++) {
				std::vector<int> line;
				// std::cout << std::endl;
				for (auto columnIndex = 0; columnIndex < routers; columnIndex++) {
					auto element = InputAdapter::getNumberInput();
					line.push_back(element);
					// std::cout << element << " - ";
				}
				matrix.push_back(line);
			}

			auto campus = new Graph(campusIndex, matrix);
			campuses.push_back(campus);

			//Reading number of 1-order routers
			auto firstOrderRouterCount = InputAdapter::getNumberInput();
			if (firstOrderRouterCount < 0) {
				continue;
			}
			// std::cout << std::endl << "1st order router count: " << firstOrderRouterCount << std::endl;
			for (auto orderIndex = 0; orderIndex < firstOrderRouterCount; orderIndex++) {
				auto identifier = InputAdapter::getNumberInput();
				// std::cout << identifier << " - ";
				campus->firstOrderRouters.push_back(identifier);
			}

			// std::cout << std::endl << "Done with campus number " << campusIndex;
		}
	
		// std::cout << std::endl;
		return campuses;
	}
};

#endif