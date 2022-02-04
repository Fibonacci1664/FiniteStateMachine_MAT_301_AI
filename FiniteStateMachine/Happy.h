#pragma once
#include "BaseState.h"

class Happy : public BaseState
{
public:
	Happy();
	~Happy();

	void run() override;
	void onEnter() override;
	void onExit() override;
};