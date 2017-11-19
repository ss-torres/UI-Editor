#ifndef EDITOR_CONTAINER_WINDOW_H
#define EDITOR_CONTAINER_WINDOW_H

/*
 * 文件名：EditorContainerWindow
 * 作用: 作为控件的容器，构建控件的父子层级关系
 */

#include "EditorFunc.h"
#include "EditorAbstractWindow.h"
#include "SimpleWindow/ContainerWindow.h"

namespace inner
{
	template <>
	class ContainerWindow<EditorContainerFunc> : public ContainerWindow<EditorEditableFunc>
	{
	public:
		using ContainerWindow<EditorEditableFunc>::ContainerWindow;
		~ContainerWindow<EditorContainerFunc>() override {}

		// 用来查看对应ID的控件
		SimpleWindow<EditorFunc>* findMatchWnd(ID_TYPE findId) override;

	protected:
		// 设置该控件是否编辑时显示
		void setEditShow(bool editShow) override;
	};
}


#endif	// EDITOR_CONTAINER_WINDOW_H
