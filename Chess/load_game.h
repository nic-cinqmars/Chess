#include <exception>
#include <iostream>
#pragma once

// This exception is thrown when a move is invalid
class load_game : public std::exception
{
	std::string message;
public:
	load_game();

	std::string what()
	{
		return message;
	}
};
