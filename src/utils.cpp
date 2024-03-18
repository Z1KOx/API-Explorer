#include "utils.h"

void drawLineX(const ImVec2& position, float length, const ImVec4& color)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 end(position.x + length, position.y);

    draw_list->AddLine(position, end, IM_COL32((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255)));
}

void drawLineY(const ImVec2& position, float length, const ImVec4& color)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 end(position.x, position.y + length);

    draw_list->AddLine(position, end, IM_COL32((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255)));
}
