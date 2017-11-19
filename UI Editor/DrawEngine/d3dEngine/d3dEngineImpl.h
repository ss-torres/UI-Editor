#ifndef D3D_ENGINE_IMPL_H
#define D3D_ENGINE_IMPL_H

/*
 * 文件名：d3dEngineImpl
 * 作用：提供一些实现d3dEngine的功能函数
 * 说明：该部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
 * 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
 */

#include "../AbstractEngineImpl.h"
#include "d3d9ResourceManager.h"

class D3D9ResourceManager;

class D3DEngineImpl : public AbstractEngineImpl
{
public:
	D3DEngineImpl();
	~D3DEngineImpl() override;

	// 初始化实现的信息，该对象负责pManager指向对象的清理
	void Init(D3D9ResourceManager* pManager, LPCTSTR pszTextureFilename);

	// Access the default display Elments used when adding new controls
	HRESULT SetDefaultElement(CONTROL_TYPE nControlType, UINT iElement, FontTexElement* pElement);
	FontTexElement* GetDefaultElement(CONTROL_TYPE nControlType, UINT iElement);

	// 初始化控件的贴图字体属性
	HRESULT InitControl(WindowControl* pControl) override;
	// 绘制函数
	HRESULT DrawRectLine(RECT* pRect, D3DCOLOR color) override;
	HRESULT DrawRect(RECT* pRect, D3DCOLOR color) override;
	HRESULT DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR color) override;
	HRESULT DrawSprite(FontTexElement* pElement, RECT* prcDest) override;
	HRESULT CalcTextRect(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, int nCount) override;
	// 在指定位置绘制文字
	HRESULT DrawRectText(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, bool bShadow = false,
		int nCount = -1) override;

	// 渲染控件之前准备
	void RenderControlsBefore() override;
	// 渲染控件之后的处理
	void RenderControlsEnd() override;

private:
	// 初始化默认使用的字体和贴图信息
	void InitDefaultElements();
	// 添加共享的字体信息
	HRESULT SetFont(UINT index, LPCTSTR strFaceName, LONG height, LONG weight);
	FontNode9* GetFont(UINT index);
	// 添加共享的贴图信息
	HRESULT SetTexture(UINT index, LPCTSTR strFilename);
	TextureNode9* GetTexture(UINT index);

private:
	D3D9ResourceManager* m_pManager = nullptr;
	// m_TextureCache中的序号
	CGrowableArray<int> m_Textures;
	// m_FontCache中的序号
	CGrowableArray<int> m_Fonts;
	// 用来记录所有不同控件类型默认的字体贴图信息
	CGrowableArray <ElementHolder*> m_DefaultElements;

	ID3DXFont* mFont = nullptr;
};

#endif	// D3D_ENGINE_IMPL_H
