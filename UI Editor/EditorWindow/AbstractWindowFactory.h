#ifndef ABSTRACT_WINDOW_FACTORY_H
#define ABSTRACT_WINDOW_FACTORY_H

#include "SimpleWindow.h"
#include "../CopyDrop/CopyWinObject.h"
#include "WindowInterface.h"


class AbstractWindowFactory
{
public:
	static AbstractWindowFactory* winFactoryInst() { return nullptr; }

	AbstractWindowFactory() {}
	virtual ~AbstractWindowFactory() {}

	// 根据拷贝的窗口数据，构造窗口
	virtual AbstractEditorWindow* createCopyObjectWnd(CopyWindowValue winObject,
		AbstractEditorWindow* parent, int relX, int relY, int width = -1, int height = -1) { return nullptr; }

	//virtual inner::SimpleWindow<T>* createStatic() const = 0;
	//virtual SimpleWindow<T>* createButton() const = 0;
};

#endif	// ABSTRACT_WINDOW_FACTORY_H
