#pragma once

#include <iostream>
#include "ishared.h"

class StatVersion001 : public ishared
{
public:
	StatVersion001() = default;
	~StatVersion001() = default;

	void ShowStats() override;
};
