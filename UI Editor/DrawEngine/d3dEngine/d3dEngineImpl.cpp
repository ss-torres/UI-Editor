#include "d3dEngineImpl.h"
#include "d3dUtil.h"
#include "../Controls/WindowControl.h"

struct SCREEN_VERTEX
{
	float x, y, z, h;
	D3DCOLOR color;
	float tu, tv;

	static DWORD FVF;
};

DWORD SCREEN_VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

D3DEngineImpl::D3DEngineImpl()
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

// 初始化控件的贴图字体属性
HRESULT D3DEngineImpl::InitControl(WindowControl * pControl)
{
	if (pControl == nullptr)
		return E_INVALIDARG;

	// Look for a default Element entries
	for (auto i = 0; i < m_DefaultElements.GetSize(); ++i)
	{
		auto pElementHolder = m_DefaultElements.GetAt(i);
		if (pElementHolder->nControlType == pControl->GetControlType())
			pControl->SetElement(pElementHolder->iElement, &pElementHolder->Element);
	}

	HR_RETURN(pControl->OnInit());

	return S_OK;
}

// 绘制函数
HRESULT D3DEngineImpl::DrawRectLine(RECT * pRect, D3DCOLOR color)
{
	POINT tl = { pRect->left, pRect->top };
	POINT tr = { pRect->right, pRect->top };
	POINT br = { pRect->right, pRect->bottom };
	POINT bl = { pRect->left, pRect->bottom };
	POINT points[5] = { tl, tr, br, bl, tl };
	return DrawPolyLine(points, sizeof(points) / sizeof(points[0]), color);
}

HRESULT D3DEngineImpl::DrawRect(RECT* pRect, D3DCOLOR color)
{
	RECT rcScreen = *pRect;

	SCREEN_VERTEX vertices[4] =
	{
		(float)rcScreen.left - 0.5f,  (float)rcScreen.top - 0.5f, 0.5f, 1.0f, color, 0, 0,
		(float)rcScreen.right - 0.5f, (float)rcScreen.top - 0.5f, 0.5f, 1.0f, color, 0, 0,
		(float)rcScreen.right - 0.5f, (float)rcScreen.bottom - 0.5f, 0.5f, 1.0f, color, 0, 0,
		(float)rcScreen.left - 0.5f,  (float)rcScreen.bottom - 0.5f, 0.5f, 1.0f, color, 0, 0
	};

	auto pd3dDevice = m_pManager->GetD3DDevice();

	// Since we're doing our own drawing here we need to flush the sprites
	m_pManager->GetSprite()->Flush();
	IDirect3DVertexDeclaration9* pDecl = nullptr;
	HR(pd3dDevice->GetVertexDeclaration(&pDecl));		// Preserve the sprite's current vertex decl
	HR(pd3dDevice->SetFVF(SCREEN_VERTEX::FVF));

	HR(pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2));
	HR(pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2));

	pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(SCREEN_VERTEX));

	pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Restore the vertex decl
	pd3dDevice->SetVertexDeclaration(pDecl);
	SAFE_RELEASE(pDecl);

	return S_OK;
}

HRESULT D3DEngineImpl::DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR color)
{
	auto vertices = new (std::nothrow) SCREEN_VERTEX[nNumPoints];
	if (vertices == nullptr)
		return E_OUTOFMEMORY;

	auto pVertex = vertices;
	auto pt = apPoints;
	for (UINT i = 0; i < nNumPoints; ++i)
	{
		pVertex->x = (float)pt->x;
		pVertex->y = (float)pt->y;
		pVertex->z = 0.5f;
		pVertex->h = 1.0f;
		pVertex->color = color;
		pVertex->tu = 0.0f;
		pVertex->tv = 0.0f;

		++pVertex;
		++pt;
	}

	auto pd3dDevice = m_pManager->GetD3DDevice();

	// Since we're doing our own drawing here we need to flush the sprites
	m_pManager->GetSprite()->Flush();
	IDirect3DVertexDeclaration9* pDecl = nullptr;
	pd3dDevice->GetVertexDeclaration(&pDecl);		// Preserve the sprite's current vertex decl
	pd3dDevice->SetFVF(SCREEN_VERTEX::FVF);

	pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);

	pd3dDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, nNumPoints - 1, vertices, sizeof(SCREEN_VERTEX));

	pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// Restore the vertex decl
	pd3dDevice->SetVertexDeclaration(pDecl);
	SAFE_RELEASE(pDecl);

	SAFE_DELETE_ARRAY(vertices);
	return S_OK;
}

HRESULT D3DEngineImpl::DrawSprite(FontTexElement* pElement, RECT* prcDest)
{
	// No need to draw fully transparent layers
	if (pElement->TextureColor.Current.a == 0)
		return S_OK;

	RECT rcTexture = pElement->rcTexture;
	RECT rcScreen = *prcDest;

	auto pTextureNode = GetTexture(pElement->iTexture);
	if (pTextureNode == nullptr)
		return E_FAIL;

	float fScaleX = (float)RectWidth(rcScreen) / RectWidth(rcTexture);
	float fScaleY = (float)RectHeight(rcScreen) / RectHeight(rcTexture);

	D3DXMATRIXA16 matTransform;
	D3DXMatrixScaling(&matTransform, fScaleX, fScaleY, 1.0f);

	m_pManager->GetSprite()->SetTransform(&matTransform);

	D3DXVECTOR3 vPos((float)rcScreen.left, (float)rcScreen.top, 0.0f);

	vPos.x /= fScaleX;
	vPos.y /= fScaleY;

	return m_pManager->GetSprite()->Draw(pTextureNode->pTexture9, &rcTexture, nullptr, &vPos,
		pElement->TextureColor.Current);
}

HRESULT D3DEngineImpl::CalcTextRect(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, int nCount)
{
	HRESULT hr = S_OK;

	auto pFontNode = GetFont(pElement->iFont);
	if (pFontNode == nullptr)
		return E_FAIL;

	DWORD dwTextFormat = pElement->dwTextFormat | DT_CALCRECT;
	// Since we are only computing the rectangle, we don't need  a sprite.
	if (pFontNode->pFont9)
	{
#if UNICODE
		hr = pFontNode->pFont9->DrawTextW(nullptr, strText, nCount, prcDest, dwTextFormat, pElement->FontColor.Current);
#else
		hr = pFontNode->pFont9->DrawTextW(nullptr, strText, nCount, prcDest, dwTextFormat, pElement->FontColor.Current);
#endif	// UNICODE
		if (FAILED(hr))
			return hr;
	}

	return S_OK;
}

// 在指定位置绘制文字
HRESULT D3DEngineImpl::DrawRectText(LPCTSTR strText, FontTexElement * pElement, RECT * prcDest, bool bShadow, int nCount)
{
	HRESULT hr = S_OK;

	// No need to draw fully transparent layers
	if (pElement->FontColor.Current.a == 0)
		return S_OK;
	
	RECT rcScreen = *prcDest;

	D3DXMATRIX matTransform;
	D3DXMatrixIdentity(&matTransform);
	m_pManager->GetSprite()->SetTransform(&matTransform);

	auto pFontNode = GetFont(pElement->iFont);

	if (bShadow)
	{
		RECT rcShadow = rcScreen;
		OffsetRect(&rcShadow, 1, 1);
#if UNICODE
		hr = pFontNode->pFont9->DrawTextW(m_pManager->GetSprite(), strText, nCount, &rcShadow, pElement->dwTextFormat,
			D3DCOLOR_ARGB(DWORD(pElement->FontColor.Current.a * 255), 0, 0, 0));
#else
		hr = pFontNode->pFont9->DrawTextA(m_pManager->GetSprite(), strText, nCount, &rcShadow, pElement->dwTextFormat,
			D3DCOLOR_ARGB(DWORD(pElement->FontColor.Current.a * 255), 0, 0, 0));
#endif	// UNICODE
		if (FAILED(hr))
			return hr;
	}

#if UNICODE
	hr = pFontNode->pFont9->DrawTextW(m_pManager->GetSprite(), strText, nCount, &rcScreen, pElement->dwTextFormat,
		pElement->FontColor.Current);
#else
	hr = pFontNode->pFont9->DrawTextA(m_pManager->GetSprite(), strText, nCount, &rcScreen, pElement->dwTextFormat,
		pElement->FontColor.Current);
#endif	// UNICODE
	if (FAILED(hr))
		return hr;

	return S_OK;
}

// 渲染控件之前准备
void D3DEngineImpl::RenderControlsBefore()
{
	auto pd3dDevice = m_pManager->GetD3DDevice();

	HR(pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

	HR(pd3dDevice->BeginScene());

	// Set up a state block here and restore it when finished drawing all the controls
	m_pManager->GetStateBlock()->Capture();

	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pd3dDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
	pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED);
	pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	auto pTextureNode = GetTexture(0);
	pd3dDevice->SetTexture(0, pTextureNode->pTexture9);

	m_pManager->GetSprite()->Begin(D3DXSPRITE_DONOTSAVESTATE);
}

// 渲染控件之后的处理
void D3DEngineImpl::RenderControlsEnd()
{
	m_pManager->GetSprite()->End();

	m_pManager->GetStateBlock()->Apply();

	auto pd3dDevice = m_pManager->GetD3DDevice();

	HR(pd3dDevice->EndScene());

	// Present the backbuffer.
	HR(pd3dDevice->Present(0, 0, 0, 0));
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
