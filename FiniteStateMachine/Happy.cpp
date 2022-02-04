#include "Happy.h"
#include <iostream>

Happy::Happy()
{

}

Happy::~Happy()
{

}

void Happy::run()
{
	std::cout << "You are now HAPPY\n";
}

void Happy::onEnter()
{
	std::cout << "You are now entering the HAPPY state\n";
}

void Happy::onExit()
{
	std::cout << "You are now leaving the HAPPY state\n";
}