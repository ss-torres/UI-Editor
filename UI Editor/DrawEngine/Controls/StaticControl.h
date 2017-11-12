#ifndef STATIC_CONTROL_H
#define STATIC_CONTROL_H

/*
 * 文件名：StaticControl
 * 作用：实现Static类型窗口的渲染
 * 说明：部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
 * 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
 */

#include "WindowControl.h"

class StaticControl : public WindowControl
{
public:
	StaticControl();
	~StaticControl() override {}

	// 重写渲染函数
	void Render(AbstractEngine* engine, float fElapsedTime) override;

	// 获取窗口类型
	CONTROL_TYPE GetControlType() const override { return CONTROL_STATIC; }

	const LABEL_TYPE* GetText()
	{
		return m_strText;
	}

	// 设置Static的内容，拷贝到对象中
	// 注意：当前实现在DrawControlManager中可能存在性能问题
	HRESULT SetText(const LABEL_TYPE* strText);

protected:
	const LABEL_TYPE* m_strText;		// Window text
};

inline HRESULT StaticControl::SetText(const LABEL_TYPE* strText)
{
	if (strText == nullptr)
	{
		m_strText = nullptr;
		return S_OK;
	}

	m_strText = strText;
	return S_OK;
}

#endif	// STATIC_CONTROL_H
