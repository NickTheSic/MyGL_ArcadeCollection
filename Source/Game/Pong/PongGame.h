#pragma once
#include <GamePCH.h>

class PongGame : public Game
{
public:
	PongGame();
	virtual ~PongGame();

	void DisplayRules();

	void Init() override;
	void Update(float delta) override;

protected:
	
};
