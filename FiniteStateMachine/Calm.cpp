#include "Calm.h"
#include <iostream>

Calm::Calm()
{

}

Calm::~Calm()
{

}

void Calm::run()
{
	std::cout << "You are now CALM\n";
}

void Calm::onEnter()
{
	std::cout << "You are now entering the CALM state\n";
}

void Calm::onExit()
{
	std::cout << "You are now leaving the CALM state\n";
}
