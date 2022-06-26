#pragma once

#include <iostream>
#include "ishared.h"

class StatVersion002 : public ishared
{
public:
	StatVersion002() = default;
	~StatVersion002() = default;

	void ShowStats() override;
	void NewFunctionality();
};
