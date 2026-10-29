#pragma once
#include "Observer.h"
#include "Game.h"

class Renderer :
    public Observer
{
    Game& game;
public:
    Renderer(Game& g) : game(g) {}

    void update() override;

    void draw();

};

