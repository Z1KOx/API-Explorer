#include "render.h"
#include "utils.h"
#include "../imgui/imgui.h"

void drawExitButton()
{
	ImGui::SetCursorPos(ImVec2(680.f, 5.f));

	// Button color
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(176, 44, 44, 255)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(209, 79, 79, 255)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(245, 103, 103, 255)));

	// Button stlye
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.f);

	if (ImGui::Button(" ", ImVec2(10.f, 10.f)))
		PostQuitMessage(0);

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();
}

void drawTitleBar()
{
	ImGui::SetCursorPos({ 0.f, 0.f });

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));

	ImGui::BeginChild("Titlebar", ImVec2(700.f, 20.f));
	{
		drawExitButton();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		ImGui::EndChild();
	}
}

void drawShadow(const ImVec2 position, const ImVec4 color)
{
	ImGui::SetCursorPos(position);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(color)));

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

	ImGui::BeginChild("Shadow", ImVec2(250.f, 235.f));
	{
		ImGui::PopStyleVar(1);
		ImGui::PopStyleColor(1);
		ImGui::EndChild();
	}
}

void drawConfigChild()
{
	ImGui::SetCursorPos({ 25.f, 35.f });

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

	ImGui::SetCursorPos({ 25.f, 35.f });
	ImGui::BeginChild("Get configuration", ImVec2(250.f, 235.f), true);
	{
		ImGui::SetCursorPos(ImVec2(10.f, 8.f));
		ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "Configuration Tab");

		// Draw line with shadows
		for (int i = 0; i <= 4; ++i)
		{
			int alpha = 100 - i * 20;
			utils::drawLineX(ImVec2(25.f, 65.f + i), 250.f, ImVec4(ImColor(24, 24, 24, alpha)));
		}

	}
	ImGui::EndChild();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(2);
}

void render::Render() noexcept
{
	// Main Window
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(11, 11, 11, 255)));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
		ImGui::Begin(
			"API Helper",
			&render::isRunning,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoTitleBar
		);

		ImGui::PopStyleColor(1);
		ImGui::PopStyleVar(2);
	}

	// TitleBar
	{
		drawTitleBar();
		// Draw Line and shadows on it
		for (int i = 0; i <= 4; ++i)
		{
			int alpha = 100 - i * 20;
			utils::drawLineX(ImVec2(0.f, 19.f + i), 700.f, ImVec4(ImColor(18, 18, 18, alpha)));
		}
	}

	// Config Child
	{
		drawShadow(ImVec2(30.f, 41.f), ImVec4(ImColor(9, 9, 9, 100)));
		drawConfigChild();
	}

	ImGui::End();
}