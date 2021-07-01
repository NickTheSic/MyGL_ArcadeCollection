#pragma once
#include <iostream>
#include <memory>
#include "../ProjectConfig.h"

FrameworkImpl template class FrameworkAPI std::shared_ptr<class App>;

class FrameworkAPI AppInitializer
{
public:
	AppInitializer(class IGameClass* game);

	void Run();

	bool Setup();

private:

	std::shared_ptr<class App> Application_;
	class IGameClass* Game_;
};