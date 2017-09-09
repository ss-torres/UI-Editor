#ifndef SIMPLE_STATIC_H
#define SIMPLE_STATIC_H

/*
 * 文件名：SimpleStatic
 * 作用：用来实现简单label显示的窗口
 */

#include "SimpleWindow.h"
#include <wx/font.h>

namespace inner
{
	template <typename T>
	class SimpleStatic : public SimpleWindow<T>
	{
	public:
		SimpleStatic(SimpleWindow<T>* parent, int relX, int relY, int width, int height);
		~SimpleStatic() override;

		// 设置显示的文字
		void setLabel(const wxString& label) { m_label = label; }
		// 设置显示用的字体
		void setFont(wxFont font) { m_font = font; }

	private:
		// 显示的label
		wxString m_label;
		// 显示使用的字体
		wxFont m_font;
	};
}

#include "SimpleStatic.inl"

#endif	// SIMPLE_STATIC_H
