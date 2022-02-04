#pragma once
#include "BaseState.h"

class Agitated : public BaseState
{
public:
	Agitated();
	~Agitated();

	void run() override;
	void onEnter() override;
	void onExit() override;
};