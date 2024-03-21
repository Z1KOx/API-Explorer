#ifndef UTILS_H
#define UTILS_H

#include "../imgui/imgui.h"

namespace utils
{
    // Draw simple lines
	void drawLineX(
		const ImVec2& position,
		const float length,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	void drawLineY(
		const ImVec2& position,
		const float length,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	// Draw color fade line
	void drawGradientLineX(
		const ImVec2& position,
		const float length,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);

	void drawGradientLineY(
		const ImVec2& position,
		const float length,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);
}

#endif