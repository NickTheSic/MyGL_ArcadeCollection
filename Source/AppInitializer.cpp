#include <GamePCH.h>
#include "AppInitializer.h"

AppInitializer::AppInitializer(Game* game)
{
	Game_ = game;
	Game_->DisplayRules();
	Run();
}

AppInitializer::~AppInitializer()
{
	delete Game_;
	Game_ = nullptr;

	delete Application_;
}

void AppInitializer::Run()
{
	Application_ = new App();
	if (Setup())
	{
		Game_->Init();
		Application_->Run();
	}
	Application_->Close();
}

bool AppInitializer::Setup()
{
	if (!Application_->Init())
	{
		Logger::LogMessage(LogVerbosity::Error, "Application was unable to initialize, will be closing");
		return false;
	}

	BindFunctionCallbacks();

	return true;
}

void AppInitializer::BindFunctionCallbacks()
{
	GameLoopFunc loop = std::bind(&Game::Update, Game_, std::placeholders::_1);
	Application_->SetGameLoop(loop);

	GameDrawFunc draw = std::bind(&Game::Draw, Game_, std::placeholders::_1);
	Application_->SetGameDraw(draw);

	GameInputFunc input = std::bind(&Game::HandleInput, Game_,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4);
	Application_->SetGameInput(input);

	GameCursorPosFunc cursor = std::bind(&Game::HandleMousePosition, Game_, std::placeholders::_1, std::placeholders::_2);
	Application_->SetGameCursorFunc(cursor);

	GameMouseInputFunc mouse = std::bind(&Game::HandleMouseInput, Game_, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	Application_->SetGameMouseInputFunc(mouse);
}
