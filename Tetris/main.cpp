#include<iostream>
#include"Game.h"
#include"Block.h"
#include<time.h>

int main()
{
    //游戏窗口创建
    HWND hd = initgraph(350, 440);
    SetWindowText(hd, L"Tetris");
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);

    //生成游戏数据
    srand(time(NULL));
    Block::generateBlockData();

    //绘制界面
    Game game;
    game.drawView();
    game.drawPrompt();

    Block block(game);
    Block next_block(game, 11, 2);

    clock_t start = 0;
    clock_t end = 0;

    next_block.draw();
    
    ExMessage em;

    //游戏循环
    BeginBatchDraw();
    while (true)
    {
        //界面更新
        block.clear();
        clearrectangle(20, 20, 220, 420);
        game.drawView();

        //按键交互
        while (peekmessage(&em, EX_KEY) && em.message == WM_KEYDOWN)
        {
            switch (em.vkcode)
            {
            case VK_UP:
                block.rotate();
                break;
            case VK_DOWN:
                if (block.move())
                {
                    block.addMap();
                    block = next_block;
                    block.setPos();
                    next_block.clear();
                    next_block.setPos(11, 2);
                    next_block.randType();
                    next_block.draw();

                    if (block.checkCollision())
                    {
                        MessageBox(GetHWnd(), L"游戏结束", L"提示", MB_ICONWARNING);
                        goto exit;
                    }
                }
                break;
            case VK_LEFT:
                block.move(2);
                break;
            case VK_RIGHT:
                block.move(1);
                break;
            }
        }
        //游戏数据更新
        end = clock();
        if (end - start >= 500)
        {
            if (block.move())
            {
                block.addMap();
                block = next_block;
                block.setPos();
                next_block.clear();
                next_block.setPos(11, 2);
                next_block.randType();
                next_block.draw();

                if (block.checkCollision())
                {
                    MessageBox(GetHWnd(), L"游戏结束", L"提示", MB_ICONWARNING);
                    goto exit;
                }
            }
            start = clock();
            game.updateTime();
        }
        block.draw();
        game.clearLine();

        FlushBatchDraw();
        Sleep(50);
    }

    //游戏释放
    exit:
    EndBatchDraw();
    closegraph();
    return 0;
}
