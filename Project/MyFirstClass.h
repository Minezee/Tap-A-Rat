#ifndef LESSON01_BGCOLOR_H
#define LESSON01_BGCOLOR_H

#include "Game.h"
#include "Setting.h"

namespace Engine {
	class MyFirstClass :public Engine::Game
	{
	public:
		MyFirstClass(Setting* setting);
		~MyFirstClass();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration;
		int r, g, b;
		int mul;
	};
}

#endif