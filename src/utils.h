#ifndef UTILS_H
#define UTILS_H

#include "../imgui/imgui.h"

namespace utils
{
	// Draw simple line
	void simplelineX(
		const ImVec2& position,
		const float length,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	void simpleLineY(
		const ImVec2& position,
		const float length,
		const ImVec4& color = ImVec4(ImColor(255, 255, 255, 255)) // rgba
	);

	// Draw simple line with shadow effect
	void lineWithShadow(
		ImVec2 position,
		int numLines,
		float length,
		int initialAlpha, // begin alpha
		int alphaStep, // reduce alpha in %
		int colorR,
		int colorG,
		int colorB
	);

	// Draw color fade line
	void gradientLineX(
		const ImVec2& position,
		const float length,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);

	void gradientLineY(
		const ImVec2& position,
		const float length,
		const int num_steps = 300, // how often the color should change along the line
		const ImVec4& start_color = ImVec4(ImColor(255, 0, 0, 255)), // rgba
		const ImVec4& end_color = ImVec4(ImColor(0, 255, 0, 255))
	);

	// Draw shadows for child
	void shadowBox(
		const char* id, // Plesae dont make 2 shadows with same id (name)
		const ImVec2& position,
		const ImVec2& size,
		const ImVec4& color = ImVec4(ImColor(9, 9, 9, 100))
	);
}

#endif