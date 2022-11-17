#pragma once
#include "imgui/imgui.h"
#include "Vector.h"
#include "Engine.h"


inline namespace Fonts {
	inline ImFont* font11;
	inline ImFont* font19;
}

class Renderer {
public:
	void DrawCircleAt(const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) const;
	ImDrawList* GetDrawList();

	bool IsScreenPointOnScreen(const Vector2& point, float offsetX, float offsetY) const;
	bool IsWorldPointOnScreen(const Vector3& point, float offsetX, float offsetY) const;
	bool CustomGuiHotkey(int* k, const ImVec2& size_arg = ImVec2(50, 22));

};
inline extern Renderer* renderer = new Renderer();

