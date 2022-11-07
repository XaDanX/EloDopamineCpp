#pragma once
#include "imgui/imgui.h"
#include "Vector.h"
#include "Engine.h"


inline namespace Fonts {
	inline ImFont* font11;
}

class Renderer {
public:
	void DrawCircleAt(const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) const;
	ImDrawList* GetDrawList();
};
inline extern Renderer* renderer = new Renderer();

