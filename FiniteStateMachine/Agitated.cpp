#include "Agitated.h"
#include <iostream>

Agitated::Agitated()
{

}

Agitated::~Agitated()
{

}

void Agitated::run()
{
	std::cout << "You are now AGITATED\n";
}

void Agitated::onEnter()
{
	std::cout << "You are now entering the AGITATED state\n";
}

void Agitated::onExit()
{
	std::cout << "You are now leaving the AGITATED state\n";
}