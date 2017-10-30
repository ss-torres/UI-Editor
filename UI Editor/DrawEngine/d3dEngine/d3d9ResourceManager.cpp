#include "d3d9ResourceManager.h"
#include <TCHAR.h>
#include "d3dUtil.h"

D3D9ResourceManager::D3D9ResourceManager()
{
}

D3D9ResourceManager::~D3D9ResourceManager()
{
	OnD3DDestroyDevice();
}

HRESULT D3D9ResourceManager::OnD3DCreateDevice(LPDIRECT3DDEVICE9 pd3dDevice)
{
	HRESULT hr = S_OK;
	
	m_pd3d9Device = pd3dDevice;

	for (int i = 0; i < m_FontCache.GetSize(); ++i)
	{
		hr = CreateFont9(i);
		if (FAILED(hr))
			return hr;
	}

	for (int i = 0; i < m_TextureCache.GetSize(); ++i)
	{
		hr = CreateTexture9(i);
		if (FAILED(hr))
			return hr;
	}

	hr = D3DXCreateSprite(pd3dDevice, &m_pSprite);
	if (FAILED(hr))
		return HR_ERR_MSGBOX(TEXT("D3DXCreateSprite"), hr);

	return S_OK;
}

HRESULT D3D9ResourceManager::OnD3DResetDevice()
{
	HRESULT hr = S_OK;

	for (int i = 0; i < m_FontCache.GetSize(); ++i)
	{
		auto pFontNode = m_FontCache.GetAt(i);

		if (pFontNode->pFont9)
			pFontNode->pFont9->OnResetDevice();
	}

	if (m_pSprite)
		m_pSprite->OnResetDevice();

	HR_RETURN(m_pd3d9Device->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock));

	return S_OK;
}

void D3D9ResourceManager::OnD3DLostDevice()
{
	for (int i = 0; i < m_FontCache.GetSize(); ++i)
	{
		auto pFontNode = m_FontCache.GetAt(i);

		if (pFontNode->pFont9)
			pFontNode->pFont9->OnLostDevice();
	}

	if (m_pSprite)
		m_pSprite->OnLostDevice();

	SAFE_RELEASE(m_pStateBlock);
}

void D3D9ResourceManager::OnD3DDestroyDevice()
{
	m_pd3d9Device = NULL;

	// Release the resources but don't clear the cache, as these will need to be
	// recreated if the device is recreated
	for (auto& value : m_FontCache)
	{
		SAFE_RELEASE(value->pFont9);
		SAFE_DELETE(value);
	}

	for (auto& value : m_TextureCache)
	{
		SAFE_RELEASE(value->pTexture9);
		SAFE_DELETE(value);
	}

	SAFE_RELEASE(m_pSprite);

	SAFE_RELEASE(m_pStateBlock);
}

int D3D9ResourceManager::AddFont(LPCTSTR strFacename, LONG height, LONG weight)
{
	// See if this font already exists
	for (int i = 0; i < m_FontCache.GetSize(); ++i)
	{
		auto pFontNode = m_FontCache.GetAt(i);
		auto nLen = _tcsnlen(strFacename, MAX_PATH);
		if (0 == _tcsnicmp(pFontNode->strFace, strFacename, nLen) &&
			pFontNode->nHeight == height &&
			pFontNode->nWeight == weight)
		{
			return i;
		}
	}

	// Add a new font and try to create it
	auto pNewFontNode = new (std::nothrow) FontNode9;
	if (pNewFontNode == nullptr)
		return -1;

	ZeroMemory(pNewFontNode, sizeof(FontNode9));
	_tcscpy_s(pNewFontNode->strFace, MAX_PATH, strFacename);
	pNewFontNode->nHeight = height;
	pNewFontNode->nWeight = weight;
	m_FontCache.Add(pNewFontNode);

	int iFont = m_FontCache.GetSize() - 1;

	// If a device is available, try to create immediately
	if (m_pd3d9Device)
		CreateFont9(iFont);

	return iFont;
}

int D3D9ResourceManager::AddTexture(LPCTSTR strFilename)
{
	// See if this texture already exists
	for (int i = 0; i < m_TextureCache.GetSize(); ++i)
	{
		auto pTextureNode = m_TextureCache.GetAt(i);
		auto nLen = _tcsnlen(strFilename, MAX_PATH);
		if (0 == _tcsnicmp(pTextureNode->strFilename, strFilename, nLen))
		{
			return i;
		}
	}

	// Add a new texture and try to create it
	auto pNewTextureNode = new (std::nothrow) TextureNode9;
	if (pNewTextureNode == nullptr)
		return -1;

	ZeroMemory(pNewTextureNode, sizeof(TextureNode9));
	_tcscpy_s(pNewTextureNode->strFilename, MAX_PATH, strFilename);

	m_TextureCache.Add(pNewTextureNode);
	
	int iTexture = m_TextureCache.GetSize() - 1;

	// If a device is avaiable, try to create immediately
	if (m_pd3d9Device)
		CreateTexture9(iTexture);

	return iTexture;
}

HRESULT D3D9ResourceManager::CreateFont9(UINT index)
{
	HRESULT hr = S_OK;

	FontNode9* pFontNode = m_FontCache.GetAt(index);

	SAFE_RELEASE(pFontNode->pFont9);

	HR_RETURN(D3DXCreateFont(m_pd3d9Device, pFontNode->nHeight, 0, pFontNode->nWeight, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		pFontNode->strFace, &pFontNode->pFont9));

	return S_OK;
}

HRESULT D3D9ResourceManager::CreateTexture9(UINT index)
{
	HRESULT hr = S_OK;

	TextureNode9* pTextureNode = m_TextureCache.GetAt(index);

	D3DXIMAGE_INFO info;

	if (pTextureNode->strFilename[0] == 0)
		return S_OK;

	// Create texture from file
	hr = D3DXCreateTextureFromFileEx(m_pd3d9Device, pTextureNode->strFilename, D3DX_DEFAULT, D3DX_DEFAULT,
		1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		&info, NULL, &pTextureNode->pTexture9);
	if (FAILED(hr))
	{
		return HR_ERR_MSGBOX(TEXT("D3DXCreateTextureFromFileEx"), hr);
	}
	
	// Store dimensions
	pTextureNode->dwWidth = info.Width;
	pTextureNode->dwHeight = info.Height;

	return S_OK;
}


