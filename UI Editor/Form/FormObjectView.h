#ifndef FORM_OBJECT_VIEW_H
#define FORM_OBJECT_VIEW_H

/*
 * 文件名：FormObjectView
 * 作用：用来查看当前创建的控件父子级关系
 * 说明：控件对象展示使用多选模式，展示所有当前选中的控件对象
 */

#include <wx/treelist.h>
#include <unordered_map>
#include <unordered_set>
#include "FormToolWindow.h"
#include "FormObjectViewDefine.h"

class FormObjectView : public FormToolWindow
{
public:
	FormObjectView(wxAuiManager &manager, wxWindow * parent, int direction = wxLEFT, const wxString & paneName = wxEmptyString);
	~FormObjectView() override;

	// 设置root节点对应的控件ID
	void setRootWindowId(ID_TYPE id, const wxString& rootName);
	// 添加一个子节点用来标识一个控件
	bool addWindowItem(ID_TYPE parentId, ID_TYPE childId, const wxString& objectName, const wxString& winTypeName);
	// 删除一个子节点
	bool delWindowItem(ID_TYPE childId);

	// 设置当前选中对象，会取消之前所有的选中
	void setCurSelect(ID_TYPE selectId) const;
	// 添加选中对象
	void addSelect(ID_TYPE selectId) const;
	// 取消选中对象
	void unSelect(ID_TYPE unSelectId) const;
	// 设置当前所有选中
	void setSelections(const std::unordered_set<ID_TYPE>& selections);
	// 获取当前所有选中
	std::unordered_set<ID_TYPE> getSelections() const;
	// 修改对象编辑器中的显示，当前只设计修改对象
	void changeWinAttr(ID_TYPE changeId, const wxString& attrName, const wxAny& toSetValue) const;

private:
	// 用来处理选中改变的消息
	void handleSelectionChange(wxTreeListEvent &event);
	// 用来处理窗口被点选
	

private:
	// 初始化子窗口
	void initSubWindows();

private:
	// 展示创建的控件的树结构
	wxTreeListCtrl* m_objectView;
	// 控件ID与节点ID之间的关联
	std::unordered_map<ID_TYPE, wxTreeListItem> m_idToItems;
};

#endif	// FORM_OBJECT_VIEW_H
