#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

/*
 * �ļ�����ButtonControl
 * ���ã�ʵ��Button���Ϳؼ�����Ⱦ
 */

#include "StaticControl.h"

class ButtonControl : public StaticControl
{
public:
	ButtonControl();
	~ButtonControl() override { }

	void Render(AbstractEngine* engine, float fElapsedTime) override;

	// ��ȡ�ؼ�����
	CONTROL_TYPE GetControlType() const override { return CONTROL_BUTTON; }

	// ���õ�ǰ�Ƿ��ڰ���״̬
	void SetPressed(bool pressed) { m_bPressed = pressed; }
	bool GetPressed() const { return m_bPressed; }

	// ���õ�ǰ����Ƿ��ڿؼ���
	void SetMouseOver(bool mouseOver) { m_bMouseOver = mouseOver; }
	bool GetMouseOver() const { return m_bMouseOver; }

protected:
	// ����Ƿ��ڿؼ���
	bool m_bMouseOver;
	// �Ƿ��ڰ���״̬
	bool m_bPressed;
};

#endif	// BUTTON_CONTROL_H