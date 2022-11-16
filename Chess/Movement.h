#pragma once
#include <vector>

class Movement
{
	bool infiniteSpaces;
	std::vector<std::vector<int>> movementVector;

public:
	Movement();
	Movement(bool infiniteSpaces, std::vector<std::vector<int>> movementVector);

	bool canMoveInfinite();
	std::vector<std::vector<int>> getMovementVector();
};

