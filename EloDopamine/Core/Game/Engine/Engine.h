#pragma once
#include "../../../Core/Game/Managers/MemoryManager/MemoryManager.h"
#include "../Offsets.h"
#include "../../Math/Vector.h"
#include "../../Math/Math.h"
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

	int hudInstance{ 0 };
	Vector3 worldMousePos;

	DWORD __cdecl CollisionFlag(float a1, float a2, float a3);
		
public:
	void Update();

	float GameTime() const;
	int WindowWidth() const;
	int WindowHeight() const;

	Vector3 MouseWorldPos();

    [[noreturn]] void UpdateLoopThread();
	std::thread spawn() {
		return std::thread([this] { this->UpdateLoopThread(); });
	}

	Vector2 WorldToScreen(const Vector3& pos);

	bool IsNotWall(Vector3 pos);



};
inline extern Engine* engine = new Engine();
