#ifndef EDITOR_FRAME_H
#define EDITOR_FRAME_H

/*
 * 文件名：EditorFrame
 * 作用：用来实现一个简单的控件容器，该控件容器用来管理控件，同时显示出控件容器范围
 */

#include "EditorContainerWindow.h"

class EditorFrame : public inner::ContainerWindow<inner::EditorContainerFunc>
{
public:
	using ContainerWindow<inner::EditorContainerFunc>::ContainerWindow;
	~EditorFrame() override {}

	// 重载绘制函数
	void draw(int x, int y) const override {}
};

#endif	// EDITOR_FRAME_H
