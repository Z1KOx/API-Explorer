#ifndef UTILS_H
#define UTILS_H

#include "../imgui/imgui.h"

namespace utils
{
	// Draw simple line
	void simpleLineX(
		const ImVec2& position = ImVec2(0.f, 0.f),
		const float length = 75.f,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	void simpleLineY(
		const ImVec2& position = ImVec2(0.f, 0.f),
		const float length = 75.f,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	// Draw simple line with shadow effect
	void lineWithShadow(
		ImVec2 position,
		int numLines,
		float length,
		int initialAlpha, // begin alpha
		int alphaStep, // reduce alpha in '%'
		int colorR,
		int colorG,
		int colorB
	);

	// Draw color fade line
	void gradientLineX(
		const ImVec2& position = ImVec2(0.f, 0.f),
		const float length = 75.f,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);

	void gradientLineY(
		const ImVec2& position = ImVec2(0.f, 0.f),
		const float length = 75.f,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);

	// Draw shadows for child
	void shadowBox(
		const char* id, // Don't make 2 shadows with same id (name)
		const ImVec2& position = ImVec2(0.f, 0.f),
		const ImVec2& size = ImVec2(50.f, 50.f),
		const ImVec4& color = ImVec4(ImColor(9, 9, 9, 100))
	);
}

#endif