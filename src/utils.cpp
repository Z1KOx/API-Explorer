#include "utils.h"
#include "../imgui/imgui_internal.h"

// Draw simple lines
void utils::simpleLineX(
    const ImVec2& position,
    const float length,
    const ImVec4& color
) noexcept
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 end(position.x + length, position.y);

    draw_list->AddLine(position, end, IM_COL32((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255)));
}

void utils::simpleLineY(
    const ImVec2& position,
    const float length, 
    const ImVec4& color
) noexcept
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 end(position.x, position.y + length);

    draw_list->AddLine(position, end, IM_COL32((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255)));
}

void utils::lineWithShadow(
    ImVec2 position,
    int numLines,
    float length,
    int initialAlpha,
    int alphaStep,
    int colorR,
    int colorG,
    int colorB
) noexcept
{
    for (int i = 0; i <= numLines; ++i)
    {
        int alpha = initialAlpha - i * alphaStep;
        utils::simpleLineX(ImVec2(position.x, position.y + i), length, ImVec4(ImColor(colorR, colorG, colorB, alpha)));
    }
}

// Draw color fade line
void utils::gradientLineX(
    const ImVec2& position,
    const float length,
    const int num_steps,
    const ImVec4& start_color,
    const ImVec4& end_color
) noexcept
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 gradient_end = ImVec2(position.x + length, position.y + 1.f);
    const float line_length = length / num_steps;

    for (int i = 0; i < num_steps; ++i)
    {
        const ImVec2 rect_start(position.x + i * line_length, position.y);
        const ImVec2 rect_end(position.x + (i + 1) * line_length, gradient_end.y);

        const float t = static_cast<float>(i) / num_steps;
        const ImVec4 col = ImVec4(
            start_color.x + (end_color.x - start_color.x) * t,
            start_color.y + (end_color.y - start_color.y) * t,
            start_color.z + (end_color.z - start_color.z) * t,
            start_color.w + (end_color.w - start_color.w) * t
        );

        draw_list->AddRectFilled(rect_start, rect_end, ImGui::ColorConvertFloat4ToU32(col));
    }
}

void utils::gradientLineY(
    const ImVec2& position,
    const float length,
    const int num_steps,
    const ImVec4& start_color,
    const ImVec4& end_color
) noexcept
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 gradient_end = ImVec2(position.x + 1.f, position.y + length);
    const float line_length = length / num_steps;

    for (int i = 0; i < num_steps; ++i)
    {
        const ImVec2 rect_start(position.x, position.y + i * line_length);
        const ImVec2 rect_end(gradient_end.x, position.y + (i + 1) * line_length);

        const float t = static_cast<float>(i) / num_steps;
        const ImVec4 col = ImVec4(
            start_color.x + (end_color.x - start_color.x) * t,
            start_color.y + (end_color.y - start_color.y) * t,
            start_color.z + (end_color.z - start_color.z) * t,
            start_color.w + (end_color.w - start_color.w) * t
        );

        draw_list->AddRectFilled(rect_start, rect_end, ImGui::ColorConvertFloat4ToU32(col));
    }
}

void utils::shadowBox(
    const char* id,
    const ImVec2& position,
    const ImVec2& size, 
    const ImVec4& color
) noexcept
{
    ImGui::SetCursorPos(position);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(color)));

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

    ImGui::BeginChild(id, ImVec2(size));
    {
        ImGui::PopStyleVar(1);
        ImGui::PopStyleColor(1);
        ImGui::EndChild();
    }
}