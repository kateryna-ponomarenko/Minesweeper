#pragma once
#include <chrono>

class Timer
{
private:
	
	int timeLimit;
	int elapsedTime;

	bool running;
	std::chrono::steady_clock::time_point startPoint;

public:
	Timer(int limit = 999) : timeLimit(limit), elapsedTime(0), running(false) {}

	void startTimer()
	{
		if (running) return;
		running = true;
		startPoint = std::chrono::steady_clock::now();
	}

	void stopTimer()
	{
		if (running)
		{
			auto now = std::chrono::steady_clock::now();
			elapsedTime += static_cast<int>(
				std::chrono::duration_cast<std::chrono::seconds>(now - startPoint).count());
			running = false;
		}
	}

	void resetTimer() 
	{
		elapsedTime = 0;
		running = false;
	}

	void addPenalty(int seconds)
	{
		elapsedTime += seconds;
	}

	int getElapsedTime()
	{
		if (running)
		{
			auto now = std::chrono::steady_clock::now();
			return elapsedTime + static_cast<int>(
				std::chrono::duration_cast<std::chrono::seconds>(now - startPoint).count());
		}
		return elapsedTime;
	}

	bool isTimeUp()
	{
		return getElapsedTime() >= timeLimit;
	}

	int getRemainingTime()
	{
		int left = timeLimit - getElapsedTime();
		if (left < 0) return 0;
		return left;
	}
};

