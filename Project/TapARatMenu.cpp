#include "TapARatMenu.h"
#include "TapARat.h"
Engine::TapARatMenu::TapARatMenu(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "GUI Demo";
}

Engine::TapARatMenu::~TapARatMenu()
{
}

void Engine::TapARatMenu::Init()
{
	Engine::ScreenManager::GetInstance(this)
		->AddScreen("ingame", new TapARat(setting))
		->AddScreen("mainmenu", new MainMenuScreen())
		->SetCurrentScreen("mainmenu");

}

void Engine::TapARatMenu::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::TapARatMenu::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}





