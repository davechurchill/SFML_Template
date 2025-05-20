#include "GameEngine.hpp"
#include "Scene_Grid.h"

#include <sstream>
#include <iostream>

int main()
{
    GameEngine engine;
    engine.changeScene<Scene_Grid>("Grid");
    engine.run();

    return 0;
}

