#include"General_utility.h"
#include<iostream>

void Log(const std::string message, const std::source_location loc)
{
	std::cout << "ERROR\n" << message << "\nin: "
		<< loc.file_name() << "\nAt or before line: " << loc.line() << "\n";
}