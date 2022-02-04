#pragma once
#include "BaseState.h"

class Alert : public BaseState
{
public:
	Alert();
	~Alert();

	void run() override;
	void onEnter() override;
	void onExit() override;
};