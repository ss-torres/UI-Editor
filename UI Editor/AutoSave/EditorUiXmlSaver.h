#ifndef EDITOR_UI_XML_SAVER_H
#define EDITOR_UI_XML_SAVER_H

/*
 * 文件名：EditorUiXmlSaver
 * 作用：提供将窗口文件保存的功能
 */

#include <map>
#include <wx/string.h>
#include <wx/any.h>

class wxXmlDocument;
class wxXmlNode;
class wxXmlAttribute;

class EditorUiXmlSaver
{
public:
	using WIN_ATTR_MAP = std::map<wxString, wxAny>;
public:
	EditorUiXmlSaver();
	~EditorUiXmlSaver() = default;

	// 添加一个窗口
	wxXmlNode* addRootWindow(const wxString& winType, const WIN_ATTR_MAP& winAttrs);
	// 添加一个子窗口
	wxXmlNode* appendChildWindow(const wxString& winType, const WIN_ATTR_MAP& winAttrs, wxXmlNode* parent);
	// 保存窗口信息到文件
	bool saveWindow(const wxString& fileName);

private:
	// 根据传入的属性列表，获取xml节点的属性列表
	wxXmlAttribute* getXmlAttr(const WIN_ATTR_MAP& winAttrs);
	// 初始化UI文件保存
	void initXmlSaver();

private:
	wxXmlDocument* m_doc = nullptr;
};

#endif	// EDITOR_UI_XML_SAVER_H