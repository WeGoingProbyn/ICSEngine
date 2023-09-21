#include "Game.h"

#include <Core/Debugger/Logger.h>

bool Game::Startup()
{
	return true;
}

bool Game::Update(float deltaTime)
{
	//ICS_TRACE("Game update called")
	return true;
}

bool Game::Render(float deltaTime)
{
	ICS_TRACE("Game render called")
	return true;
}
