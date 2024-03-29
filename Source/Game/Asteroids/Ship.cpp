#include "GamePCH.h"
#include "Ship.h"
#include "AsteroidsGame.h"

using namespace std;

Ship::Ship(AsteroidsGame* game)
{
	m_pGame = game;

	GameInputFunc input = bind(&Ship::HandleKeyboardInput, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4);
	game->RegisterForInputCallback(input);
}

void Ship::Init()
{
	std::vector<glm::vec2> vertices =
	{
		{  0.0f,  40.0f},
		{ 40.0f, -40.0f},
		{  0.0f, -25.0f},
		{-40.0f, -40.0f},
	};

	m_Scale = { 30, 30 };

	GameObject::Init();

	m_Mesh->Init(vertices, ColorList::WHITE, GL_LINE_LOOP);

	Reset();
}

void Ship::Update(float delta)
{
	m_Rotation += m_RotationDirection * delta * (m_Speed * 0.01f);

	if (bDoThrust)
	{
		m_Speed += delta * 50;
		if (m_Speed > 150.0f) m_Speed = 150.0f;

		m_Velocity.y = cosf(-m_Rotation);
		m_Velocity.x = sinf(-m_Rotation);
	}
	else
	{
		m_Speed -= m_Speed * 0.5f * delta;
	}

	m_Position.x += m_Velocity.x * float(delta) * m_Speed;
	m_Position.y += m_Velocity.y * float(delta) * m_Speed;

	ScreenWrapPosition();
}

void Ship::Reset()
{
	m_Position = {
		App::Get().GetWindowWidth() * 0.5,
		App::Get().GetWindowHeight() * 0.5
	};

	m_Health = 3;

	HandleHealth();

	m_Speed = 0.0f;
	m_Rotation = 0.0f;

	bIsActive = true;
}

void Ship::HandleBeginOverlap()
{
	m_Health--;

	HandleHealth();
}

void Ship::HandleKeyboardInput(int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT:
			[[fallthrough]];
		case GLFW_KEY_A:
			m_RotationDirection += 1.0f;
			break;

		case GLFW_KEY_RIGHT:
			[[fallthrough]];
		case GLFW_KEY_D:
			m_RotationDirection += -1.0f;
			break;

		case GLFW_KEY_UP:
			[[fallthrough]];
		case GLFW_KEY_W:
			bDoThrust = true;
			break;

		case GLFW_KEY_DOWN:
			[[fallthrough]];
		case GLFW_KEY_S:
			break;

		case GLFW_KEY_SPACE:
			m_pGame->ShootBullet(m_Rotation, m_Position);
			break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_LEFT: [[fallthrough]];
		case GLFW_KEY_A:
			m_RotationDirection += -1.0f;
			break;
		case GLFW_KEY_RIGHT: [[fallthrough]];
		case GLFW_KEY_D: 
			m_RotationDirection += 1.0f;
			break;
		case GLFW_KEY_UP: [[fallthrough]];
		case GLFW_KEY_W: 
			bDoThrust = false;
			break;
		case GLFW_KEY_DOWN: [[fallthrough]];
		case GLFW_KEY_S:
			break;
		}
	}
}

void Ship::HandleHealth()
{
	if (m_Health > 0)
	{
		m_Mesh->SetColor(HealthColors[m_Health - 1]);
	}
	else
	{
		bIsActive = false;
		m_pGame->TriggerReset();
	}
}
