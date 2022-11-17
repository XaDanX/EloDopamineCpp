#include "Renderer.h"
#include "KeyCodes.h"
void Renderer::DrawCircleAt(const Vector3& worldPos, float radius, bool filled, int numPoints, ImColor color, float thickness) const {
	if (numPoints >= 200)
		return;

	static ImVec2 points[200];

	ImDrawList* canvas = ImGui::GetBackgroundDrawList();

	float step = 6.2831f / numPoints;
	float theta = 0.f;
	for (int i = 0; i < numPoints; i++, theta += step) {
		Vector3 worldSpace = { worldPos.x + radius * cos(theta), worldPos.y, worldPos.z - radius * sin(theta) };
		Vector2 screenSpace = engine->WorldToScreen(worldSpace);

		points[i].x = screenSpace.x;
		points[i].y = screenSpace.y;
	}

	if (filled)
		canvas->AddConvexPolyFilled(points, numPoints, color);
	else
		canvas->AddPolyline(points, numPoints, color, true, thickness);
}

bool Renderer::IsScreenPointOnScreen(const Vector2& point, float offsetX, float offsetY) const {
	return point.x > -offsetX && point.x < (engine->WindowWidth() + offsetX) && point.y > -offsetY && point.y < (engine->WindowWidth() + offsetY);
}

bool Renderer::IsWorldPointOnScreen(const Vector3& point, float offsetX, float offsetY) const {
	return IsScreenPointOnScreen(engine->WorldToScreen(point), offsetX, offsetY);
}


ImDrawList* Renderer::GetDrawList() {
	return ImGui::GetBackgroundDrawList();
}

bool Renderer::CustomGuiHotkey(int* k, const ImVec2& size_arg) {
	
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames[*(int*)k], size_arg))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...", size_arg);
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState(Key) & 0x8000) {
				*(int*)k = Key;
				waitingforkey = false;
			}
		}
	}
	return true;
		
}
