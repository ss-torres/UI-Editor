#ifndef SIMPLE_BUTTON_H
#define SIMPLE_BUTTON_H

/*
 * 文件名：SimpleButton
 * 作用：实现简单的按钮功能
 */

#include <wx/font.h>
#include "SimpleWindow.h"
#include "UiEditorProtocol.h"

namespace inner
{
	template <typename T>
	class SimpleButton : public SimpleWindow<T>
	{
	public:
		using SIMPLE_WINDOW_TYPE = typename SimpleWindow<T>::SIMPLE_WINDOW_TYPE;
	public:
		SimpleButton(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		~SimpleButton() override;

		// 设置button显示的文字
		template <typename T>
		void setText(T&& text) { m_text = text; }
		// 获取button显示的文字
		const LABEL_TYPE& getText() const { return m_text; }
		// 设置显示用的字体
		void setFont(wxFont font) { m_font = font; }

		// 重载绘制函数
		void draw(int x, int y) const override {}

	private:
		// 显示的label
		LABEL_TYPE m_text;
		// 显示使用的字体
		wxFont m_font;
	};
}

#include "SimpleButton.inl"

#endif	// SIMPLE_BUTTON_H