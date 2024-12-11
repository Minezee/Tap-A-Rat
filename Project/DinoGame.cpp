//#include "DinoGame.h"
//
//Engine::DinoGame::DinoGame(Setting* setting) :Engine::Game(setting)
//{
//	setting->windowTitle = "DINO GAME";
//}
//
//Engine::DinoGame::~DinoGame()
//{
//}
//
//void Engine::DinoGame::Init()
//{
//	textureDino = new Texture("dino_maulidzar.png");
//	textureObstacle = new Texture("platform.png");
//
//	spriteDino = new Sprite(textureDino, defaultSpriteShader, defaultQuad);
//	spriteObstacle = new Sprite(textureObstacle, defaultSpriteShader, defaultQuad);
//
//	initialXObstacle = setting->screenWidth;
//
//	spriteDino
//		->SetNumXFrames(30)
//		->SetNumYFrames(1)
//		->AddAnimation("run", 9, 15)
//		->AddAnimation("jump", 0,8)
//		->SetScale(0.3)
//		->SetAnimationDuration(100)
//		->SetPosition(xDino, yDino)
//		->PlayAnim("run");
//
//	spriteObstacle
//		->SetSize(60, 100);
//
//	inputManager
//		->AddInputMapping("arrow-up", SDLK_UP);
//
//	for (int i = 0; i <= 4; i++) {
//		AddToLayer(backgrounds, "back.png");
//	}
//	for (int i = 5; i <= 8; i++) {
//		AddToLayer(middlegrounds, "front.png");
//	}
//}
//
//void Engine::DinoGame::Update()
//{
//	spriteDino->PlayAnim("run");
//	spriteObstacle->PlayAnim("idle-1");
//
//	if (inputManager->IsKeyPressed("arrow-up") && !jump) {
//		float ratio = (GetGameTime() / 16.7f);
//		gravity = 0.12f * ratio;
//		yVelocity = 1.6f;
//		jump = true;
//	}
//
//	if (yDino > -10) {
//		yVelocity -= gravity;
//		spriteDino->PlayAnim("jump");
//	} else if (yDino < -10) {
//		jump = false;
//		yVelocity = 0;
//		yDino = -10;
//	}
//
//	MoveBackground(backgrounds, 0.005f);
//	MoveBackground(middlegrounds, gameSpeed);
//
//	yDino += yVelocity * GetGameTime();
//
//	spriteDino->SetPosition(xDino, yDino);
//	spriteDino->Update(GetGameTime());
//
//	MoveObstacle(spriteObstacle, gameSpeed);
//
//	if (isObstacleOutOfScreen) {
//		spriteObstacle->SetPosition(initialXObstacle, yObstacle);
//		isObstacleOutOfScreen = false;
//	}
//}
//
//void Engine::DinoGame::Render()
//{
//	DrawLayer(backgrounds);
//	DrawLayer(middlegrounds);
//	spriteDino->Draw();
//	spriteObstacle->Draw();
//}
//
//void Engine::DinoGame::DrawLayer(vector<Sprite*>& bg)
//{
//	for (Sprite* s : bg) {
//		s->Draw();
//	}
//}
//
//void Engine::DinoGame::AddToBackgroundVector(vector<Sprite*>& bg, string name)
//{
//	Texture* texture = new Texture(name);
//
//	Sprite* s = new Sprite(texture, defaultSpriteShader, defaultQuad);
//	s->SetSize(setting->screenWidth, setting->screenHeight);
//	bg.push_back(s);
//
//	Sprite* s2 = new Sprite(texture, defaultSpriteShader, defaultQuad);
//	s2->SetSize(setting->screenWidth, setting->screenHeight)->SetPosition(setting->screenWidth, 0);
//	bg.push_back(s2);
//}
//
//void Engine::DinoGame::MoveBackground(vector<Sprite*>& bg, float speed)
//{
//	for (Sprite* s : bg) {
//		if (s->GetPosition().x < -setting->screenWidth) {
//			s->SetPosition(setting->screenWidth, 0);
//		}
//		s->SetPosition(s->GetPosition().x - speed * GetGameTime(), s->GetPosition().y);
//		s->Update(GetGameTime());
//	}
//}
//
//void Engine::DinoGame::MoveObstacle(Sprite* obs, float speed)
//{
//	if (obs->GetPosition().x <= -200) {
//		isObstacleOutOfScreen = true;
//	}
//	else {
//		obs->SetPosition(obs->GetPosition().x - speed * GetGameTime(), obs->GetPosition().y);
//	}
//
//	obs->Update(GetGameTime());
//}
//
