#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include "AbstractWindowFactory.h"

namespace inner
{
	template <typename T>
	class SimpleLabel;
}

class EditorLabel;

class WindowFactory : AbstractWindowFactory <inner::EditorFunc>
{
public:
	using EditorLabel = inner::SimpleLabel<inner::EditorFunc>;
public:
	WindowFactory() {}
	~WindowFactory() {}

	// 根据拷贝的窗口数据，构造窗口
	AbstractEditorWindow* createCopyObjectWnd(const CopyWindowValue& winObject,
		AbstractEditorWindow* parent, int relX, int relY, int width, int height) override;

	//// 创建一个Static
	//EditorLabel* createStatic() const override;
	//// 创建一个Button
	//EditorButton* createButton() const override;

private:
	// 根据窗口名获取对应的窗口对象
	AbstractEditorWindow* createEditorWnd(const wxString& winName,
		AbstractEditorWindow* parent, int relX, int relY, int width, int height) const;
};

#endif	// WINDOW_FACTORY_H
