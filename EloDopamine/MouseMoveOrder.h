#pragma once
#include "OrderBase.h"
#include <Windows.h>
#include "Logger.h"


class MouseMoveOrder : public OrderBase {
private:

	float x = NULL;
	float y = NULL;
public:
	MouseMoveOrder(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}
	bool Execute() {
		static float fScreenWidth = (float)::GetSystemMetrics(SM_CXSCREEN) - 1;
		static float fScreenHeight = (float)::GetSystemMetrics(SM_CYSCREEN) - 1;

		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		input.mi.dx = (LONG)(x * (65535.0f / fScreenWidth));
		input.mi.dy = (LONG)(y * (65535.0f / fScreenHeight));

		SendInput(1, &input, sizeof(INPUT));
		SendInput(1, &input, sizeof(INPUT));
		return true;

	}
};