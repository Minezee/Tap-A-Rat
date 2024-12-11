#include "TapARat.h"
Engine::TapARat::TapARat(Setting* setting)
{
    setting->windowTitle = "TAP A RAT";
}

Engine::TapARat::~TapARat()
{
}

void Engine::TapARat::Init() {
    InitBackground();
    InitCaveHole();
    InitRat();

    game->GetInputManager()->AddInputMapping("hit-cave-1", SDLK_a);
    game->GetInputManager()->AddInputMapping("hit-cave-2", SDLK_s);
    game->GetInputManager()->AddInputMapping("hit-cave-3", SDLK_d);
    game->GetInputManager()->AddInputMapping("hit-cave-4", SDLK_j);
    game->GetInputManager()->AddInputMapping("hit-cave-5", SDLK_k);
    game->GetInputManager()->AddInputMapping("hit-cave-6", SDLK_l);

    punchSound = (new Sound("punch_sound.wav"))->SetVolume(100);

    text = (new Text("8-bit Arcade In.ttf", 150, game->GetDefaultTextShader()))->SetPosition(0, 0);
    missScore = (new Text("8-bit Arcade In.ttf", 150, game->GetDefaultTextShader()))->SetPosition(game->GetSettings()->screenWidth - (text->GetFontSize() * text->GetScale()), game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()));

    text
        ->SetScale(0.5f)
        ->SetColor(255, 255, 255)
        ->SetPosition(20, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
        ->SetText(std::to_string(score));

    int totalMiss = totalSpawn - score;
    missScore
        ->SetScale(0.5f)
        ->SetColor(255, 255, 255)
        ->SetPosition(game->GetSettings()->screenWidth - (text->GetFontSize() * text->GetScale()), game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
        ->SetText(to_string(totalMiss));
}

void Engine::TapARat::Update() {
    int totalMiss = totalSpawn - score;
    if ((score > 5 && totalMiss >= score) || (score <= 5 && totalMiss >= 5)) {
        ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
        score = 0;
        totalMiss = 0;
        totalSpawn = 0;
        ratSpawnTimer = 0.06f;

        text->SetScale(0.5f)
            ->SetColor(255, 255, 255)
            ->SetPosition(20, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
            ->SetText(std::to_string(score));

        missScore->SetScale(0.5f)
            ->SetColor(255, 255, 255)
            ->SetPosition(game->GetSettings()->screenWidth - (text->GetFontSize() * text->GetScale()), game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
            ->SetText(std::to_string(totalMiss));

        return;
    }

    beatTimer += game->GetGameTime();
    if (beatTimer >= beatInterval) {
        beatTimer = 0.0f;
        SpawnRat();
    }

    HandleHitDetection();
}

void Engine::TapARat::SpawnRat() {
    ratVisible = true;
    hitLocked = false;
    totalSpawn += 1;

    int totalMiss = totalSpawn - score;
    int randomCaveIndex = rand() % cavePositions.size();
    ratPosX = cavePositions[randomCaveIndex].first;
    ratPosY = cavePositions[randomCaveIndex].second;
    ratSprite->SetPosition(ratPosX, ratPosY);

    missScore
        ->SetScale(0.5f)
        ->SetColor(255, 255, 255)
        ->SetPosition(game->GetSettings()->screenWidth - (text->GetFontSize() * text->GetScale()), game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
        ->SetText(to_string(totalMiss));
}

void Engine::TapARat::Draw() {
    RenderBackground();
    RenderCaveHole();
    if (ratVisible) {
        ratSprite->Draw();
    }

    text->Draw();
    missScore->Draw();
}

void Engine::TapARat::InitRat() {
    bgTexture = new Texture("asset_rat.png");
    ratSprite = new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
    ratSprite->SetSize(50, 50);
}

void Engine::TapARat::InitBackground() {
    bgTexture = new Texture("asset_bg.png");
    bgSprite = new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

    bgSprite->SetSize(game->GetSettings()->screenWidth, game->GetSettings()->screenHeight)
        ->SetPosition(0, 0);
}

void Engine::TapARat::InitCaveHole() {
    caveTexture = new Texture("asset_cave_mouth.png");

    cavePositions = {
        {200, 330},
        {400, 330},
        {600, 330},
        {200, 180},
        {400, 180},
        {600, 180},
    };

    for (auto& pos : cavePositions) {
        Engine::Sprite* caveSprite = new Sprite(caveTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
        caveSprite->SetPosition(pos.first, pos.second);
        caveSprite->SetSize(100, 90);
        spritesCave.push_back(caveSprite);
    }
}

void Engine::TapARat::HandleHitDetection() {
    if (hitLocked) return;

    for (int i = 0; i < cavePositions.size(); i++) {
        std::string hitInput = "hit-cave-" + std::to_string(i + 1);
        if (game->GetInputManager()->IsKeyPressed(hitInput)) {
            if (ratVisible && cavePositions[i].first == ratPosX && cavePositions[i].second == ratPosY) {
                ratVisible = false;
                hitLocked = true;
                HandleScore();
                punchSound->Play(false);
                break;
            }
        }
    }
}

void Engine::TapARat::HandleScore() {
    if (hitLocked) {
        score += 1;
    }

    if (score % 10 == 0) {
        ratSpawnTimer += 0.02f;
        beatInterval = 60.0f / ratSpawnTimer;
    }

    text
        ->SetScale(0.5f)
        ->SetColor(255, 255, 255)
        ->SetPosition(20, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()))
        ->SetText(to_string(score));
}

void Engine::TapARat::RenderBackground() {
    bgSprite->Draw();
}

void Engine::TapARat::RenderCaveHole() {
    for (auto& cave : spritesCave) {
        cave->Draw();
    }
}

void Engine::TapARat::RenderRat() {
    if (ratVisible) {
        ratSprite->Draw();
    }
}

void Engine::TapARat::HandleClick()
{
}

void Engine::TapARat::HandleRestart()
{
}

void Engine::TapARat::HandleGameOver()
{
}