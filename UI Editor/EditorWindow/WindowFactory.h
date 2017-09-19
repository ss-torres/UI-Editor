#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include "AbstractWindowFactory.h"
#include "EditorStatic.h"

class EditorButton;

class WindowFactory : AbstractWindowFactory <inner::EditorFunc>
{
public:
	using EditorStatic = inner:: SimpleStatic<inner::EditorFunc>;
public:
	WindowFactory() {}
	~WindowFactory() {}

	// 根据窗口类型名窗口对应窗口

	// 创建一个Static
	EditorStatic* createStatic() const override;
	//// 创建一个Button
	//EditorButton* createButton() const override;
};

#endif	// WINDOW_FACTORY_H
