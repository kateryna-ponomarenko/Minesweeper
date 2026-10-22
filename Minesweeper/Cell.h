#pragma once
#include <iostream>
class Cell
{
private:
	int CellX;
	int CellY;
	bool hasMine;
	bool IsRevealed;
	bool IsFlagged;
	bool IsQuestioned;
	int neighboringMines;

public:
	
	Cell(int xCoord, int yCoord): CellX(xCoord), CellY(yCoord), hasMine(false), IsRevealed(false), IsFlagged(false), IsQuestioned(false), neighboringMines(0) {}

	void setHasMine(bool value) {hasMine = value;}
	void setRevealed(bool value) { IsRevealed = value; }
	void setFlagged(bool value) { IsFlagged = value; }
	void setQuestioned(bool value) { IsQuestioned = value; }
	void setNeighboringMines(int value) { neighboringMines = value; }

	void reveal()
	{
		if (!IsRevealed && !IsFlagged)
		{
			IsRevealed = true;
			if (hasMine)
			{
				// Handle mine reveal
			}
			else if (neighboringMines == 0)
			{
				// Handle revealing neighboring cells logic here
			}
			else if (neighboringMines > 0)
			{
				// Handle revealing the number of neighboring mines logic here
			}
		}
		else if (IsQuestioned)
		{
			std::cout << "Cell is questioned." << std::endl	;
		}
	}
	void cycleMark()
	{
		if (!IsRevealed)
		{
			if (!IsFlagged && !IsQuestioned)
			{
				IsFlagged = true;
			}
			else if (IsFlagged)
			{
				IsFlagged = false;
				IsQuestioned = true;
			}
			else if (IsQuestioned)
			{
				IsQuestioned = false;
			}
		}
	}

	bool getHasMine() const
	{
		return hasMine;
	}
	bool getIsRevealed() const
	{
		return IsRevealed;
	}
	bool getIsFlagged() const
	{
		return IsFlagged;
	}
	bool getIsQuestioned() const
	{
		return IsQuestioned;
	}
	int getNeighboringMines() const
	{
		return neighboringMines;
	}

	int getX() const
	{
		return CellX;
	}

	int getY() const
	{
		return CellY;
	}

};
