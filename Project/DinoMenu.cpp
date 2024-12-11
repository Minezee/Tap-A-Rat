#include "DinoMenu.h"
#include "TapARat.h"

Engine::DinoMenu::DinoMenu(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "GUI Demo";
}

Engine::DinoMenu::~DinoMenu()
{
}

void Engine::DinoMenu::Init()
{
	Engine::ScreenManager::GetInstance(this)
		->AddScreen("ingame",new TapARat(setting))
		->AddScreen("mainmenu", new MainMenuScreen())
		->SetCurrentScreen("mainmenu");

}

void Engine::DinoMenu::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::DinoMenu::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}





