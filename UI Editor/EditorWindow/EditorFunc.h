#ifndef EDITOR_FUNC_H
#define EDITOR_FUNC_H

/*
 * 文件名：EditorFunc
 * 作用：用来实现窗口编辑相关的功能
 * 说明：如果采用C++ Programming Language 4th中的27.4.2: Linearizing Class Hierarchies中的设计方法，
 * 优化属性处理相关函数的实现
 */

#include <map>
#include <utility>
#include <functional>
#include <wx/string.h>
#include <wx/any.h>

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
		using WIN_ATTR_MAP = std::map<wxString, wxAny>;
	public:
		EditorFunc();
		virtual ~EditorFunc();

		// 用来获取构建的窗口类型，继承的窗口返回自身
		virtual SimpleWindow<EditorFunc>* getConstructWindow() = 0;

		// 更新窗口对象属性信息
		virtual void updateWinAttr(const wxString& attrName, const wxAny& value) { updateAttrValue(attrName, value); }

	protected:
		// 定义处理消息的类型，返回值表示是否修改了属性，true表示修改，false表示未修改
		using CHANGE_ATTR_FUNC = std::function<bool(EditorFunc*, const wxAny&)>;
		using ATTR_HANDLE_MAP = std::map<const wxString, CHANGE_ATTR_FUNC>;
		// 修改编辑时是否显示
		bool ChangeEditShow(const wxAny& value);
		// 修改X坐标
		bool ChangePosX(const wxAny& value);
		// 修改Y坐标
		bool ChangePosY(const wxAny& value);
		// 修改sizeX
		bool ChangeSizeX(const wxAny& value);
		// 修改sizeY
		bool ChangeSizeY(const wxAny& value);

		// 获取属性与属性处理函数Map
		static const ATTR_HANDLE_MAP& getEditorAttrHandles();

	protected:
		// 设置窗口在编辑时是否显示
		void setEditShow(bool editShow) { m_editShow = editShow; }
		bool getEditShow() const { return m_editShow; }

		// 更新整个属性表中的信息
		void updateAttrValue(const wxString& name, const wxAny& value);
		// 获取整个属性表中的全部信息
		const WIN_ATTR_MAP& getWinAttrs() const { return m_allWinAttrs;  }

	private:
		// 初始化属性处理函数Map
		static ATTR_HANDLE_MAP initEditorAttrHanldes();
		// 修改窗口中一个T型属性
		template <typename T>
		bool ChangeWndAttrValue(const wxAny& value, std::function<T(SimpleWindow<EditorFunc>*)> getFunc,
			std::function<void(SimpleWindow<EditorFunc>*, T)> setFunc, const char* funcName);

	private:
		// 在编辑时，该窗口是否显示
		bool m_editShow;
		// 用来记录窗口的全部属性
		WIN_ATTR_MAP m_allWinAttrs;
	};


	// 更新整个属性表中的信息
	inline void EditorFunc::updateAttrValue(const wxString & name, const wxAny & value)
	{
		m_allWinAttrs[name] = value;
	}

	// 修改窗口中一个int型属性
	template <typename T>
	inline bool EditorFunc::ChangeWndAttrValue(const wxAny& value, std::function<T(SimpleWindow<EditorFunc>*)> getFunc,
		std::function<void(SimpleWindow<EditorFunc>*, T)> setFunc, const char* funcName)
	{
		if (value.CheckType<T>())
		{
			auto v = value.As<T>();
			auto pThis = getConstructWindow();
			if (v != getFunc(pThis))
			{
				setFunc(pThis, v);
			}
			return false;
		}
		else
		{
			throw std::runtime_error(funcName + std::string("'s parameter is not an int."));
		}

		return false;
	}
}

#endif	// EDITOR_FUNC_H
