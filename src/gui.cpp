#include "render.h"
#include "utils.h"
#include "gui.h"
#include "api.h"

#include "../imgui/imgui.h"

#include <fstream>
#include <thread>

namespace draw
{
	namespace button
	{
		void saveToFile(const std::string& content) noexcept
		{
			OPENFILENAME ofn;
			CHAR szFile[260] = { 0 };

			// Initilize OPENFILENAME structure
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

			// Prompt user to select file to save
			if (GetSaveFileName(&ofn) == TRUE)
			{
				std::string filename = ofn.lpstrFile;

				// If no file extension provided, add ".txt"
				if (filename.find('.') == std::string::npos)
					filename += ".txt";

				// Write content to file
				std::ofstream file(filename);
				if (file.is_open())
				{
					file << content;
					file.close();
				}
			}
		}

		void saveAPI() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(300.f, 227.f));

			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::requested && !API::response.empty())
			{
				// Button color
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				if (ImGui::Button("Save API", ImVec2(65.f, 20.f)))
					draw::button::saveToFile(API::response);
			}
			else
			{
				// Button color if no api requested
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(5, 5, 5, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(50, 21, 23, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(30, 30, 30, 255)));

				ImGui::Button("Save API", ImVec2(65.f, 20.f));
			}

			ImGui::PopStyleColor(5);
			ImGui::PopStyleVar(2);
		}

		void deleteAPI() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(220.f, 227.f));

			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

			if (API::requested && !API::response.empty())
			{
				// Button color
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(9, 9, 9, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(233, 233, 233, 255)));

				if (ImGui::Button("Delete API", ImVec2(75.f, 20.f)))
				{
					// Restore everything so we can use another api input
					API::response = "";
					API::requested = false;
					btn::submit = false;
					childs::apiPrev_Height = 35.f; // Reset API Viewer size

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
			// Set x, y pos
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
			ImGui::PopStyleVar(1);
		}

		void start() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos({ 0.f, 0.f });

			// Color child background rgba
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));

			ImGui::BeginChild("Titlebar", ImVec2(700.f, 20.f));
			{
				draw::titleBar::exitButton();

				ImGui::PopStyleColor(1);
				ImGui::EndChild();
			}

			// Draw lines with shadow effect: utils.h
			utils::lineWithShadow(ImVec2(0.f, 19.f), 4, 700.f, 100, 20, 18, 18, 18);
		}
	} // titleBar





	namespace getAPIBox
	{
		void labelTab() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 8.f));
			ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "Get API");
		}

		void labelEnterAPI() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));
			ImGui::Text("Enter API");
		}

		void APITooltip() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(70.f, 37.f));

			// Make font smaller
			ImGui::SetWindowFontScale(0.8f);
			ImGui::TextColored(ImVec4(ImColor(182, 116, 16, 255)), "{?}");

			// restore font size
			ImGui::SetWindowFontScale(1.0f);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Please enter your api key/link here and click on submit");
		}

		void APIInputBox() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(15.f, 60.f));

			// InputText color
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(11, 11, 11, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

			// InputText style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			// Input buffer
			static char buffer[256];
			strcpy_s(buffer, sizeof(buffer), API::userApiLink.c_str());

			// Adjust x size for InputText
			ImGui::PushItemWidth(225.f);
			if (ImGui::InputText("##apiLink", buffer, sizeof(buffer)))
			{
				// Apply and reset input buffer
				API::userApiLink = buffer;
				buffer[0] = '\0';
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}

		void submitButton() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(160.f, 85));

			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			if (!API::userApiLink.empty())
			{
				// Button colors
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(11, 11, 11, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

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

				ImGui::Button("Submit", ImVec2(80.f, 20.f));
			}

			if (btn::submit)
			{
				// Check if userApiLink is not empty and API request is not already made
				if (!API::userApiLink.empty() && !API::requested)
				{
					// Start a new thread to make API request
					std::thread apiThread([&]() {
						API::response = API::getAPI();
						API::userApiLink = "";
						}
					);

					// Detach the thread to let it run independently
					apiThread.detach();
				}

				// Check if API response is received
				if (!API::response.empty())
					API::requested = true;
			}

			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar(2);
		}

		void start() noexcept
		{
			// Draw small shadow to our child
			utils::shadowBox("Get API Tab", ImVec2(30.f, 41.f), ImVec2(250.f, 120.f), ImVec4(ImColor(9, 9, 9, 100)));

			// Set x, y pos
			ImGui::SetCursorPos({ 25.f, 35.f });

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			// Background style
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			ImGui::BeginChild("Get configuration", ImVec2(250.f, 120.f), true);
			{
				// 'Get API Tab' text
				draw::getAPIBox::labelTab();

				// Draw lines with shadow effect: utils.h
				utils::lineWithShadow(ImVec2(25.f, 64.f), 3, 250.f, 70, 20, 24, 24, 24);

				// 'Enter API' text
				draw::getAPIBox::labelEnterAPI();

				// '?' text
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
		void labelTab() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 8.f));
			ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "API Viewer");
		}

		void apiResponseBg() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(11, 11, 11, 255)));

			ImGui::BeginChild("Api-Response-Bg", ImVec2(354.f, childs::apiPrev_Height), true);
			{
				// Set x, y pos for 'none' text
				ImGui::SetCursorPos(ImVec2(10.f, 10.f));
				if (!API::requested)
					ImGui::TextColored(ImVec4(ImColor(70, 70, 75, 255)), "none");

				if (API::requested)
				{
					// Opening animation
					if (btn::submit)
						if (childs::apiPrev_Height <= 185.f)
							++childs::apiPrev_Height;

					// Set x, y pos
					ImGui::SetCursorPos(ImVec2(5.f, 5.f));

					ImGui::TextWrapped("%s", API::response.c_str());
				}

				ImGui::PopStyleColor(1);
			}
		}

		void start() noexcept
		{
			// Draw small shadow to our child
			utils::shadowBox("apiPrev", ImVec2(305.f, 41.f), ImVec2(374.f, 250.f), ImVec4(ImColor(9, 9, 9, 100)));

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(300.f, 35.f));

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			// Background style
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			ImGui::BeginChild("Api-Preview-Box", ImVec2(374.f, 250.f), true);
			{
				// 'API-Preview Tab' text
				draw::APIViewerBox::labelTab();

				// Draw lines with shadow effect: utils.h
				utils::lineWithShadow(ImVec2(300.f, 65.f), 3, 374.f, 70, 20, 24, 24, 24);

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





	namespace saveAPIBox
	{
		static std::string userSaveChain;

		void labelTab() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 8.f));
			ImGui::TextColored(ImVec4(ImColor(232, 232, 232, 255)), "Save API");
		}

		void labelWhatSave() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(10.f, 40.f));
			ImGui::Text("Enter Chain Save");
		}

		void saveTooltip() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(115.f, 37.f));

			// Make font smaller
			ImGui::SetWindowFontScale(0.8f);
			ImGui::TextColored(ImVec4(ImColor(182, 116, 16, 255)), "{?}");

			// restore font size
			ImGui::SetWindowFontScale(1.0f);

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Please enter what you want to save from API Viewer");
		}

		void saveInputBox() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(15.f, 60.f));

			// InputText color
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(11, 11, 11, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

			// InputText style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);

			// Input buffer
			static char buffer[256];
			strcpy_s(buffer, sizeof(buffer), userSaveChain.c_str());

			// Adjust x size for InputText
			ImGui::PushItemWidth(225.f);
			if (ImGui::InputText("##saveAPI", buffer, sizeof(buffer)))
			{
				// Apply and reset input buffer
				userSaveChain = buffer;
				buffer[0] = '\0';
			}

			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
		}

		void saveChainButton() noexcept
		{
			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(160.f, 85));

			// Button style
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);


			if (!userSaveChain.empty())
			{
				// Button colors
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(11, 11, 11, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(25, 25, 25, 255)));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(35, 35, 35, 255)));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(24, 24, 24, 255)));

				if (ImGui::Button("Save Chain", ImVec2(80.f, 20.f)))
				{
					userSaveChain = "";
					// Placeholder
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

				ImGui::Button("Save Chain", ImVec2(80.f, 20.f));
			}


			ImGui::PopStyleColor(4);
			ImGui::PopStyleVar(2);
		}

		void start() noexcept
		{
			// Move shadow with SaveAPI child
			if (childs::apiSaveShadow_Height <= 120.f)
				++childs::apiSaveShadow_Height;

			// Draw small shadow to our child
			utils::shadowBox("SaveBox Shadow", ImVec2(28.f, 171.f), ImVec2(252.f, childs::apiSaveShadow_Height), ImVec4(ImColor(9, 9, 9, 100)));

			// Set x, y pos
			ImGui::SetCursorPos(ImVec2(25.f, 165.f));

			// Background color
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(14, 14, 14, 255)));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(18, 18, 18, 255)));

			// Background style
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.f);

			// Animate height
			if (childs::apiSave_Height <= 119.f)
				++childs::apiSave_Height;

			ImGui::BeginChild("SaveAPI", ImVec2(250.f, childs::apiSave_Height), true, ImGuiWindowFlags_NoScrollbar);
			{
				saveAPIBox::labelTab();

				utils::lineWithShadow(ImVec2(25.f, 194.f), 3, 250.f, 70, 20, 24, 24, 24);

				saveAPIBox::labelWhatSave();
				saveAPIBox::saveTooltip();

				saveAPIBox::saveInputBox();
				saveAPIBox::saveChainButton();

				ImGui::PopStyleColor(2);
				ImGui::PopStyleVar(2);
				ImGui::EndChild();
			}
		} // saveAPIBox
	}
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

	draw::getAPIBox::start();

	if (API::requested)
		draw::saveAPIBox::start();

	draw::APIViewerBox::start();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::End();
}