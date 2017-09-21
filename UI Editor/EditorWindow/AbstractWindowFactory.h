#ifndef ABSTRACT_WINDOW_FACTORY_H
#define ABSTRACT_WINDOW_FACTORY_H

#include "SimpleWindow.h"
#include "../CopyDrop/CopyWinObject.h"
#include "WindowInterface.h"

template <typename T>
class AbstractWindowFactory
{
public:
	AbstractWindowFactory() {}
	virtual ~AbstractWindowFactory() {}

	// 根据拷贝的窗口数据，构造窗口
	virtual AbstractEditorWindow* createCopyObjectWnd(const CopyWindowValue& winObject,
		AbstractEditorWindow* parent, int relX, int relY, int width, int height) { return nullptr; }

	//virtual inner::SimpleWindow<T>* createStatic() const = 0;
	//virtual SimpleWindow<T>* createButton() const = 0;
};

#endif	// ABSTRACT_WINDOW_FACTORY_H
