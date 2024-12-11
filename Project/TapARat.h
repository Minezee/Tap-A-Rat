#pragma once
#ifndef TAP_A_RAT
#define TAPARAT

#include "Game.h"
#include "Screen.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "ScreenManager.h"
#include <vector>

namespace Engine {
	class TapARat : public Engine::Screen
	{
	public:
		TapARat(Setting* setting);
		~TapARat();
		virtual void Init();
		virtual void Update();
		virtual void Draw();

	private:
		void InitRat();
		void InitBackground();
		void InitCaveHole();

		void RenderRat();
		void RenderBackground();
		void RenderCaveHole();
		void SpawnRat();

		void UpdateRat();

		void HandleScore();
		void HandleClick();
		void HandleHitDetection();
		void HandleRestart();
		void HandleGameOver();

		Engine::Texture* bgTexture = NULL;
		Engine::Texture* caveTexture = NULL;

		Engine::Sprite* bgSprite = NULL;
		Engine::Sprite* ratSprite = NULL;
		Sound* punchSound = NULL;
		Text* text = 0;
		Text* missScore = 0;
		bool hitLocked = false;
		bool gameOver = false;
		int score = 0;
		int totalSpawn = 0;
		float ratSpawnTimer = 0.06f;
		float beatInterval = 60.0f / ratSpawnTimer;
		float beatTimer = 0.06f;
		float ratSpawnInterval = 0.06;
		bool ratVisible = false;
		float ratPosX = 0.0f, ratPosY = 0.0f;

		std::vector<Engine::Sprite*> spritesCave;
		std::vector<std::pair<float, float>> cavePositions;
	};
}

#endif