#pragma once

#include<easyx.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

class Game
{
private:
    bool map[MAP_HEIGHT][MAP_WIDTH]{ 0 };
    int score = 0;
    int gameTime = 0;
public:
    //绘制界面
    void drawView();
    //游戏提示界面
    void drawPrompt();
    //判断满行
    bool checkLine(int line) const;
    //清除满行
    void clearLine();

    //更新游戏时间
    void updateTime();
    //设置map数据
    void setMap(int x, int y, bool v);
    //获取map
    bool getMap(int x, int y);
};