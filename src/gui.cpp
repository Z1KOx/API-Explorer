#include "render.h"
#include "utils.h"
#include "gui.h"
#include "api.h"

#include "../imgui/imgui.h"

#include <fstream>
#include <thread>

namespace draw
{
	namespace titleBar
	{
		void exitButton()
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

		void start()
		{
			ImGui::SetCursorPos({ 0.f, 0.f });

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));

			ImGui::BeginChild("Titlebar", ImVec2(700.f, 20.f));
			{
				draw::titleBar::exitButton();

				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
				ImGui::EndChild();
			}

			utils::drawLineWithShadow(4, 0.f, 19.f, 700.f, 100, 20, 18, 18, 18);
		}
	} // titleBar

	namespace configBox
	{
		void labelTab()
		{
			ImGui::SetCursorPos(ImVec2(10.f, 8.f));
			ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "Configuration Tab");
		}

		void labelEnterAPI()
		{
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));
			ImGui::Text("Enter API");
		}

		void APITooltip()
		{
			ImGui::SetCursorPos(ImVec2(70.f, 37.f));
			ImGui::SetWindowFontScale(0.8f);
			ImGui::TextColored(ImVec4(ImColor(182, 116, 16, 255)), "{?}");
			ImGui::SetWindowFontScale(1.0f);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Please enter your api key/link here and click on submit");
		}

		void APIInputBox()
		{
			ImGui::SetCursorPos(ImVec2(15.f, 60.f));

			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(11, 11, 11, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			ImGui::PushItemWidth(225.f);
			static char buffer[256];
			strcpy_s(buffer, sizeof(buffer), API::userApiLink.c_str());
			if (ImGui::InputText("##apiLink", buffer, sizeof(buffer)))
			{
				API::userApiLink = buffer;
				buffer[0] = '\0';
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}

		void submitButton()
		{
			ImGui::SetCursorPos(ImVec2(160.f, 85));

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(11, 11, 11, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));

			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			if (ImGui::Button("Submit", ImVec2(80, 20)))
				btn::submit = true;

			if (btn::submit)
			{
				if (!API::userApiLink.empty() && !API::requested)
				{
					std::thread apiThread([&]() {
						API::response = API::getAPI();
						API::userApiLink = "";
						}
					);

					apiThread.detach();
				}

				if (!API::response.empty())
					API::requested = true;
			}

			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar(2);
		}

		void start()
		{
			utils::drawShadow("Shadow1", ImVec2(30.f, 41.f), ImVec2(250.f, 235.f), ImVec4(ImColor(9, 9, 9, 100)));

			ImGui::SetCursorPos({ 25.f, 35.f });

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			ImGui::SetCursorPos({ 25.f, 35.f });
			ImGui::BeginChild("Get configuration", ImVec2(250.f, 235.f), true);
			{
				draw::configBox::labelTab();

				utils::drawLineWithShadow(4, 25.f, 64.f, 250.f, 100, 20, 24, 24, 24);

				draw::configBox::labelEnterAPI();
				draw::configBox::APITooltip();

				draw::configBox::APIInputBox();
				draw::configBox::submitButton();

				ImGui::EndChild();
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}
	} // configBox

	namespace apiBox
	{
		void labelTab()
		{
			ImGui::SetCursorPos(ImVec2(10.f, 8.f));
			ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "API-Preview Tab");
		}

		void apiResponseBg()
		{
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(11, 11, 11, 255)));

			ImGui::BeginChild("Api-Response-Bg", ImVec2(childs::apiPrev_Width, childs::apiPrev_Height), true);
			{
				ImGui::SetCursorPos(ImVec2(10.f, 10.f));
				if (!API::requested)
					ImGui::TextColored(ImVec4(ImColor(70, 70, 75, 255)), "none");

				if (API::requested)
				{
					if (btn::submit)
					{
						if (childs::apiPrev_Height <= 185.f)
							++childs::apiPrev_Height;
						if (childs::apiPrev_Width <= 354.f)
							childs::apiPrev_Width += 2.f;
					}

					ImGui::SetCursorPos(ImVec2(5.f, 5.f));
					ImGui::TextWrapped("%s", API::response.c_str());
				}

				ImGui::PopStyleColor(1);
			}
		}

		void start()
		{
			utils::drawShadow("Shadow2", ImVec2(305.f, 41.f), ImVec2(374.f, 235.f), ImVec4(ImColor(9, 9, 9, 100)));

			ImGui::SetCursorPos(ImVec2(300.f, 35.f));

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			ImGui::BeginChild("Api-Preview-Box", ImVec2(374.f, 235.f), true);
			{
				draw::apiBox::labelTab();

				utils::drawLineWithShadow(4, 300.f, 65.f, 374.f, 100, 20, 24, 24, 24);
				
				draw::apiBox::apiResponseBg();

				ImGui::EndChild();
			}

			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);
			ImGui::EndChild();
		}
	} // apiBox

	namespace button
	{
		void saveToFile(const std::string& content)
		{
			OPENFILENAME ofn;
			CHAR szFile[260] = { 0 };

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrInitialDir = NULL;
			ofn.lpstrTitle = "Save File";
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

			if (GetSaveFileName(&ofn) == TRUE)
			{
				std::string filename = ofn.lpstrFile;

				if (filename.find('.') == std::string::npos)
					filename += ".txt";

				std::ofstream file(filename);
				if (file.is_open())
				{
					file << content;
					file.close();
				}
			}
		}

		void save()
		{
			ImGui::SetCursorPos(ImVec2(615.f, 275.f));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::requested && !API::response.empty()) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				if (ImGui::Button("Save", ImVec2(50.f, 20.f)))
					draw::button::saveToFile(API::response);
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::Button("Save", ImVec2(50.f, 20.f));
			}

			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
		}

		void del()
		{
			ImGui::SetCursorPos(ImVec2(562.f, 275.f));

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::requested && !API::response.empty()) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				if (ImGui::Button("Delete", ImVec2(50.f, 20.f)))
				{
					API::response = "";
					API::requested = false;

					btn::del = true;
				}
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::Button("Delete", ImVec2(50.f, 20.f));
			}

			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
		}
	} // button
} // draw


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
		} // Main Window

		draw::titleBar::start();

		draw::configBox::start();
		draw::apiBox::start();

		draw::button::save();
		draw::button::del();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		ImGui::End();
	}