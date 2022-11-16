#include "Movement.h"

Movement::Movement()
{
	infiniteSpaces = false;
}

Movement::Movement(bool infiniteSpaces, std::vector<std::vector<int>> movementVector)
{
	this->infiniteSpaces = infiniteSpaces;
	this->movementVector = movementVector;
}

bool Movement::canMoveInfinite()
{
	return infiniteSpaces;
}

std::vector<std::vector<int>> Movement::getMovementVector()
{
	return movementVector;
}
