//#ifndef DINO_GAME
//#define DINOGAME
//
//#include "Game.h"
//#include "Setting.h"
//#include "Texture.h"
//#include "Sprite.h"
//
//namespace Engine {
//	class DinoGame :public Engine::Game
//	{
//	public:
//		DinoGame(Setting* setting);
//		~DinoGame();
//		virtual void Init();
//		virtual void Update();
//		virtual void Render();
//	private:
//		Engine::Texture* textureDino = NULL;
//		Engine::Texture* textureObstacle = NULL;
//
//		Engine::Sprite* spriteDino = NULL;
//		Engine::Sprite* spriteObstacle = NULL;
//
//		vector<Sprite*> backgrounds, middlegrounds, obstacles;
//		vector<bool> obstacleAvailableStatus;
//
//		void MoveBackground(vector<Sprite*>& bg, float speed);
//		void MoveObstacle(Sprite* obs, float speed);
//
//		void DrawLayer(vector<Sprite*>& bg);
//		void AddToBackgroundVector(vector<Sprite*>& bg, string name);
//		void AddTo
//
//		float yVelocity = 0, 
//			gravity = 0, 
//			xDino = 150,
//			yDino = -10,
//			initialXObstacle, 
//			yObstacle = 0, 
//			gameSpeed = 0.5;
//		bool jump = false, isObstacleOutOfScreen = false;
//	};
//}
//
//#endif
//
