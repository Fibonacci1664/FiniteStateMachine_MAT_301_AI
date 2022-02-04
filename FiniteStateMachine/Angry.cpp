#include "Angry.h"
#include <iostream>

Angry::Angry()
{

}

Angry::~Angry()
{

}

void Angry::run()
{
	std::cout << "You are now ANGRY\n";
}

void Angry::onEnter()
{
	std::cout << "You are now entering the ANGRY state\n";
}

void Angry::onExit()
{
	std::cout << "You are now leaving the ANGRY state\n";
}