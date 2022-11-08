#pragma once
#include <iostream>
#include <queue>
#include "OrderBase.h"
#include "Vector.h"
#include <thread>
#include <iostream>

class InputController {
private:
	std::queue<std::unique_ptr<OrderBase>> orderQueue;

	void MoveCursor(float x, float y);

	void LeftClickDown();
	void LeftClickUp();

	void RightClickDown();
	void RightClickUp();

public:
	void Update();

	void IssueClickAt(int x, int y);
	void IssueClick();

	Vector2 GetCursorPosition();

	void UpdateLoopThread();
	std::thread spawn() {
		return std::thread([this] { this->UpdateLoopThread(); });
	}

};
inline extern std::unique_ptr<InputController> inputController = std::make_unique<InputController>();