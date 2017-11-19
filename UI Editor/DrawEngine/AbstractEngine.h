#ifndef ABSTRACT_ENGINE_H
#define ABSTRACT_ENGINE_H

/*
 * 文件名：AbstractEngine
 * 作用：对于同一个控件，不同窗口，或者不同情况下，可能需要实现不同的绘制效果，
 * 这里抽象不同的实现效果
 */

#include <memory>
#include "AbstractEngineImpl.h"

class AbstractEngine
{
public:
	AbstractEngine() { }
	virtual ~AbstractEngine() {}

	// 初始化控件的贴图字体属性
	virtual HRESULT InitControl(WindowControl* pControl) 
	{ 
		return m_engineImpl->InitControl(pControl); 
	}
	// 绘制函数
	virtual HRESULT DrawRectLine(RECT* pRect, D3DCOLOR color)
	{
		return m_engineImpl->DrawRectLine(pRect, color);
	}
	virtual HRESULT DrawRect(RECT* pRect, D3DCOLOR color)
	{ 
		return m_engineImpl->DrawRect(pRect, color); 
	}
	virtual HRESULT DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR color) 
	{ 
		return m_engineImpl->DrawPolyLine(apPoints, nNumPoints, color); 
	}
	virtual HRESULT DrawSprite(FontTexElement* pElement, RECT* prcDest) 
	{ 
		return m_engineImpl->DrawSprite(pElement, prcDest); 
	}
	virtual HRESULT CalcTextRect(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, int nCount) 
	{ 
		return m_engineImpl->CalcTextRect(strText, pElement, prcDest, nCount); 
	}
	// 在指定位置绘制文字
	virtual HRESULT DrawRectText(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, bool bShadow = false,
		int nCount = -1) 
	{
		return m_engineImpl->DrawRectText(strText, pElement, prcDest, bShadow, nCount);
	}

	// 渲染控件之前准备
	virtual void RenderControlsBefore() 
	{
		m_engineImpl->RenderControlsBefore();
	}
	// 渲染控件之后的处理
	virtual void RenderControlsEnd() 
	{
		m_engineImpl->RenderControlsEnd();
	}

	// 每帧检测状态
	virtual bool checkEveryFrame() { return true; }

protected:
	void SetEngineImpl(AbstractEngineImpl* engineImpl) { m_engineImpl.reset(engineImpl); }

	const std::unique_ptr<AbstractEngineImpl>& GetEngineImpl() const { return m_engineImpl; }

protected:
	std::unique_ptr<AbstractEngineImpl> m_engineImpl;
};


#endif	// ABSTRACT_ENGINE_H
