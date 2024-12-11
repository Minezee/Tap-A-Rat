#ifndef DinoMenu_H
#define DinoMenu_H

#include "Game.h"
#include "Setting.h"
#include "MainMenuScreen.h"
#include "InGameScreen.h"
#include "DinoMaulidzar.h"

namespace Engine {
	class DinoMenu :public Engine::Game
	{
	public:
		DinoMenu(Setting* setting);
		~DinoMenu();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif

