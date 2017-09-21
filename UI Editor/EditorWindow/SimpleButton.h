#ifndef SIMPLE_BUTTON_H
#define SIMPLE_BUTTON_H

/*
 * 文件名：SimpleButton
 * 作用：实现简单的按钮功能
 */

#include "SimpleWindow.h"
#include <wx/font.h>

namespace inner
{
	template <typename T>
	class SimpleButton : public SimpleWindow<T>
	{
	public:
		SimpleButton(SimpleWindow<T>* parent, int relX, int relY, int width, int height);
		~SimpleButton() override;

		// 设置显示的文字
		void setLabel(const wxString& label) { m_label = label; }
		// 设置显示用的字体
		void setFont(wxFont font) { m_font = font; }

		// 重载绘制函数
		void draw() override {}

	private:
		// 显示的label
		wxString m_label;
		// 显示使用的字体
		wxFont m_font;
	};
}

#include "SimpleButton.inl"

#endif	// SIMPLE_BUTTON_H