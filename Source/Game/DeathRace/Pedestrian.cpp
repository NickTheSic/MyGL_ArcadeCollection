#include "GamePCH.h"
#include "Pedestrian.h"

#ifdef _WINDOWS
#include <Windows.h>
#include "mmsystem.h"
#endif

void Pedestrian::Init()
{
	float width = 12.0f;
	float height = 25.0f;

	m_Mesh->MakeRectangle(width, height, ColorList::WHITE, GL_LINE_LOOP);

	m_Scale = { width + 1, height + 1 };

	GameObject::Init();

	Reset();
}

void Pedestrian::Update(float delta)
{
	if (bIsDead) return;

	m_Position.x += m_Movement.x * delta * 100.0f;
	m_Position.y += m_Movement.y * delta * 100.0f;

	ScreenWrapPosition();

	m_Timer -= delta;

	if (m_Timer < 0)
		UpdateDirection();
}

void Pedestrian::Reset()
{
	m_Position.x = Random::RandomFloat(30.0f, INITIAL_WINDOW_WIDTH - 30.0f);
	m_Position.y = Random::RandomFloat(30.0f, INITIAL_WINDOW_HEIGHT - 30.0f);

	bIsDead = false;

	UpdateDirection();
}

bool Pedestrian::GetIsDead()
{
	return bIsDead;
}

void Pedestrian::HandleBeginOverlap()
{
	if (bIsDead) return;

	m_Mesh->SetColor(ColorList::RED);
	bIsDead = true;

#ifdef _WINDOWS
	PlaySound(TEXT("Data/Audio/Destroy.wav"), NULL, SND_FILENAME | SND_ASYNC);
#endif
}

void Pedestrian::UpdateDirection()
{
	m_Direction = Random::RandomFloat(0.0f, 6.28f);

	m_Movement.x = sinf(m_Direction);
	m_Movement.y = cosf(m_Direction);

	m_Timer = Random::RandomFloat(0.65f, 4.5f);
}
