#include "Alert.h"
#include <iostream>

Alert::Alert()
{

}

Alert::~Alert()
{

}

void Alert::run()
{
	std::cout << "You are now ALERT\n";
}

void Alert::onEnter()
{
	std::cout << "You are now entering the ALERT state\n";
}

void Alert::onExit()
{
	std::cout << "You are now leaving the ALERT state\n";
}