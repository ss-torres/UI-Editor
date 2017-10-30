#include "EngineImplDefine.h"

void BlendColor::Init(D3DCOLOR defaultColor, D3DCOLOR disabledColor, D3DCOLOR hiddenColor)
{
	for (decltype(States.size()) i = 0; i != States.size(); ++i)
	{
		States[i] = defaultColor;
	}

	States[STATE_DISABLED] = disabledColor;
	States[STATE_HIDDEN] = hiddenColor;
	Current = hiddenColor;
}

void BlendColor::Blend(CONTROL_STATE iState, float fElapsedTime, float fRate)
{
	D3DXCOLOR destColor = States[iState];
	D3DXColorLerp(&Current, &Current, &destColor, 1.0f - powf(fRate, 30 * fElapsedTime));
}

void FontTexElement::SetTexture(UINT iTexture, RECT * prcTexture, D3DCOLOR defaultTextureColor)
{
	this->iTexture = iTexture;

	if (prcTexture)
		rcTexture = *prcTexture;
	else
		SetRectEmpty(&rcTexture);

	TextureColor.Init(defaultTextureColor);
}

void FontTexElement::SetFont(UINT iFont, D3DCOLOR defaultFontColor, DWORD dwTextFormat)
{
	this->iFont = iFont;
	this->dwTextFormat = dwTextFormat;

	FontColor.Init(defaultFontColor);
}

void FontTexElement::Refresh()
{
	TextureColor.Current = TextureColor.States[STATE_HIDDEN];
	FontColor.Current = FontColor.States[STATE_HIDDEN];
}