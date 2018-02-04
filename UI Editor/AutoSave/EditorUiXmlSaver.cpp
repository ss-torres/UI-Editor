#include <wx/xml/xml.h>
#include <wx/filename.h>
#include "EditorUiXmlSaver.h"

const char* const UI_ROOT_NAME = "UISave";
const char* const UI_ROOT_VERSION = "Version";
const char* const CURRENT_VERSION = "1";

EditorUiXmlSaver::EditorUiXmlSaver()
{
	initXmlSaver();
}

// 添加一个窗口
wxXmlNode* EditorUiXmlSaver::addRootWindow(const wxString & winType, const WIN_ATTR_MAP & winAttrs)
{
	wxXmlAttribute* attr = new wxXmlAttribute(UI_ROOT_VERSION, CURRENT_VERSION);
	wxXmlNode* root = new wxXmlNode(nullptr, wxXML_ELEMENT_NODE, UI_ROOT_NAME, wxEmptyString, attr);

	auto winAttr = getXmlAttr(winAttrs);
	wxXmlNode* win = new wxXmlNode(root, wxXML_ELEMENT_NODE, winType, wxEmptyString, winAttr);
	// 会清楚之前的root节点
	m_doc->SetRoot(root);

	return win;
}

// 添加一个子窗口
wxXmlNode* EditorUiXmlSaver::appendChildWindow(const wxString & winType, const WIN_ATTR_MAP & winAttrs, wxXmlNode* parent)
{
	auto winAttr = getXmlAttr(winAttrs);
	return new wxXmlNode(parent, wxXML_ELEMENT_NODE, winType, wxEmptyString, winAttr);
}

// 保存窗口信息到文件
bool EditorUiXmlSaver::saveWindow(const wxString& fileName)
{
	// 如果已存在文件，则返回
	wxFileName file(fileName);
	if (file.FileExists())
	{
		return false;
	}
	else
	{
		// 如果文件不存在，则创建UI文件所在路径，防止之后的写失败
		file.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	}
	m_doc->Save(fileName);
	return true;
}

// 根据传入的属性列表，获取xml节点的属性列表
wxXmlAttribute * EditorUiXmlSaver::getXmlAttr(const WIN_ATTR_MAP & winAttrs)
{
	wxXmlAttribute* winAttr = nullptr;
	if (!winAttrs.empty())
	{
		auto it = winAttrs.cbegin();
		wxVariant toV;
		it->second.GetAs(&toV);
		winAttr = new wxXmlAttribute(it->first, toV.MakeString());

		wxXmlAttribute* newAttr = winAttr;
		for (++it; it != winAttrs.cend(); ++it)
		{
			it->second.GetAs(&toV);
			newAttr->SetNext(new wxXmlAttribute(it->first, toV.MakeString()));
			newAttr = newAttr->GetNext();
		}
	}
	return winAttr;
}

void EditorUiXmlSaver::initXmlSaver()
{
	m_doc = new wxXmlDocument();
	m_doc->SetFileEncoding("UTF-8");
	m_doc->SetVersion("1.0");
}
