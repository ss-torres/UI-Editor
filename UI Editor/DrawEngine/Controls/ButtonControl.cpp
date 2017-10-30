#include "ButtonControl.h"
#include "../AbstractEngine.h"

ButtonControl::ButtonControl()
	: m_bMouseOver(false),
	m_bPressed(false)
{

}

void ButtonControl::Render(AbstractEngine* engine, float fElapsedTime)
{
	int nOffsetX = 0;
	int nOffsetY = 0;

	CONTROL_STATE iState = STATE_NORMAL;

	if(GetEnabled() == false)
	{
		iState = STATE_DISABLED;
	}
	else if (GetPressed())
	{
		iState = STATE_PRESSED;

		nOffsetX = 1;
		nOffsetY = 2;
	}
	else if (GetMouseOver())
	{
		iState = STATE_MOUSEOVER;

		nOffsetX = -1;
		nOffsetY = -2;
	}
	
	// Background fill layer
	auto pElement = m_Elements.GetAt(0);

	float fBlendRate = (iState == STATE_PRESSED) ? 0.0f : 0.8f;

	RECT rcWindow = GetRect();
	OffsetRect(&rcWindow, nOffsetX, nOffsetY);

	// Blend current color
	pElement->TextureColor.Blend(iState, fElapsedTime, fBlendRate);
	pElement->FontColor.Blend(iState, fElapsedTime, fBlendRate);

	engine->DrawSprite(pElement, &rcWindow);
	engine->DrawRectText(m_strText, pElement, &rcWindow, false, -1);

	// Main button
	pElement = m_Elements.GetAt(1);

	// Blend current color
	pElement->TextureColor.Blend(iState, fElapsedTime, fBlendRate);
	pElement->FontColor.Blend(iState, fElapsedTime, fBlendRate);

	engine->DrawSprite(pElement, &rcWindow);
	engine->DrawRectText(m_strText, pElement, &rcWindow, false, -1);
}
