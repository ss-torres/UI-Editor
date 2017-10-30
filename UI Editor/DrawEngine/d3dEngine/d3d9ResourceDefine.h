#ifndef D3D9_RESOURCE_DEFINE_H
#define D3D9_RESOURCE_DEFINE_H

#include <d3dx9.h>

// 记录纹理信息
struct TextureNode9
{
	TCHAR strFilename[MAX_PATH];
	DWORD dwWidth;
	DWORD dwHeight;
	IDirect3DTexture9* pTexture9;
};

// 记录字体信息
struct FontNode9
{
	TCHAR strFace[MAX_PATH];
	LONG nHeight;
	LONG nWeight;
	ID3DXFont* pFont9;
};

#endif	// D3D9_RESOURCE_DEFINE_H
