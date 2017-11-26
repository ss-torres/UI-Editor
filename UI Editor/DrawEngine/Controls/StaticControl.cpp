#include "StaticControl.h"
#include "../AbstractEngine.h"

StaticControl::StaticControl()
	: WindowControl()
{
	ZeroMemory(&m_strText, sizeof(m_strText));
}

// ÖØÐ´äÖÈ¾º¯Êý
void StaticControl::Render(AbstractEngine* engine, float fElapsedTime)
{
	CONTROL_STATE iState = STATE_NORMAL;

	if (GetEnabled() == false)
		iState = STATE_DISABLED;

	auto pElement = m_Elements.GetAt(0);

	pElement->FontColor.Blend(iState, fElapsedTime);

	engine->DrawRectText(m_strText->c_str(), pElement, &GetRect(), false, -1);
}
