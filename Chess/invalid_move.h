#include <exception>
#pragma once
class invalid_move : public std::exception
{
	char* message;
public:
	invalid_move(char* message);
	char* what()
	{
		return message;
	}
};

