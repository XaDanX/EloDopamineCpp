#include "InputController.h"
#include "TimeoutOrder.h"
#include "MouseMoveOrder.h"
#include "RightClickOrder.h"
#include "BlockInputOrder.h"
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


void InputController::Update() {
	if (this->orderQueue.empty())
		return;
	auto& current = this->orderQueue.front();
	if (current->Execute()) {
		this->orderQueue.pop();
	}
}

void InputController::IssueClickAt(int x, int y) {

	auto lastPos = this->GetCursorPosition();

	this->orderQueue.emplace(new BlockInputOrder(true));
	this->orderQueue.emplace(new MouseMoveOrder(x, y));
	this->orderQueue.emplace(new RightClickOrder(0));
	this->orderQueue.emplace(new TimeoutOrder(12));
	this->orderQueue.emplace(new RightClickOrder(1));
	this->orderQueue.emplace(new MouseMoveOrder(lastPos.x, lastPos.y));
	this->orderQueue.emplace(new BlockInputOrder(false));

}

void InputController::IssueClick() {
	this->orderQueue.emplace(new RightClickOrder(0));
	this->orderQueue.emplace(new TimeoutOrder(12));
	this->orderQueue.emplace(new RightClickOrder(1));
}

Vector2 InputController::GetCursorPosition() {
	POINT pos;
	GetCursorPos(&pos);
	return { (float)pos.x, (float)pos.y };
}

void InputController::UpdateLoopThread() {
	while (true) {
		this->Update();
		std::this_thread::sleep_for(500ns);
	}
}