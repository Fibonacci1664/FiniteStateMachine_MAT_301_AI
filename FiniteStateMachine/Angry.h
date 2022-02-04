#pragma once
#include "BaseState.h"

class Angry : public BaseState
{
public:
	Angry();
	~Angry();

	void run() override;
	void onEnter() override;
	void onExit() override;
};