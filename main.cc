#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "InputAdapter.h"

int main() {
	auto input = new InputAdapter();
	auto campuses = input->getInput();
	std::for_each(campuses.begin(), campuses.end(), [](Graph *campus) {
		campus->getMST();
	});
}