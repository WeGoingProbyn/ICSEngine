#pragma once

#include <Application/Application.h>

class Game : public Application
{
public:
	Game() {};

	bool Update(float deltaTime) override;
};