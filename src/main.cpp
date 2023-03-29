#include "GameEngine.h"
#include "Scene_Grid.h"

#include <sstream>
#include <iostream>

int main()
{
    GameEngine engine;
    engine.changeScene("Grid", std::make_shared<Scene_Grid>(&engine));
    engine.run();

    return 0;
}

