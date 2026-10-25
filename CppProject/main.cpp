#include "graphics.h"
#include "game.h"
#include "config.h"


void update(float dt)
{
    Game::getInstance().update(dt);
}

void draw()
{
    graphics::Brush br;
    br.fill_color[0] = br.fill_color[1] = br.fill_color[2] = 0.95f;
    graphics::drawRect(
        WINDOW_WIDTH / 2,
        WINDOW_HEIGHT / 2,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        br
    );
    Game::getInstance().draw();
}

int main()
{
    

    graphics::createWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "CppProject");
    Game::getInstance().init();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::startMessageLoop();

    return 0;
}



