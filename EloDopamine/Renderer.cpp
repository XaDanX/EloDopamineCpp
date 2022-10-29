#include "Renderer.h"

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
