#include "EmptyPiece.h"

EmptyPiece::EmptyPiece()
{
	empty = true;
	color = -1;
	displayedChar = ' ';
}

Movement EmptyPiece::move()
{
	return Movement();
}
