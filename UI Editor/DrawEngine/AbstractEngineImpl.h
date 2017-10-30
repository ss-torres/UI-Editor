#ifndef ABSTRACT_ENGINE_IMPL_H
#define ABSTRACT_ENGINE_IMPL_H

/*
 * 文件名：AbstractEngineImpl
 * 作用：提供EngineImpl可使用接口，抽象化不同实现能够提供的功能
 * 用来隐藏绘制功能使用的系统实现
 */

#include <winerror.h>
#include "EngineImplDefine.h"

class AbstractEngineImpl
{
public:
	AbstractEngineImpl() {}
	virtual ~AbstractEngineImpl() {}

	// 绘制函数
	virtual HRESULT DrawRect(RECT* pRect, D3DCOLOR color) { return S_OK; }
	virtual HRESULT DrawPolyLine(POINT* apPoints, UINT nNumPoints, D3DCOLOR color) { return S_OK; }
	virtual HRESULT DrawSprite(FontTexElement* pElement, RECT* prcDest) { return S_OK; }
	virtual HRESULT CalcTextRect(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, int nCount) { return S_OK; }
	// 在指定位置绘制文字
	virtual HRESULT DrawRectText(LPCTSTR strText, FontTexElement* pElement, RECT* prcDest, bool bShadow = false,
		int nCount = -1) {
		return S_OK;
	}

	// 渲染控件之前准备
	virtual void RenderControlsBefore() {}
	// 渲染控件之后的处理
	virtual void RenderControlsEnd() {}
};

#endif	// ABSTRACT_ENGINE_IMPL_H