#include "Blank.h"

CBlank::CBlank()
{
}

CBlank::~CBlank()
{
}

bool CBlank::LoadContent()
{
	return true;
}

void CBlank::UnloadContent()
{
}

void CBlank::Update(float dt)
{
}

void CBlank::Render()
{
	if (!m_d3dContext)
	{
		return;
	}

	float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };

	m_d3dContext->ClearRenderTargetView(m_backBufferTarget, clearColor);
	m_swapChain->Present(0, 0);
}