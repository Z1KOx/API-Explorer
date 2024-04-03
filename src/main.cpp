#include "render.h"

#include <thread>

#pragma warning(push)
#pragma warning(disable: 28251) // wWinMain

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// create gui
	render::CreateHWindow("API Helper");
	render::CreateDevice();
	render::CreateImGui();

	while (render::isRunning)
	{
		render::BeginRender();
		render::Render();
		render::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	render::DestroyImGui();
	render::DestroyDevice();
	render::DestroyHWindow();

	return EXIT_SUCCESS;
}

#pragma warning(pop)