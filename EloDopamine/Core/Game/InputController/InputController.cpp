#include "InputController.h"
#include "Orders/TimeoutOrder.h"
#include "Orders/MouseMoveOrder.h"
#include "Orders/RightClickOrder.h"
#include "Orders/BlockInputOrder.h"
#include "Orders/KeyClickOrder.h"
using namespace std::chrono_literals;

void InputController::MoveCursor(float x, float y) {
	static float fScreenWidth = (float)::GetSystemMetrics(SM_CXSCREEN) - 1;
	static float fScreenHeight = (float)::GetSystemMetrics(SM_CYSCREEN) - 1;

	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input.mi.dx = (LONG)(x * (65535.0f / fScreenWidth));
	input.mi.dy = (LONG)(y * (65535.0f / fScreenHeight));

	SendInput(1, &input, sizeof(INPUT));
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::LeftClickDown() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::LeftClickUp() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::RightClickDown() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::RightClickUp() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::KeyDown(HKey key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &input, sizeof(INPUT));
}

void InputController::KeyUp(HKey key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}




void InputController::Update() {
	__try {
		while (true) {
			if (this->orderQueue.empty())
				return;
			auto& current = this->orderQueue.front();
			if (current->Execute()) {
				this->orderQueue.pop();

			}
			else {
				return;
			}
		}
	}
	__except (true) {
		return;
	}
}

void InputController::IssueClickAt(int x, int y) {

	auto lastPos = this->GetCursorPosition();

	this->orderQueue.emplace(new BlockInputOrder(true));
	this->orderQueue.emplace(new MouseMoveOrder(x, y));
	this->orderQueue.emplace(new RightClickOrder(0));
	this->orderQueue.emplace(new TimeoutOrder(8));
	this->orderQueue.emplace(new RightClickOrder(1));
	this->orderQueue.emplace(new MouseMoveOrder(lastPos.x, lastPos.y));
	this->orderQueue.emplace(new BlockInputOrder(false));

}

void InputController::IssueClick() {
	this->orderQueue.emplace(new RightClickOrder(0));
	this->orderQueue.emplace(new TimeoutOrder(8));
	this->orderQueue.emplace(new RightClickOrder(1));
}

void InputController::IssueClickButtonAt(int x, int y, HKey button) {
	auto lastPos = this->GetCursorPosition();

	this->orderQueue.emplace(new BlockInputOrder(true));
	this->orderQueue.emplace(new MouseMoveOrder(x, y));
	this->orderQueue.emplace(new KeyClickOrder(button, 0));
	this->orderQueue.emplace(new TimeoutOrder(2));
	this->orderQueue.emplace(new KeyClickOrder(button, 1));
	this->orderQueue.emplace(new MouseMoveOrder(lastPos.x, lastPos.y));
	this->orderQueue.emplace(new BlockInputOrder(false));
}

void InputController::IssueClickButton(HKey button) {
	this->orderQueue.emplace(new KeyClickOrder(button, 0));
	this->orderQueue.emplace(new TimeoutOrder(2));
	this->orderQueue.emplace(new KeyClickOrder(button, 1));
}

Vector2 InputController::GetCursorPosition() {
	POINT pos;
	GetCursorPos(&pos);
	return { (float)pos.x, (float)pos.y };
}

[[noreturn]] void InputController::UpdateLoopThread() {
	while (true) {
		this->Update();
		std::this_thread::sleep_for(1ms);
	}
}