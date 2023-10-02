#pragma once

#include <Application/Application.h>

class Game : public Application
{
public:
	Game() {};

	bool Update(Clock::Time& delta_time) override;
};