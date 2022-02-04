#pragma once

// Abstract base state that CANNOT be instantiated

class BaseState
{

public:
	virtual void run() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

};