#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

/*
 * 文件名：ButtonControl
 * 作用：实现Button类型窗口的渲染
 */

#include "StaticControl.h"

class ButtonControl : public StaticControl
{
public:
	ButtonControl();
	~ButtonControl() override { }

	void Render(AbstractEngine* engine, float fElapsedTime) override;

	// 设置当前是否处于按下状态
	void SetPressed(bool pressed) { m_bPressed = pressed; }
	bool GetPressed() const { return m_bPressed; }

	// 设置当前鼠标是否在控件上
	void SetMouseOver(bool mouseOver) { m_bMouseOver = mouseOver; }
	bool GetMouseOver() const { return m_bMouseOver; }

protected:
	// 鼠标是否在控件上
	bool m_bMouseOver;
	// 是否处于按下状态
	bool m_bPressed;
};

#endif	// BUTTON_CONTROL_H
