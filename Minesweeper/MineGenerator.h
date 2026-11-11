#pragma once
#include <vector>
#include <random>      // mt19937, random_device
#include <algorithm>   // shuffle
#include "Cell.h"

// static_cast<T> - зміна типу
class MineGenerator
{
protected:
	int mineCount;
	int timeMineCount;
	virtual bool isForbidden(int x, int y, int safeX, int safeY) const = 0;

public:
	MineGenerator(int mines, int timeMines) : mineCount(mines), timeMineCount(timeMines) {}

	void generate(std::vector<std::vector<Cell>>& board, int safeX, int safeY)
	{
        int width = static_cast<int>(board[0].size());
        int height = static_cast<int>(board.size());


        std::vector<std::pair<int, int>> minesPsbl;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (!isForbidden(x,y,safeX,safeY))
                minesPsbl.push_back({ x,y });

            }

        }

        std::shuffle(minesPsbl.begin(), minesPsbl.end(), std::mt19937(std::random_device{}()));

        int size =  static_cast<int>(minesPsbl.size());

        for (int i = 0; i < mineCount && i < size; ++i)
        {
            auto [x, y] = minesPsbl[i];
            board[y][x].setHasMine(true);
        }

        for (int i = mineCount; i < mineCount + timeMineCount && i < size; ++i)
        {
            auto [x, y] = minesPsbl[i];
            board[y][x].setIsTimeMine(true);
        }

    
	}


    virtual ~MineGenerator() = default;
};

