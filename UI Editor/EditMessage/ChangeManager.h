#ifndef CHANGE_MANAGER_H
#define CHANGE_MANAGER_H

/*
 * 文件名：ChangeManager
 * 作用：（1）记录目标和观察者的映射关系
 *		 （2）定义特定的更新策略
 *		 （3）在目标改变时，更新所有与之相关的观察者
 */

#include <memory>

class EditorWorkArea;
class EditorToolPropertyEditor;
class EditorToolObjectView;

namespace Command
{
	class ChangeManager
	{
	public:
		ChangeManager() {}
		~ChangeManager() {}

		// 设置主工作区和工具窗口
		void setWorkArea(std::shared_ptr<EditorWorkArea> workArea) { m_workArea = workArea; }
		void setPropertyEditor(std::shared_ptr<EditorToolPropertyEditor> propertyEditor) { m_propertyEditor = propertyEditor; }
		void setObjectView(std::shared_ptr<EditorToolObjectView> objectView) { m_objectView = objectView; }
		// 获取主工作区和工具窗口
		std::shared_ptr<EditorWorkArea> getWorkArea() const { return m_workArea; }
		std::shared_ptr<EditorToolPropertyEditor> getPropertyEditor() const { return m_propertyEditor; }
		std::shared_ptr<EditorToolObjectView> getObjectView() const { return m_objectView; }

	private:
		std::shared_ptr<EditorWorkArea> m_workArea;
		std::shared_ptr<EditorToolPropertyEditor> m_propertyEditor;
		std::shared_ptr<EditorToolObjectView> m_objectView;
	};
}


#endif		// CHANGE_MANAGER_H
