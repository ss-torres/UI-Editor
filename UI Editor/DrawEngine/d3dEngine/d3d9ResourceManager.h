#ifndef D3D9_RESOURCE_MANAGER_H
#define D3D9_RESOURCE_MANAGER_H

/*
 * 文件名：d3d9ResourceManager
 * 作用：用来管理窗口渲染中用到的字体和贴图
 * 说明：该部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
 * 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
 */

#include <d3dx9.h>
#include "d3d9ResourceDefine.h"
#include "../CGrowableArray.h"

class D3D9ResourceManager
{
public:
	D3D9ResourceManager();
	~D3D9ResourceManager();

	HRESULT OnD3DCreateDevice(LPDIRECT3DDEVICE9 pd3dDevice);
	HRESULT OnD3DResetDevice();
	void OnD3DLostDevice();
	void OnD3DDestroyDevice();

	IDirect3DDevice9* GetD3DDevice()
	{
		return m_pd3d9Device;
	}

	// 用来获取绘制的Sprite
	ID3DXSprite* GetSprite()
	{
		return m_pSprite;
	}

	// 用来记录状态的对象
	IDirect3DStateBlock9* GetStateBlock()
	{
		return m_pStateBlock;
	}

	FontNode9* GetFontNode(int iIndex)
	{
		return m_FontCache.GetAt(iIndex);
	}

	TextureNode9* GetTextureNode(int iIndex)
	{
		return m_TextureCache.GetAt(iIndex);
	}

	int AddFont(LPCTSTR strFaceName, LONG height, LONG weight);
	int AddTexture(LPCTSTR strFileName);
private:
	HRESULT CreateFont9(UINT index);
	HRESULT CreateTexture9(UINT index);

private:
	IDirect3DDevice9* m_pd3d9Device = nullptr;
	IDirect3DStateBlock9* m_pStateBlock = nullptr;
	ID3DXSprite* m_pSprite = nullptr;

	// 纹理信息
	CGrowableArray<TextureNode9*> m_TextureCache;
	CGrowableArray<FontNode9*> m_FontCache;
};

#endif	// D3D9_RESOURCE_MANAGER_H
