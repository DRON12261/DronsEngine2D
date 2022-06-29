#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "Math.h"

namespace DronsEngine{
    class Game{
    private:
        sf::CircleShape *shape;
        sf::CircleShape *mouseShape;

        std::string gameTitle = "";
        int gameWindowWidth = 0;
        int gameWindowHeight = 0;
        sf::RenderWindow *gameWindow;
        sf::Clock *gameTime;
        sf::Time elapsedTime;
        sf::Time idleLag;
        sf::Time physicsLag;
        int FPSCap = 0;
        int PhysicsFPSCap = 0;
        sf::Time msPerIdleFrame;
        sf::Time msPerPhysicsFrame;

        int init();
        int handleEvents();
        int physicsUpdate();
        int update();
        int render();

    public:
        Game(std::string gameTitle, int gameWindowWidth, int gameWindowHeight);
        int run();
    };
}

#endif // GAME_H
