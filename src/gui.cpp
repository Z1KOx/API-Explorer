#include "render.h"
#include "utils.h"
#include "gui.h"
#include "api.h"

#include "../imgui/imgui.h"
#include <nlohmann/json.hpp>

#include <fstream>
#include <thread>

using json = nlohmann::json;

namespace draw
{
	namespace button
	{
		void saveToFile(const json& jsonData) noexcept
		{
			OPENFILENAME ofn;
			CHAR szFile[260] = { 0 };

			// Initialize OPENFILENAME structure
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "JSON Files (*.json)\0*.json\0All Files (*.*)\0*.*\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrInitialDir = NULL;
			ofn.lpstrTitle = "Save File";
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

			// Prompt user to select file to save
			if (GetSaveFileName(&ofn) == TRUE)
			{
				std::string filename = ofn.lpstrFile;

				// If no file extension provided, add ".json"
				if (filename.find('.') == std::string::npos)
					filename += ".json";

				// Write formatted JSON data to file
				std::ofstream file(filename);
				if (file.is_open())
				{
					file << jsonData.dump(4);
					file.close();
				}
			}
		}

		void saveAPI() noexcept
		{
			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::m_requested && !API::m_response.empty())
			{
				// Button color
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(300.f, 277.f));

				json jsonData = json::parse(API::m_response);

				if (ImGui::Button("Save API", ImVec2(65.f, 20.f)))
					saveToFile(jsonData);
			}
			else
			{
				// Button color if no api requested
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(300.f, 277.f));

				ImGui::Button("Save API", ImVec2(65.f, 20.f));
			}

			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
		}

		void deleteAPI() noexcept
		{
			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::m_requested && !API::m_response.empty())
			{
				// Button color
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(220.f, 277.f));

				if (ImGui::Button("Delete API", ImVec2(75.f, 20.f)))
				{
					// Restore everything so we can use another api input
					API::m_response = "";
					API::m_requested = false;
					btn::submit = false;

					// Restore everything back so we get the animation again
					childs::apiPrev_Height = 35.f;
					childs::apiSaveShadow_Height = 0.f;
					childs::apiSave_Height = 0.f;

					btn::del = true;
				}
			}
			else
			{
				// Button color if no api requested
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(220.f, 277.f));

				ImGui::Button("Delete API", ImVec2(75.f, 20.f));
			}

			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
		}
	} // button





	namespace titleBar
	{
		void exitButton() noexcept
		{
			// Button color
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(176, 44, 44, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(209, 79, 79, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(245, 103, 103, 255)));

			// Button stlye
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.f);

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(680.f, 4.f));

			if (ImGui::Button(" ", ImVec2(10.f, 10.f)))
				render::isRunning = false;

			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar(1);
		}

		void start() noexcept
		{
			// Color child background rgba
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));

			// Set x, y pos
			ImGui::SetCursorPos({ 0.f, 0.f });

			ImGui::BeginChild("Titlebar", ImVec2(700.f, 20.f));
			{
				ImGui::SetCursorPos(ImVec2(5.f, 2.f));
				ImGui::Text("API Explorer");

				draw::titleBar::exitButton();

				ImGui::PopStyleColor(1);
				ImGui::EndChild();
			}

			utils::gradientLineX(ImVec2(0.f, 19.f), 700.f, 300, ImVec4(ImColor(168, 50, 50, 255)), ImVec4(ImColor(181, 113, 49)));
			// Draw lines with shadow effect: utils.h
			utils::lineWithShadow(ImVec2(0.f, 19.f), 4, 700.f, 100, 20, 18, 18, 18);
		}
	} // titleBar





	namespace getAPIBox
	{
		void APITooltip() noexcept
		{
			// Make font smaller
			ImGui::SetWindowFontScale(0.8f);

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(100.f, 37.f));

			ImGui::TextColored(ImVec4(ImColor(182, 116, 16, 255)), "{?}");

			// restore font size
			ImGui::SetWindowFontScale(1.0f);

			// Tooltip color
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(ImColor(50, 29, 0, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(170, 109, 16, 255)));

			// Tooltip style
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.f);

			if (ImGui::IsItemHovered())
			{
				ImGui::SetNextWindowSize(ImVec2(300.f, 25.f));
				ImGui::BeginTooltip();
				ImGui::SetCursorPos(ImVec2(5.f, 5.f));
				ImGui::Text("Please enter your API link here and click 'Submit'");
				ImGui::EndTooltip();
			}
		
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);
		}

		void APIInputBox() noexcept
		{
			// InputText color
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(11, 11, 11, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

			// InputText style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			// Input buffer
			static char buffer[256];
			strcpy_s(buffer, sizeof(buffer), API::m_userApiLink.c_str());

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(15.f, 60.f));

			// Adjust x size for InputText
			ImGui::PushItemWidth(225.f);

			if (ImGui::InputText("##apiLink", buffer, sizeof(buffer)))
			{
				// Apply and reset input buffer
				API::m_userApiLink = buffer;
				buffer[0] = '\0';
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}

		void submitButton() noexcept
		{
			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			if (!API::m_userApiLink.empty())
			{
				// Button colors
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(11, 11, 11, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(160.f, 85));

				if (ImGui::Button("Submit", ImVec2(80.f, 20.f)))
					btn::submit = true;
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(160.f, 85));

				ImGui::Button("Submit", ImVec2(80.f, 20.f));
			}

			if (btn::submit)
			{
				// Check if userApiLink is not empty and API request is not already made
				if (!API::m_userApiLink.empty() && !API::m_requested)
				{
					// Start a new thread to make API request
					std::thread apiThread([&]() {
						API::m_response = API::getAPI();
						API::m_userApiLink = "";
						}
					);

					// Detach the thread to let it run independently
					apiThread.detach();
				}

				// Check if API response is received
				if (!API::m_response.empty())
					API::m_requested = true;
			}

			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar(2);
		}

		void start() noexcept
		{
			// Draw small shadow to our child
			utils::shadowBox("Get API", ImVec2(30.f, 41.f), ImVec2(250.f, 120.f), ImVec4(ImColor(9, 9, 9, 100)));

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			// Background style
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			// Set x, y pos
			ImGui::SetCursorPos({ 25.f, 35.f });

			ImGui::BeginChild("Get configuration", ImVec2(250.f, 120.f), true);
			{
				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(10.f, 8.f));
				ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "Obtain API Key");

				// Draw colored line
				utils::gradientLineX(ImVec2(25.f, 64.f), 250.f, 300, ImVec4(ImColor(168, 50, 50, 255)), ImVec4(ImColor(181, 113, 49)));

				// Draw lines with shadow effect: utils.h
				utils::lineWithShadow(ImVec2(25.f, 64.f), 3, 250.f, 70, 20, 24, 24, 24);

				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(10.f, 40.f));
				ImGui::Text("Insert API Link");

				draw::getAPIBox::APITooltip();

				draw::getAPIBox::APIInputBox();
				draw::getAPIBox::submitButton();

				ImGui::EndChild();
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}
	} // getAPIBox



	namespace APIViewerBox
	{
		void apiResponseBg() noexcept
		{
			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(11, 11, 11, 255)));

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));
			
			ImGui::BeginChild("Api-Response-Bg", ImVec2(354.f, childs::apiPrev_Height), true, ImGuiWindowFlags_HorizontalScrollbar);
			{
				// Set x, y pos for 'none' text
				ImGui::SetCursorPos(ImVec2(10.f, 10.f));
				if (!API::m_requested)
					ImGui::TextColored(ImVec4(ImColor(70, 70, 75, 255)), "none");
				else
				{
					// Opening animation
					if (btn::submit)
						if (childs::apiPrev_Height <= 235.f)
							++childs::apiPrev_Height;

					// Set x, y pos
					ImGui::SetCursorPos(ImVec2(5.f, 5.f));

					try
					{
						json jsonData = json::parse(API::m_response);

						static char responseText[4096];
						snprintf(responseText, sizeof(responseText), "%s", jsonData.dump(4).c_str());

						ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(0, 0, 0, 0)));

						ImGui::SetCursorPos(ImVec2(0.f, 0.f));
						ImGui::InputTextMultiline("##ApiResponse", responseText, sizeof(responseText), ImVec2(-1.f, -1.f), ImGuiInputTextFlags_ReadOnly);

						ImGui::PopStyleColor(1);
					}
					catch (json::parse_error&) {
						ImGui::TextColored(ImVec4(ImColor(255, 0, 0, 255)), "Failed to convert API response to JSON");
					}
				}

				ImGui::PopStyleColor(1);
			}
		}

		void start() noexcept
		{
			// Draw small shadow to our child
			utils::shadowBox("apiPrev", ImVec2(305.f, 41.f), ImVec2(374.f, 300.f), ImVec4(ImColor(9, 9, 9, 100)));

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			// Background style
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

                        // Set x, y pos
			ImGui::SetCursorPos(ImVec2(300.f, 35.f));
			
			ImGui::BeginChild("Api-Preview-Box", ImVec2(374.f, 300.f), true);
			{
				// Set x, y pos
				ImGui::SetCursorPos(ImVec2(10.f, 8.f));
				ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "API Viewer");

				// Draw colored line
				utils::gradientLineX(ImVec2(300.f, 64.f), 374.f, 300, ImVec4(ImColor(181, 113, 49, 255)), ImVec4(ImColor(168, 50, 50)));

				// Draw lines with shadow effect: utils.h
				utils::lineWithShadow(ImVec2(300.f, 64.f), 3, 374.f, 70, 20, 24, 24, 24);

				// Draw new background for API response
				draw::APIViewerBox::apiResponseBg();

				ImGui::EndChild();
			}

			draw::button::deleteAPI();
			draw::button::saveAPI();

			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);
			ImGui::EndChild(); // End main child
		}
	} // APIViewerBox
} // draw





void render::Render() noexcept
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

	draw::titleBar::start();

	draw::getAPIBox::start();

	draw::APIViewerBox::start();

	ImGui::End();
}