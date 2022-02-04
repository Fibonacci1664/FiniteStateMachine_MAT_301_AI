#pragma once
#include "BaseState.h"

class Surprised : public BaseState
{
public:
	Surprised();
	~Surprised();

	void run() override;
	void onEnter() override;
	void onExit() override;
};