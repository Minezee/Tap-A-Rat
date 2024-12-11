#ifndef TapARatMenu_H
#define TapARatMenu_H

#include "Game.h"
#include "Setting.h"
#include "MainMenuScreen.h"
#include "InGameScreen.h"
#include "DinoMaulidzar.h"

namespace Engine {
	class TapARatMenu :public Engine::Game
	{
	public:
		TapARatMenu(Setting* setting);
		~TapARatMenu();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif