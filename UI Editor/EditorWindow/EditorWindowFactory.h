#ifndef EDITOR_WINDOW_FACTORY_H
#define EDITOR_WINDOW_FACTORY_H

#include <map>
#include "AbstractWindowFactory.h"

namespace inner
{
	template <typename T>
	class SimpleLabel;
}

class EditorLabel;

class EditorWindowFactory : AbstractWindowFactory
{
public:
	using EditorLabel = inner::SimpleLabel<inner::EditorFunc>;
public:
	static AbstractWindowFactory* winFactoryInst();

	EditorWindowFactory() {}
	~EditorWindowFactory() {}

	// 根据拷贝的窗口数据，构造窗口
	EditorAbstractWindow* createCopyObjectWnd(CopyWindowInfo winObject,
		EditorAbstractWindow* parent, int relX, int relY, int width = -1, int height = -1) override;

	// 创建一个管理窗口
	EditorAbstractWindow* createManageWnd(int width, int height) override;

	//// 创建一个Static
	//EditorLabel* createStatic() const override;
	//// 创建一个Button
	//EditorButton* createButton() const override;

private:
	static AbstractWindowFactory* s_factoryInst;
	// 用来记录每种类型的创建的数量（不考虑删除）
	std::map<wxString, long> m_winTypeToNums;
};

namespace WindowFactoryImpl
{
	// 根据窗口名获取对应的窗口对象
	EditorAbstractWindow* createEditorWnd(const wxString& winName,
		EditorAbstractWindow* parent, int relX, int relY, int width, int height);
}

inline AbstractWindowFactory* EditorWindowFactory::winFactoryInst()
{
	if (s_factoryInst == nullptr)
	{
		s_factoryInst = new EditorWindowFactory();
	}

	return s_factoryInst;
}

#endif	// EDITOR_WINDOW_FACTORY_H
