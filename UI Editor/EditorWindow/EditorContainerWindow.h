#ifndef EDITOR_CONTAINER_WINDOW_H
#define EDITOR_CONTAINER_WINDOW_H

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

		// 用来查看对应ID的窗口
		SimpleWindow<EditorFunc>* findMatchWnd(ID_TYPE findId) override;

	protected:
		// 设置该窗口是否编辑时显示
		void setEditShow(bool editShow) override;
	};
}


#endif	// EDITOR_CONTAINER_WINDOW_H
