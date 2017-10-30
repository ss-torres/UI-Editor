#ifndef STATIC_CONTROL_H
#define STATIC_CONTROL_H

/*
 * 文件名：StaticControl
 * 作用：实现Static类型窗口的渲染
 * 说明：部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
 * 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
 */

#include "WindowControl.h"
#include <tchar.h>

class StaticControl : public WindowControl
{
public:
	StaticControl();
	~StaticControl() override {}

	// 重写渲染函数
	void Render(AbstractEngine* engine, float fElapsedTime) override;

	HRESULT GetTextCopy(__out_ecount(bufferCount) LPTSTR strDest,
		UINT bufferCount);

	LPCTSTR GetText()
	{
		return m_strText;
	}

	HRESULT SetText(LPCTSTR strText);

protected:
	TCHAR m_strText[MAX_PATH];		// Window text
};

inline HRESULT StaticControl::GetTextCopy(__out_ecount(bufferCount) LPTSTR strDest,
	UINT bufferCount)
{
	// Validate incoming parameters
	if (strDest == nullptr || bufferCount == 0)
	{
		return E_INVALIDARG;
	}

	// Copy the window text
	_tcscpy_s(strDest, bufferCount, m_strText);

	return S_OK;
}

inline HRESULT StaticControl::SetText(LPCTSTR strText)
{
	if (strText == nullptr)
	{
		m_strText[0] = 0;
		return S_OK;
	}

	_tcscpy_s(m_strText, MAX_PATH, strText);
	return S_OK;
}

#endif	// STATIC_CONTROL_H
