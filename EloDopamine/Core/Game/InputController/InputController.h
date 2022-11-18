#pragma once
#include <iostream>
#include <queue>
#include "Orders/OrderBase.h"
#include "../../Math/Vector.h"
#include <thread>
#include <iostream>
#include "../../Utils/KeyCodes.h"
class InputController {
private:
	std::queue<std::unique_ptr<OrderBase>> orderQueue;

	void MoveCursor(float x, float y);

	void LeftClickDown();
	void LeftClickUp();

	void RightClickDown();
	void RightClickUp();

	void KeyDown(HKey key);
	void KeyUp(HKey key);

public:
	void Update();

	void IssueClickAt(int x, int y);
	void IssueClick();

	void IssueClickButtonAt(int x, int y, HKey button);

	void IssueClickButton(HKey button);

	Vector2 GetCursorPosition();

    [[noreturn]] void UpdateLoopThread();
	std::thread spawn() {
		return std::thread([this] { this->UpdateLoopThread(); });
	}

};
inline extern std::unique_ptr<InputController> inputController = std::make_unique<InputController>();