#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "MineGenerator.h"

class Board
{
private:
	std::vector<std::vector<Cell>> cells;
	int width;
	int height;
	int mineCount;
	std::unique_ptr<MineGenerator> generator;

public:
	
	Board(int w, int h, int mines) : width(w), height(h), mineCount(mines)
	{
		for (int y = 0; y < height; ++y)
		{
			std::vector<Cell> row;
			for (int x = 0; x < width; ++x)
			{
				row.emplace_back(x, y);
			}
			cells.push_back(row);
		} //matrix[y][x]
	}

	void setGenerator(std::unique_ptr<MineGenerator> gen)
	{
		generator = std::move(gen);

	}

	void generateMines(int safeX, int safeY)
	{
		if (generator != nullptr)
		{
			generator->generate(cells, safeX, safeY);
			countNeighbourMines();
		}
	}

	void countNeighbourMines() 
	{
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				int count = 0;
				for (auto n : getNeighbors(x, y))
				{
					if (n->getHasMine()) ++count;
				}
				
				cells[y][x].setNeighboringMines(count);
			}

	}

	std::vector<Cell*> getNeighbors(int x, int y)
	{
		std::vector<Cell*> neighbors;
		for (int dx = -1; dx <= 1; ++dx) // Loop through the neighboring cells 
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				if (dx == 0 && dy == 0) continue;
				int nx = x + dx;
				int ny = y + dy;
				if (nx >= 0 && nx < width && ny >= 0 && ny < height)
				{
					neighbors.push_back(&cells[ny][nx]); 
					//&cells means adress
				}
			}
		}
		return neighbors;
	}

	void revealCell(int x, int y)
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			cells[y][x].reveal();
		}
	}

	void revealNeighbors(int x, int y)
	{
		auto neighbors = getNeighbors(x, y);
		for (Cell* neighbor : neighbors)
		{
			if (!neighbor->getIsRevealed() && !neighbor->getIsQuestioned() && !neighbor->getIsFlagged())
			{
				neighbor->reveal();
				if (neighbor->getNeighboringMines() == 0 && !neighbor->getHasMine())
				{
					revealNeighbors(neighbor->getX(), neighbor->getY());
				}
			}
		}
	}

	void revealAllCells()
	{
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				cells[y][x].reveal();
			}
		
	} 

	void revealAllMines()
	{
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				Cell& cell = cells[y][x];
				if (cell.getHasMine())
				{
					cell.reveal();
				}
			}
		
	}

	void flagAllMines()
	{
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x)
			{
				Cell& cell = cells[y][x];
				if (cell.getHasMine())
				{
					cell.setQuestioned(false);
					cell.setFlagged(true);
				}
			}
	}


	
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getMineCount() { return mineCount; }
	Cell& getCell(int x, int y)
	{
		return cells[y][x];
	}
	
	bool isInside(int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	}


};

