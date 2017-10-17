#include "d3dEngineImpl.h"
#include "d3dUtil.h"

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

D3DEngineImpl::D3DEngineImpl()
	: m_pManager(nullptr)
{

}

D3DEngineImpl::~D3DEngineImpl()
{
	m_Fonts.RemoveAll();
	m_Textures.RemoveAll();

	for (int i = 0; i < m_DefaultElements.GetSize(); ++i)
	{
		auto pElementHolder = m_DefaultElements.GetAt(i);
		SAFE_DELETE(pElementHolder);
	}

	m_DefaultElements.RemoveAll();
}

// 初始化实现的信息
void D3DEngineImpl::Init(D3D9ResourceManager * pManager, LPCTSTR pszTextureFilename)
{
	m_pManager = pManager;
	SetTexture(0, pszTextureFilename);
	InitDefaultElements();
}

HRESULT D3DEngineImpl::SetDefaultElement(CONTROL_TYPE nControlType, UINT iElement, FontTexElement* pElement)
{
	// If this Element type already exist in the list, simply update the stored Element
	for (int i = 0; i < m_DefaultElements.GetSize(); ++i)
	{
		auto pElementHolder = m_DefaultElements.GetAt(i);

		if (pElementHolder->nControlType == nControlType &&
			pElementHolder->iElement == iElement)
		{
			pElementHolder->Element = *pElement;
			return S_OK;
		}
	}

	// Otherwise, add a new entry
	auto pNewHolder = new (std::nothrow) ElementHolder;
	if (pNewHolder == nullptr)
		return E_OUTOFMEMORY;

	pNewHolder->nControlType = nControlType;
	pNewHolder->iElement = iElement;
	pNewHolder->Element = *pElement;

	HRESULT hr = m_DefaultElements.Add(pNewHolder);
	if (FAILED(hr))
	{
		delete pNewHolder;
	}

	return hr;
}

FontTexElement* D3DEngineImpl::GetDefaultElement(CONTROL_TYPE nControlType, UINT iElement)
{
	for (int i = 0; i < m_DefaultElements.GetSize(); ++i)
	{
		auto pElementHolder = m_DefaultElements.GetAt(i);

		if (pElementHolder->nControlType == nControlType &&
			pElementHolder->iElement == iElement)
		{
			return &pElementHolder->Element;
		}
	}

	return nullptr;
}

// 初始化默认使用的字体和贴图信息
void D3DEngineImpl::InitDefaultElements()
{
	SetFont(0, TEXT("Arial"), 14, FW_NORMAL);

	FontTexElement Element;
	RECT rcTexture;

	// Static
	Element.SetFont(0);
	Element.FontColor.States[STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);

	// Assign the Element
	SetDefaultElement(CONTROL_STATIC, 0, &Element);

	// Button
	SetRect(&rcTexture, 0, 0, 136, 54);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0);
	Element.TextureColor.States[STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[STATE_PRESSED] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.FontColor.States[STATE_MOUSEOVER] = D3DCOLOR_ARGB(255, 0, 0, 0);

	// Assign the Element
	SetDefaultElement(CONTROL_BUTTON, 0, &Element);

	// Button - Fill layer
	SetRect(&rcTexture, 136, 0, 252, 54);
	Element.SetTexture(0, &rcTexture, D3DCOLOR_ARGB(0, 255, 255, 255));
	Element.TextureColor.States[STATE_MOUSEOVER] = D3DCOLOR_ARGB(160, 255, 255, 255);
	Element.TextureColor.States[STATE_PRESSED] = D3DCOLOR_ARGB(60, 0, 0, 0);
	Element.TextureColor.States[STATE_FOCUS] = D3DCOLOR_ARGB(30, 255, 255, 255);

	// Assign the Element
	SetDefaultElement(CONTROL_BUTTON, 1, &Element);

	// CheckBox - Box
	SetRect(&rcTexture, 0, 54, 27, 81);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER);
	Element.FontColor.States[STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);
	Element.TextureColor.States[STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[STATE_PRESSED] = D3DCOLOR_ARGB(255, 255, 255, 255);

	// Assign the Element
	SetDefaultElement(CONTROL_CHECKBOX, 0, &Element);

	// CheckBox - Check
	SetRect(&rcTexture, 27, 54, 54, 81);
	Element.SetTexture(0, &rcTexture);

	// Assign the Element
	SetDefaultElement(CONTROL_CHECKBOX, 1, &Element);

	// RadioButton - Box
	SetRect(&rcTexture, 54, 54, 81, 81);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER);
	Element.FontColor.States[STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);
	Element.TextureColor.States[STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.TextureColor.States[STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.TextureColor.States[STATE_PRESSED] = D3DCOLOR_ARGB(255, 255, 255, 255);

	// Assign the Element
	SetDefaultElement(CONTROL_RADIOBUTTON, 0, &Element);

	// RadioButton - Check
	SetRect(&rcTexture, 81, 54, 108, 81);
	Element.SetTexture(0, &rcTexture);

	// Assign the Element
	SetDefaultElement(CONTROL_RADIOBUTTON, 1, &Element);
}

HRESULT D3DEngineImpl::SetFont(UINT index, LPCTSTR strFaceName, LONG height, LONG weight)
{
	assert(m_pManager != nullptr && TEXT("To fix call D3DEngineImpl::Init() first"));

	// Make sure the list is at least as large as the index being set
	for (UINT i = m_Fonts.GetSize(); i <= index; ++i)
	{
		m_Fonts.Add(-1);
	}

	auto iFont = m_pManager->AddFont(strFaceName, height, weight);
	m_Fonts.SetAt(index, iFont);

	return S_OK;
}

FontNode9 * D3DEngineImpl::GetFont(UINT index)
{
	if (nullptr == m_pManager)
		return nullptr;

	return m_pManager->GetFontNode(m_Fonts.GetAt(index));
}

HRESULT D3DEngineImpl::SetTexture(UINT index, LPCTSTR strFilename)
{
	assert(m_pManager != nullptr && TEXT("To fix this, call D3DEngineImpl::Init() first."));

	// Make sure the list is at least as large as the index being set
	for (UINT i = m_Textures.GetSize(); i <= index; ++i)
	{
		m_Textures.Add(-1);
	}

	int iTexture = m_pManager->AddTexture(strFilename);

	m_Textures.SetAt(index, iTexture);
	return S_OK;
}

TextureNode9 * D3DEngineImpl::GetTexture(UINT index)
{
	if (nullptr == m_pManager)
		return nullptr;

	return m_pManager->GetTextureNode(m_Textures.GetAt(index));
}
