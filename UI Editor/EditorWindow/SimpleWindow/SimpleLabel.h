#ifndef SIMPLE_STATIC_H
#define SIMPLE_STATIC_H

/*
 * 文件名：SimpleLabel
 * 作用：用来实现简单label显示的控件
 */

#include <wx/font.h>
#include "SimpleWindow.h"
#include "UiEditorProtocol.h"

namespace inner
{
	template <typename T>
	class SimpleLabel : public SimpleWindow<T>
	{
	public:
		using SIMPLE_WINDOW_TYPE = typename SimpleWindow<T>::SIMPLE_WINDOW_TYPE;
	public:
		SimpleLabel(SIMPLE_WINDOW_TYPE* parent, int relX, int relY, int width, int height);
		~SimpleLabel() override;

		// 设置Label显示的文字
		template <typename T>
		void setText(T&& text) { m_text = text; }
		// 获取Label显示的文字
		const LABEL_TYPE& getText() const { return m_text; }
		// 设置显示用的字体
		void setFont(wxFont font) { m_font = font; }

		// 重载绘制函数
		void draw(int x, int y) const override {}

	private:
		// 记录label的内容
		LABEL_TYPE m_text;
		// 显示使用的字体
		wxFont m_font;
	};
}

#include "SimpleLabel.inl"

#endif	// SIMPLE_STATIC_H
