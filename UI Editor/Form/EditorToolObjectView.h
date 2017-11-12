#ifndef EDITOR_TOOL_OBJECT_VIEW_H
#define EDITOR_TOOL_OBJECT_VIEW_H

/*
 * 文件名：EditorToolObjectView
 * 作用：用来查看当前创建的窗口父子级关系
 * 说明：窗口对象展示使用多选模式，展示所有当前选中的窗口对象
 */

#include "EditorToolWindow.h"
#include <wx/treelist.h>
#include <unordered_map>
#include "../EditorFuncDefine.h"

class EditorToolObjectView : public EditorToolWindow
{
public:
	EditorToolObjectView(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~EditorToolObjectView() override;

	// 设置root节点对应的窗口ID
	void setRootWindowId(ID_TYPE id);
	// 添加一个子节点用来标识一个窗口
	bool addWindowItem(ID_TYPE parentId, ID_TYPE childId, const wxString& objectName, const wxString& winTypeName);

	// 设置当前选中对象，会取消之前所有的选中
	void setCurSelect(ID_TYPE selectId) const;
	// 添加选中对象
	void addSelect(ID_TYPE selectId) const;
	// 取消选中对象
	void unSelect(ID_TYPE unSelectId) const;
	// 获取当前所有选中
	std::vector<ID_TYPE> getSelections() const;
	// 修改对象编辑器中的显示，当前只设计修改对象
	void changeWinAttr(ID_TYPE changeId, const wxString& attrName, const wxAny& toSetValue) const;

private:
	// 初始化子窗口
	void initSubWindows();

private:
	// 展示创建的窗口的树结构
	wxTreeListCtrl* m_objectView;
	// 窗口ID与节点ID之间的关联
	std::unordered_map<ID_TYPE, wxTreeListItem> m_idToItems;
};

#endif	// EDITOR_TOOL_OBJECT_VIEW_H
