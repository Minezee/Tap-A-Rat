#include "DinoMaulidzar.h"

Engine::DinoMaulidzar::DinoMaulidzar(Setting* setting)
{
	setting->windowTitle = "DINO GAME";
}

Engine::DinoMaulidzar::~DinoMaulidzar()
{
}


void Engine::DinoMaulidzar::Init()
{
	InitEnvironment();
	InitMaulidzar();
	InitObstacle();

	text = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	loseText = (new Text("8-bit Arcade In.ttf", 150, game->GetDefaultTextShader()))->SetPosition(0, 0);
	endText = (new Text("8-bit Arcade In.ttf", 24, game->GetDefaultTextShader()))->SetPosition(0, 0);

	game
		->GetInputManager()
		->AddInputMapping("arrow-up", SDLK_SPACE)
		->AddInputMapping("mainmenu", SDLK_ESCAPE);
}

void Engine::DinoMaulidzar::Update()
{
	if (isPlay) {
		UpdateEnvironment();
		UpdateMaulidzar();
		UpdateObstacles();
		CalculateScore();
		CollisionDetector();

		speed += 0.000005;
		text
			->SetScale(1.0f)
			->SetColor(255, 255, 255)
			->SetPosition(0, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
			->SetText(("Score = " + to_string(score)));
	}
	else {
		loseText->SetText("YOU LOSE")
				->SetPosition(160, 280)
				->SetColor(239, 1, 1);

		endText->SetText("Press ESC to Menu")
			->SetPosition(360, 250)
			->SetColor(255, 255, 255);

		speed = defaultSpeed;
	}
	
	if (game->GetInputManager()->IsKeyPressed("mainmenu")) {
		ScreenManager::GetInstance(game)
			->SetCurrentScreen("mainmenu");
		isPlay = true;
		score = 0;
		loseText->SetText("");
		endText->SetText("");

		spritesObstacle.clear();
		InitObstacle();

	}
}

void Engine::DinoMaulidzar::Draw()
{
	RenderEnvironment();
	RenderMaulidzar();
	RenderObstacles();
	text->Draw();
	loseText->Draw();
	endText->Draw();
}

void Engine::DinoMaulidzar::InitMaulidzar()
{
	textureMaulidzar = new Texture("maulidzar.png");
	spriteMaulidzar = new Sprite(textureMaulidzar, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

	spriteMaulidzar
		->SetNumXFrames(10)
		->SetNumYFrames(3)
		->AddAnimation("run", 0, 26)
		->AddAnimation("jump", 0,0)
		->SetAnimationDuration(20)
		->PlayAnim("run");

	spriteMaulidzar->SetBoundingBoxSize(spriteMaulidzar->GetScaleWidth() - 120,
		spriteMaulidzar->GetScaleHeight() - 120);
}

void Engine::DinoMaulidzar::InitObstacle()
{
	textureObstacle = new Texture("cactus.png");

	for (int i = 0; i <= obstacleMaxCount; i++) {
		Sprite* obs = new Sprite(textureObstacle, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

		obs	
			->SetPosition(game->GetSettings()->screenWidth, 0)
			->SetScale(0.2f);

		obs->SetBoundingBoxSize(obs->GetScaleWidth() - 120,
			obs->GetScaleHeight() - 120);

		spritesObstacle.push_back(obs);
		obstacleAvailabilityStatus.push_back(true);
	}
}

void Engine::DinoMaulidzar::InitEnvironment()
{
	textureBackground = new Texture("back.png");
	textureGround = new Texture("ground.png");

	int counter = 0;

	for (int i = 0; i <= environmentMaxCount; i++) {
		float offsetX = counter * game->GetSettings()->screenWidth;
		Sprite* back = new Sprite(textureBackground, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		Sprite* ground = new Sprite(textureGround, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

		back
			->SetSize(game->GetSettings()->screenWidth + environmentOffset, game->GetSettings()->screenHeight)
			->SetPosition(offsetX, 0);

		ground
			->SetSize(game->GetSettings()->screenWidth + environmentOffset, 200)
			->SetPosition(offsetX, 0);

		spritesBackground.push_back(back);
		spritesGround.push_back(ground);

		counter++;
	}
}

void Engine::DinoMaulidzar::UpdateMaulidzar()
{
	JumpPhysic();

	spriteMaulidzar
		->PlayAnim("run");

	if (game->GetInputManager()->IsKeyPressed("arrow-up") && !isJump) {
		Jump();
	}

	if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
	}

	yMaulidzar += yVelocity * game->GetGameTime();

	spriteMaulidzar
		->SetPosition(xMaulidzar, yMaulidzar)
		->Update(game->GetGameTime());
}

void Engine::DinoMaulidzar::UpdateObstacles() {
	int random = rand() % 200;
	nextObstacleDelayWaitTime = nextObstacleDelayWaitTime + random;

	for (Sprite* s : spritesObstacle) {
		MoveObstacleToScreen(s);
	}

	obstacleDelayWaitTimeCounter += game->GetGameTime();
}

void Engine::DinoMaulidzar::UpdateEnvironment() {
	int counterBackground = 0;
	int counterGround = 0;

	for (Sprite* s : spritesBackground) {
		float offsetX = counterBackground * game->GetSettings()->screenWidth;

		if (s->GetPosition().x < -game->GetSettings()->screenWidth - offsetX) {
			s->SetPosition(game->GetSettings()->screenWidth + offsetX, 0);
		}

		s->SetPosition(s->GetPosition().x - speed * game->GetGameTime(), 0);
		s->Update(game->GetGameTime());

		counterBackground++;
		if (counterBackground >= spritesBackground.size() - 1) {
			counterBackground = 0;
		}
	}

	for (Sprite* s : spritesGround) {
		float offsetX = counterGround * game->GetSettings()->screenWidth;

		if (s->GetPosition().x < -game->GetSettings()->screenWidth - offsetX) {
			s->SetPosition(game->GetSettings()->screenWidth + offsetX, 0);
		}

		s->SetPosition(s->GetPosition().x - speed * game->GetGameTime(), 0);
		s->Update(game->GetGameTime());

		counterGround++;
		if (counterGround >= spritesGround.size() - 1) {
			counterGround = 0;
		}
	}
}

void Engine::DinoMaulidzar::RenderMaulidzar()
{
	spriteMaulidzar->Draw();
}

void Engine::DinoMaulidzar::RenderObstacles()
{
	for (Sprite* s : spritesObstacle) {
		s->Draw();
	}
}

void Engine::DinoMaulidzar::RenderEnvironment()
{
	for (Sprite* s : spritesBackground) {
		s->Draw();
	}

	for (Sprite* s : spritesGround) {
		s->Draw();
	}
}

void Engine::DinoMaulidzar::StartGame()
{
	//TODO
}

void Engine::DinoMaulidzar::RestartGame()
{
	//TODO
}

void Engine::DinoMaulidzar::StopGameBecauseOfDeath()
{
	//TODO
}

void Engine::DinoMaulidzar::PlayRunAnimation()
{
	//TODO
}

void Engine::DinoMaulidzar::PlayIdleAnimation()
{
	//TODO
}

void Engine::DinoMaulidzar::PlayJumpAnimation()
{
	//TODO
}

void Engine::DinoMaulidzar::Jump()
{
	float ratio = (game->GetGameTime() / 16.7f);
	gravity = 0.12f * ratio;
	yVelocity = 2.2f;
	isJump = true;
}

void Engine::DinoMaulidzar::JumpPhysic() {
	if (yMaulidzar > -30) {
		yVelocity -= gravity;
		spriteMaulidzar->PlayAnim("jump");
	} else if (yMaulidzar < -30) {
		isJump = false;
		yVelocity = 0;
		yMaulidzar = -30;
		spriteMaulidzar->PlayAnim("run");
	}
}

void Engine::DinoMaulidzar::CalculateScore()
{
	score += speed * 1.2;
}

void Engine::DinoMaulidzar::CollisionDetector() {
	for (Sprite* obs : spritesObstacle) {
		if (obs->GetBoundingBox()->CollideWith(spriteMaulidzar->GetBoundingBox())) {
			isPlay = false;
		}
	}
}

void Engine::DinoMaulidzar::MoveObstacleToScreen(Sprite* s) {
	if(s->GetPosition().x < -game->GetSettings()->screenWidth) {
		s->SetPosition(game->GetSettings()->screenWidth, 0);
	}

	s->SetPosition(s->GetPosition().x - speed * game->GetGameTime(), 0);
}