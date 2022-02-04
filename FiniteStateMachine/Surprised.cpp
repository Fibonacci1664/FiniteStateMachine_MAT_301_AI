#include "Surprised.h"
#include <iostream>

Surprised::Surprised()
{

}

Surprised::~Surprised()
{

}

void Surprised::run()
{
	std::cout << "You are now SURPRISED\n";
}

void Surprised::onEnter()
{
	std::cout << "You are now entering the SURPRISED state\n";
}

void Surprised::onExit()
{
	std::cout << "You are now leaving the SURPRISED state\n";
}