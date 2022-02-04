#pragma once
#include "BaseState.h"

class Calm : public BaseState
{
public:
	Calm();
	~Calm();

	void run() override;
	void onEnter() override;
	void onExit() override;
};