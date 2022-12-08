#include <exception>
#include <iostream>
#pragma once

// This exception is thrown when a move is invalid
class invalid_move : public std::exception
{
	std::string message;
public:
	invalid_move(std::string message);

	std::string what()
	{
		return message;
	}
};

