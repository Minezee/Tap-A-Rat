#pragma once
#ifndef DINO_MAULIDZAR
#define DINOMAULIDZAR

#include "Game.h"
#include "Screen.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "ScreenManager.h"



namespace Engine {
	class DinoMaulidzar :public Engine::Screen
	{
	public:
		DinoMaulidzar(Setting* setting);
		~DinoMaulidzar();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
	private:
		void InitMaulidzar();
		void InitEnvironment();
		void InitObstacle();

		void UpdateMaulidzar();
		void UpdateEnvironment();
		void UpdateObstacles();

		void RenderMaulidzar();
		void RenderEnvironment();
		void RenderObstacles();

		void StartGame();
		void RestartGame();
		void StopGameBecauseOfDeath();

		void PlayRunAnimation();
		void PlayIdleAnimation();
		void PlayJumpAnimation();

		void Jump();
		void JumpPhysic();
		
		void CalculateScore();
		void MoveObstacleToScreen(Sprite* s);
		void CollisionDetector();

		Engine::Texture* textureMaulidzar = NULL;
		Engine::Texture* textureObstacle = NULL;
		Engine::Texture* textureBackground = NULL;
		Engine::Texture* textureGround = NULL;

		Engine::Sprite* spriteMaulidzar = NULL;

		Text* text = NULL;
		Text* loseText = NULL;
		Text* endText = NULL;

		vector<Sprite*> spritesBackground, spritesGround, spritesObstacle;

		vector<bool> obstacleAvailabilityStatus;

		float currentScore = 0,
			speed = 0.7,
			score = 0,
			defaultSpeed = 0.7,
			xMaulidzar = 10,
			yMaulidzar = -30,
			environmentMaxCount = 3,
			obstacleMaxCount = 1,
			environmentOffset = 20,
			yVelocity = 0,
			gravity = 0,
			nextObstacleDelayWaitTime = 300,
			obstacleDelayWaitTimeCounter = 0;

		bool isJump = false, isPlay = true;
	};
}

#endif
