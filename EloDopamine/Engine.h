#pragma once
#include "MemoryManager.h"
#include "Offsets.h"
#include "Vector.h"
#include "Math.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
class Engine {
private:
	float gameTime{ 0 };

	float viewMatrix[16];
	float projectionMatrix[16];
	float viewProjectionMatrix[16];

	int windowWidth{ 0 };
	int windowHeight{ 0 };

	int renderer{ 0 };
		
public:
	void Update();

	float GameTime();
	int WindowWidth();
	int WindowHeight();

	void UpdateLoopThread();
	std::thread spawn() {
		return std::thread([this] { this->UpdateLoopThread(); });
	}

	Vector2 WorldToScreen(const Vector3& pos);


};
inline extern Engine* engine = new Engine();
