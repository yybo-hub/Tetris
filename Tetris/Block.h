#pragma once

#include"Game.h"

class Block
{
private:
    int x, y, type;
    COLORREF color;
    Game& game;
    static bool blockData[7][4][4];
    bool curBlockData[4][4];
    bool direct;
public:
    Block(Game& game, int x = (MAP_WIDTH - 4) / 2, int y = 0);

    bool move(int direct = 0);

    void draw();

    void clear();

    void addMap();
    //falseÎª×ó£¬trueÎªÓÒ
    void rotate();

    bool checkCollision()const;

    static void generateBlockData();

    void setPos(int x = (MAP_WIDTH - 4) / 2, int Y = 0);

    VOID randType();

    void operator=(const Block& block);
};