#ifndef ENGINE_IMPL_DEFINE_H
#define ENGINE_IMPL_DEFINE_H

#include <array>
#include <d3d9.h>
#include <d3dx9.h>

// Enums for pre-defined control types
enum CONTROL_TYPE
{
	CONTROL_BUTTON = 0,
	CONTROL_STATIC,
	CONTROL_CHECKBOX,
	CONTROL_RADIOBUTTON,
	CONTROL_COMBOBOX,
	CONTROL_SLIDER,
	CONTROL_EDITBOX,
	CONTROL_LISTBOX,
	CONTROL_SCROLLBAR
};

enum CONTROL_STATE
{
	STATE_NORMAL = 0,
	STATE_DISABLED,
	STATE_HIDDEN,
	STATE_FOCUS,
	STATE_MOUSEOVER,
	STATE_PRESSED
};

const int MAX_CONTROL_STATES = 6;

struct BlendColor
{
	void Init(D3DCOLOR defaultColor, D3DCOLOR disabledColor = D3DCOLOR_ARGB(200, 128, 128, 128),
		D3DCOLOR hiddenColor = 0);
	void Blend(CONTROL_STATE iState, float fElapsedTime, float fRate = 0.7f);

	std::array<D3DCOLOR, MAX_CONTROL_STATES> States;		// Modulate colors for all possible control states
	D3DXCOLOR Current;
};

// Contains all the display tweakables for a sub-control
class FontTexElement
{
public:
	void SetTexture(UINT iTexture, RECT* prcTexture,
		D3DCOLOR defaultTextureColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void SetFont(UINT iFont, D3DCOLOR defaultFontColor = D3DCOLOR_ARGB(255, 255, 255, 255),
		DWORD dwTextFormat = DT_CENTER | DT_VCENTER);
	void Refresh();

	UINT iTexture;			// Index of the texture for this Element
	UINT iFont;				// Index of the font for this Element
	DWORD dwTextFormat;		// The format argument to DrawText

	RECT rcTexture;			// Bounding rect of this element on the composite texture

	BlendColor TextureColor;
	BlendColor FontColor;
};

// Contains all the display information for a given control type
struct ElementHolder
{
	UINT nControlType;
	UINT iElement;

	FontTexElement Element;
};

// 获取矩形的宽
inline int RectWidth(const RECT& rc)
{
	return (rc.right - rc.left);
}

// 获取矩形的高
inline int RectHeight(const RECT& rc)
{
	return (rc.bottom - rc.top);
}

#endif	// ENGINE_IMPL_DEFINE_H
