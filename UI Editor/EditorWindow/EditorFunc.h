#ifndef EDITOR_FUNC_H
#define EDITOR_FUNC_H

/*
 * 文件名：EditorFunc
 * 作用：用来实现窗口编辑相关的功能
 */

#include <map>
#include <utility>
#include <wx/string.h>

namespace inner
{
	template <typename T>
	class SimpleWindow;
}

class Visitor;

namespace inner
{
	class EditorFunc
	{
	public:
		EditorFunc();
		virtual ~EditorFunc();

		// 设置窗口在编辑时是否显示
		void setEditShow(bool editShow) { m_editShow = editShow; }

		// 用来获取构建的窗口类型，继承的窗口返回自身
		virtual SimpleWindow<EditorFunc>* getConstructWindow() = 0;

		// 更新窗口对象信息
		template <typename ...Args>
		void updateAttr(Visitor* visitor, const wxString& attrName, Args&&... args);

	private:
		// 在编辑时，该窗口是否显示
		bool m_editShow;
		// 用来记录窗口的额外属性
		std::map<wxString, wxString> m_extraAttrs;
	};


	// 更新窗口对象信息
	template <typename ...Args>
	void EditorFunc::updateAttr(Visitor* visitor, const wxString& attrName, Args&&... args)
	{
		visitor->updateAttr(getConstructWindow(), attrName, std::forward<Args>(args)...);
	}
}

#endif	// EDITOR_FUNC_H
