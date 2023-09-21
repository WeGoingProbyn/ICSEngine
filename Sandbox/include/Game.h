#pragma once

#include <Core/Application/Application.h>
#include <Core/Application/UserInterface.h>

class Game : public UserInterface
{
public:
	Game() {};

	bool Startup() override;
	bool Update(float deltaTime) override;
	bool Render(float deltaTime) override;
};