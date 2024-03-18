#ifndef UTILS_H
#define UTILS_H

#include "../imgui/imgui.h"

// To draw simple lines
void drawLineX(const ImVec2& position, float length, const ImVec4& color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
void drawLineY(const ImVec2& position, float length, const ImVec4& color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

#endif // UTILS_H
