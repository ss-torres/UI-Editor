#ifndef EDITOR_TOOL_OBJECT_VIEW_H
#define EDITOR_TOOL_OBJECT_VIEW_H

/*
 * 文件名：EditorToolObjectView
 * 作用：用来查看当前创建的窗口父子级关系
 */

#include "EditorToolWindow.h"
#include <wx/treelist.h>
#include <unordered_map>
#include "../EditorWindow/EditorFuncDefine.h"

class EditorToolObjectView : public EditorToolWindow
{
public:
	EditorToolObjectView(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~EditorToolObjectView() override;

	// 设置root节点对应的窗口ID
	void setRootWindowId(ID_TYPE id);
	// 添加一个子节点用来标识一个窗口
	bool addWindowItem(ID_TYPE parentId, ID_TYPE childId, const wxString& objectName, const wxString& winTypeName);

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
