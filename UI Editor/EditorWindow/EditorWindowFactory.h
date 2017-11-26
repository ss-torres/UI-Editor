#ifndef EDITOR_WINDOW_FACTORY_H
#define EDITOR_WINDOW_FACTORY_H

#include <map>
#include "EditorAbstractWindowFactory.h"

namespace inner
{
	template <typename T>
	class SimpleLabel;
}

class EditorLabel;

class EditorWindowFactory : public EditorAbstractWindowFactory
{
public:
	using EditorLabel = inner::SimpleLabel<inner::EditorFunc>;
public:
	static EditorAbstractWindowFactory* winFactoryInst();

	EditorWindowFactory() {}
	~EditorWindowFactory() {}

	// 根据拷贝的控件数据，构造控件
	EditorAbstractWindow* createCopyObjectWnd(CopyWindowInfo winObject,
		EditorAbstractWindow* parent, int relX, int relY, int width = -1, int height = -1) override;

	// 创建一个管理控件
	EditorAbstractWindow* createManageWnd(int width, int height) override;

	//// 创建一个Static
	//EditorLabel* createStatic() const override;
	//// 创建一个Button
	//EditorButton* createButton() const override;

private:
	// 根据拷贝控件名，给新控件取一个名字
	void changeWindowName(wxString& winName);

private:
	static EditorAbstractWindowFactory* s_factoryInst;
	// 用来记录每种类型的创建的数量（不考虑删除）
	std::map<wxString, long> m_winTypeToNums;
};

namespace WindowFactoryImpl
{
	// 根据控件名获取对应的控件对象
	EditorAbstractWindow* createEditorWnd(const wxString& winName,
		EditorAbstractWindow* parent, int relX, int relY, int width, int height);
}

inline EditorAbstractWindowFactory* EditorWindowFactory::winFactoryInst()
{
	if (s_factoryInst == nullptr)
	{
		s_factoryInst = new EditorWindowFactory();
	}

	return s_factoryInst;
}

#endif	// EDITOR_WINDOW_FACTORY_H
