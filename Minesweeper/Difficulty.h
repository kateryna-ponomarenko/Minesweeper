#pragma once
#include <iostream>

class Difficulty
{
protected:
    std::string level;
    int width;
    int height;
    int minesCount;
    int timeLimitSeconds;

public:
    Difficulty(std::string n, int w, int h, int m, int t)
        : level(n), width(w), height(h), minesCount(m), timeLimitSeconds(t) {
    }

    int getWithd() const { return width; }
    int getHeight() const { return height; }
    int getMinesCount() const { return minesCount; }
    int getLimitSeconds() const { return timeLimitSeconds; }
    std::string getLevel() const { return level; }

    void setTime(int minutes) { timeLimitSeconds = minutes; }

    virtual ~Difficulty() = default;
};

