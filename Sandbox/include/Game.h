#pragma once

#include <Application/Application.h>
#include <Application/UserInterface.h>

class Game : public UserInterface
{
public:
	Game() {};

	bool Startup() override;
	bool Update(float deltaTime) override;
	bool Render(float deltaTime) override;
};