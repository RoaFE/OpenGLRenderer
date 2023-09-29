#include "Log.h"
#include <iostream>
void Log::Message(std::string input)
{
	std::cout << input << std::endl;
}


void Log::Error(std::string input)
{
	Message("Error:" + input);
}
