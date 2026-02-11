#include "Game.h"
void Game::drawView()
{
    //绘制边框
    roundrect(10, 10, 340, 430, 10, 10);
    rectangle(20, 20, 220, 420);

    //绘制游戏区域
    setfillcolor(LIGHTCYAN);
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            if (map[j][i])
            {
                int left = 20 + 20 * i;
                int top = 20 + 20 * j;

                fillrectangle(left, top, left + 20, top + 20);
            }
        }
    }
}

void Game::drawPrompt()
{
    //设置字体
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 30;
    wcscpy_s(f.lfFaceName, L"微软雅黑");
    f.lfQuality = DEFAULT_QUALITY;
    settextstyle(&f);
    settextcolor(BLACK);

    //绘制提示
    outtextxy(235, 20, L"下个方块");
    rectangle(240, 60, 320, 140);
    f.lfHeight = 25;
    settextstyle(&f);

    //绘制分数
    wchar_t str[10];
    wsprintf(str, L"分数：%d", this->score);
    outtextxy(230, 150, str);

    //绘制时间
    wsprintf(str, L"时间：%d.%d", this->gameTime / 1000, this->gameTime % 1000 / 10);
    outtextxy(230, 175, str);

    //绘制游戏标题
    f.lfHeight = 40;
    settextstyle(&f);
    settextcolor(RED);

    outtextxy(234, 250, L"Tetris");

}

bool Game::checkLine(int line) const
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        if (map[line][i] == 0)
            return false;
    }
    return true;
}


void Game::clearLine()
{
    int line = -1;
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        if (checkLine(i))
        {
            line = i;
            break;
        }
    }
    if (line != -1)
    {
        for (int i = line; i > 0; --i)
        {
            for (int j = 0; j < MAP_WIDTH; ++j)
            {
                map[i][j] = map[i - 1][j];
            }
        }
        this->score += 10;
    }
    this->drawPrompt();
}

void Game::updateTime()
{
    this->gameTime += 500;
}

void Game::setMap(int x, int y, bool v)
{
    map[y][x] = v;
}

bool Game::getMap(int x, int y)
{
    return map[y][x];
}