#ifndef EDITOR_FUNC_H
#define EDITOR_FUNC_H

/*
 * 文件名：EditorFunc
 * 作用：用来实现控件编辑相关的功能
 * 说明：
 * 1.如果采用C++ Programming Language 4th中的27.4.2: Linearizing Class Hierarchies中的设计方法，
 * 优化属性处理相关函数的实现
 * 2.修改该类的子类属性，需要对应类的updateWinAttr函数，这样属性列表中的值才能与属性保持一致
 */

#include <map>
#include <utility>
#include <functional>
#include <wx/string.h>
#include <wx/any.h>
#include "WinAttrAndNameProtocol.h"
#include "EditorFuncDefine.h"
#include "../Form/FormWidgetSelectDefine.h"
#include "../ErrorHandle/ErrorHandle.h"

namespace inner
{
	template <typename T>
	class SimpleWindow;
}

class Visitor;
class DrawControlManager;

namespace inner
{
	class EditorFunc
	{
	public:
		using FuncBaseType = EditorFunc;
		using WIN_ATTR_MAP = std::map<wxString, wxAny>;
	public:
		EditorFunc();
		virtual ~EditorFunc();

		// 用来获取构建的控件类型，继承的控件返回自身
		virtual SimpleWindow<EditorFunc>* getConstructWindow() = 0;

		// 用来获取控件类名字
		virtual wxString getWindowClassName() const { return EDITOR_WINDOW_TYPE; }
		// 获取控件ID，用来标识控件
		ID_TYPE getId() const { return m_id; }
		// 用来判断控件在编辑器是否可以编辑
		bool isUiShow() const { return m_editShow; }
		// 用来获取属性是否可以编辑，对于控件管理类，属性不可以编辑
		virtual bool isAttrEditable() { return true; }
		// 用来查看对应ID的控件
		virtual SimpleWindow<EditorFunc>* findMatchWnd(ID_TYPE findId);

		// 更新控件对象属性信息
		virtual void updateWinAttr(const wxString& attrName, const wxAny& value) { updateAttrValue(attrName, value); }
		// 获取控件对象属性列表中的信息
		const wxAny& getWinAttr(const wxString& attrName) const;
		// 重新设置整个属性表，当前只会更新列表信息，不会修改Window中的数据
		template <typename ATTR_MAP_TYPE = WIN_ATTR_MAP>
		void resetWinAttrs(ATTR_MAP_TYPE&& allTypes = ATTR_MAP_TYPE());
		// 获取整个属性表中的全部信息
		const WIN_ATTR_MAP& getWinAttrs() const 
		{ 
			return m_allWinAttrs; 
		}

		//在编辑界面上绘制
		virtual void editDraw(int absX, int absY, DrawControlManager* drawManager) {}

	public:
		// 用来处理各种鼠标事件
		virtual bool handleLMouseDown(int x, int y);

	protected:
		// 定义处理消息的类型，返回值表示是否修改了属性，true表示修改，false表示未修改
		using CHANGE_ATTR_FUNC = std::function<bool(EditorFunc*, const wxAny&)>;
		using ATTR_HANDLE_MAP = std::map<const wxString, CHANGE_ATTR_FUNC>;
		// 修改编辑时是否显示
		bool changeEditShow(const wxAny& value);
		// 修改X坐标
		bool changePosX(const wxAny& value);
		// 修改Y坐标
		bool changePosY(const wxAny& value);
		// 修改sizeX
		bool changeSizeX(const wxAny& value);
		// 修改sizeY
		bool changeSizeY(const wxAny& value);

		// 设置控件在编辑时是否显示
		virtual void setEditShow(bool editShow) { m_editShow = editShow; }

		// 获取属性与属性处理函数Map
		static const ATTR_HANDLE_MAP& getEditorAttrHandles();

	protected:
		bool getEditShow() const { return m_editShow; }
		// 设置控件ID
		void setId(ID_TYPE id) { m_id = id; }

	private:
		// 用来生成新的控件ID
		static ID_TYPE s_id_generator;
		// 获取一个控件ID，获取的控件ID从ID_BEG开始，如果新的控件ID为负值，则提示错误
		static ID_TYPE getNewId();
		// 更新整个属性表中的信息
		void updateAttrValue(const wxString& name, const wxAny& value);
		// 初始化属性处理函数Map
		static ATTR_HANDLE_MAP initEditorAttrHanldes();
		// 修改控件中一个T型属性
		template <typename T>
		bool ChangeWndAttrValue(const wxAny& value, std::function<T(SimpleWindow<EditorFunc>*)> getFunc,
			std::function<void(SimpleWindow<EditorFunc>*, T)> setFunc, const char* funcName);

	private:
		// 在编辑时，该控件是否显示
		bool m_editShow;
		// 用来记录当前控件的ID
		ID_TYPE m_id;
		// 用来记录控件的全部属性
		WIN_ATTR_MAP m_allWinAttrs;
	};

	// 重新设置整个属性表，当前只会更新列表信息，不会修改Window中的数据
	template<typename ATTR_MAP_TYPE>
	inline void EditorFunc::resetWinAttrs(ATTR_MAP_TYPE&& allTypes)
	{
		m_allWinAttrs = allTypes;
	}

	// 更新整个属性表中的信息
	inline void EditorFunc::updateAttrValue(const wxString & name, const wxAny & value)
	{
		m_allWinAttrs[name] = value;
	}

	// 获取控件对象属性列表中的信息
	inline const wxAny& EditorFunc::getWinAttr(const wxString & attrName) const
	{
		auto it = m_allWinAttrs.find(attrName);
		if (it != m_allWinAttrs.cend())
		{
			return it->second;
		}

		// 按照逻辑不应该出现的情况
		throw ExtraExcept::unexpected_situation("EditorFunc::getWinAttr can't find " + attrName.ToStdString());

		static wxAny value;
		return value;
	}

	// 修改控件中一个int型属性
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
				return true;
			}
		}
		else
		{
			throw std::runtime_error(funcName + std::string("'s parameter is not ") + typeid(T).name());
		}

		return false;
	}

	// 获取一个控件ID，获取的控件ID从10开始，如果新的控件ID为负值，则提示错误
	inline int EditorFunc::getNewId()
	{
		auto newId = ++s_id_generator;
		if (newId < 0)
		{
			throw std::runtime_error("EditorFunc::getNewId will return negative id");
		}
		return newId;
	}
}

#include "EditorFuncCategory.inl"


#endif	// EDITOR_FUNC_H
