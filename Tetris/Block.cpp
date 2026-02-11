#include"Block.h"

bool Block::blockData[7][4][4] = {0};

Block::Block(Game& game, int x, int y) : x(x), y(y), game(game), color(LIGHTBLUE)
{
    type = rand() % 7;
    switch (type)
    {
    case 0:
        color = LIGHTBLUE;
        break;
    case 1:
        color = LIGHTGRAY;
        break;
    case 2:
        color = LIGHTGREEN;
        break;
    case 3:
        color = YELLOW;
        break;
    case 4:
        color = RED;
        break;
    case 5:
        color = BLACK;
        break;
    case 6:
        color = CYAN;
        break;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)

        {
            curBlockData[i][j] = blockData[type][i][j];
        }
    }
    direct = true;
}

bool Block::move(int direction)
{
    switch (direction)
    {
    case 0:
        y++;
        if (checkCollision())
        {
            y--;
            return true;
        }
        break;
    case 1:
        x++;
        if (checkCollision())
        {
            x--;
        }
        break;
    case 2:
        x--;
        if (checkCollision())
        {
            x++;
        }
        break;
    }
    return false;
}

void Block::draw()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curBlockData[i][j])
            {
                if (j + y >= 0)
                {
                    setfillcolor(this->color);
                    int left = 20 + 20 * (x + i);
                    int top = 20 + 20 * (y + j);

                    fillrectangle(left, top, left + 20, top + 20);
                }
            }
        }
    }
}

void Block::clear()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curBlockData[i][j])
            {
                if (j + y >= 0)
                {
                    int left = 20 + 20 * (x + i);
                    int top = 20 + 20 * (y + j);

                    clearrectangle(left, top, left + 20, top + 20);
                }
            }
        }
    }
}

void Block::addMap()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (curBlockData[i][j])
            {
                game.setMap(x + i, y + j, curBlockData[i][j]);
            }
        }
    }
}

void Block::rotate()
{
    if (type == 4)
        return;
    bool temp;
    if (!direct)
    {
        //direct为零时顺时针旋转
        temp = curBlockData[0][0];
        curBlockData[0][0] = curBlockData[0][2];
        curBlockData[0][2] = curBlockData[2][2];
        curBlockData[2][2] = curBlockData[2][0];
        curBlockData[2][0] = temp;
        temp = curBlockData[1][0];
        curBlockData[1][0] = curBlockData[0][1];
        curBlockData[0][1] = curBlockData[1][2];
        curBlockData[1][2] = curBlockData[2][1];
        curBlockData[2][1] = temp;

    }
    else
    {
        //逆时针旋转
        temp = curBlockData[0][0];
        curBlockData[0][0] = curBlockData[2][0];
        curBlockData[2][0] = curBlockData[2][2];
        curBlockData[2][2] = curBlockData[0][2];
        curBlockData[0][2] = temp;
        temp = curBlockData[1][0];
        curBlockData[1][0] = curBlockData[2][1];
        curBlockData[2][1] = curBlockData[1][2];
        curBlockData[1][2] = curBlockData[0][1];
        curBlockData[0][1] = temp;
    }

    switch (type)
    {
    case 0:
        if (curBlockData[1][3])
        {
            curBlockData[1][3] = false;
            curBlockData[3][1] = true;
        }
        else
        {
            curBlockData[3][1] = false;
            curBlockData[1][3] = true;
        }
        break;
    case 5:
    case 6:
        if (!checkCollision())
        {
            direct = !direct;
        }
    }

    if (checkCollision())
    {
        if (direct)
        {
            temp = curBlockData[0][0];
            curBlockData[0][0] = curBlockData[0][2];
            curBlockData[0][2] = curBlockData[2][2];
            curBlockData[2][2] = curBlockData[2][0];
            curBlockData[2][0] = temp;
            temp = curBlockData[1][0];
            curBlockData[1][0] = curBlockData[0][1];
            curBlockData[0][1] = curBlockData[1][2];
            curBlockData[1][2] = curBlockData[2][1];
            curBlockData[2][1] = temp;
        }
        else
        {
            temp = curBlockData[0][0];
            curBlockData[0][0] = curBlockData[2][0];
            curBlockData[2][0] = curBlockData[2][2];
            curBlockData[2][2] = curBlockData[0][2];
            curBlockData[0][2] = temp;
            temp = curBlockData[1][0];
            curBlockData[1][0] = curBlockData[2][1];
            curBlockData[2][1] = curBlockData[1][2];
            curBlockData[1][2] = curBlockData[0][1];
            curBlockData[0][1] = temp;
        }
        if (type == 0)
        {
            if (curBlockData[1][3])
            {
                curBlockData[1][3] = true;
                curBlockData[3][1] = false;
            }
            else
            {
                curBlockData[3][1] = true;
                curBlockData[1][3] = false;;
            }
        }
    }
}

bool Block::checkCollision()const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j  < 4; j++)
        {
            if ((game.getMap(x + i, y + j)
                || 20 + 20 * (x + i) < 20
                || 20 + 20 * (x + i) + 20 > 220
                || 20 + 20 * (j + y) + 20 > 420)
                && curBlockData[i][j]
                )
                return true;
        }
    }
    return false;
}

void Block::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Block::generateBlockData()
{
    blockData[0][1][0] = blockData[0][1][1] = blockData[0][1][2] = blockData[0][1][3] = true;

    blockData[1][1][0] = blockData[1][1][1] = blockData[1][1][2] = blockData[1][0][2] = true;

    blockData[2][0][0] = blockData[2][1][0] = blockData[2][1][1] = blockData[2][1][2] = true;

    blockData[3][1][0] = blockData[3][1][1] = blockData[3][0][1] = blockData[3][1][2] = true;

    blockData[4][0][0] = blockData[4][0][1] = blockData[4][1][0] = blockData[4][1][1] = true;

    blockData[5][0][0] = blockData[5][0][1] = blockData[5][1][1] = blockData[5][1][2] = true;

    blockData[6][1][0] = blockData[6][0][1] = blockData[6][1][1] = blockData[6][0][2] = true;
}

void Block::randType()
{
    this->type = rand() % 7;
    switch (type)
    {
    case 0:
        color = LIGHTBLUE;
        break;
    case 1:
        color = LIGHTGRAY;
        break;
    case 2:
        color = LIGHTGREEN;
        break;
    case 3:
        color = YELLOW;
        break;
    case 4:
        color = RED;
        break;
    case 5:
        color = BLACK;
        break;
    case 6:
        color = CYAN;
        break;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)

        {
            curBlockData[i][j] = blockData[type][i][j];
        }
    }
    direct = true;
}

void Block::operator=(const Block& block)
{
    x = block.x;
    y = block.y;
    type = block.type;
    direct = block.direct;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            this->curBlockData[i][j] = block.curBlockData[i][j];
        }
    }
    color = block.color;
}

