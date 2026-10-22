#pragma once
#include "MineGenerator.h"
#include "Cell.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

class RandomMineGenerator :
    public MineGenerator
{
private:
    int mineCount;


public:
    RandomMineGenerator(int count) : mineCount(count) {}


    void generate(std::vector<std::vector<Cell>>& board, int safeX, int safeY) override 
    {
        int width = board[0].size();
        int height = board.size();
        std::vector<std::pair<int, int>> minesPsbl;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (x == safeX && y == safeY) continue;
                minesPsbl.push_back({ x,y });

            }

        }

        std::shuffle(minesPsbl.begin(), minesPsbl.end(), std::mt19937(std::random_device{}()));

        for (int i = 0; i < mineCount && i < minesPsbl.size(); ++i)
        {
            auto [x, y] = minesPsbl[i];
            board[y][x].setHasMine(true);
        }
    }
};

