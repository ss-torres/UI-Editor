#ifndef WINDOW_CONTROL_H
#define WINDOW_CONTROL_H

/*
 * 文件名：WindowControl
 * 作用：用来实现窗口渲染的功能，通过设置窗口的值，来渲染对应的对象，当需要的数据很多时，可以通过
 * 传递需要渲染窗口的指针，调用对应函数来实现
 * 说明：部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
 * 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
 */

#include "../CGrowableArray.h"
#include <d3d9.h>

class AbstractEngine;
class FontTexElement;

class WindowControl
{
public:
	WindowControl();
	virtual ~WindowControl();

	virtual void Refresh();
	// 渲染函数
	virtual void Render(AbstractEngine* engine, float fElapsedTime) { }

	void SetX(int x) { m_rcBoundingBox.left = x; }
	void SetY(int y) { m_rcBoundingBox.top = y; }
	void SetWidth(int width) { m_rcBoundingBox.right = m_rcBoundingBox.left + width; }
	void SetHeight(int height) { m_rcBoundingBox.bottom = m_rcBoundingBox.top = height; }
	void SetEnable(bool enable) { m_bEnabled = enable; }
	void SetRect(const RECT& boundingBox) { m_rcBoundingBox = boundingBox; }

	int GetX() const { return m_rcBoundingBox.left; }
	int GetY() const { return m_rcBoundingBox.right; }
	int GetWidth() const { return m_rcBoundingBox.right - m_rcBoundingBox.left; }
	int GetHeight() const { return m_rcBoundingBox.bottom - m_rcBoundingBox.top; }
	RECT& GetRect() { return m_rcBoundingBox; }
	bool GetEnabled() const { return m_bEnabled; }

	virtual void SetTextColor(D3DCOLOR Color);

	FontTexElement* GetElement(UINT iElement)
	{
		return m_Elements.GetAt(iElement);
	}

	HRESULT SetElement(UINT iElement, FontTexElement* pElement);

protected:
	// Rectangle defining the active region of the control
	RECT m_rcBoundingBox;
	// 是否为Enable状态
	bool m_bEnabled;

	// All display elements
	CGrowableArray<FontTexElement*> m_Elements;
};

#endif	// WINDOW_CONTROL_H
