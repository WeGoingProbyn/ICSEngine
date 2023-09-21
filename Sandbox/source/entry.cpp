#include <Core/Application/entry.h>
#include "Game.h"

UserInterface& GetUserInstance() { static Game game; return game; }