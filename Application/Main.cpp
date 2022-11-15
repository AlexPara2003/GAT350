#include "Engine.h"
#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
	LOG("Application Started...");

	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Gamer", 800, 600, 0);
	LOG("Window Initialized...");

	neu::g_gui.Initialize(neu::g_renderer);

	// load scene 
	auto scene = neu::g_resources.Get<neu::Scene>("Scenes/texture.scn");

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 rot{ 0, 0, 0 };

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation = rot;
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			actor->m_transform.position = pos;
		}

		ImGui::Begin("Controls");
		ImGui::Button("Press Me!");
		ImGui::SliderFloat3("Position", &pos.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Rotation", &rot.x, -180.0f, 180.0f);
		ImGui::End();

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();
	}

	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();

	return 0;
}