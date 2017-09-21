#ifndef WINDOW_ATTRIBUTE_DEFINE_H
#define WINDOW_ATTRIBUTE_DEFINE_H

#include <wx/string.h>
#include <map>

// 用来标识在xml中如何制定设置的项
const wxString SET_PROPERTY_TYPE = wxS("EditorProperty");
const wxString SET_EDITOR_NAME = wxS("EditorName");
const wxString SET_EDITOR_VALIDATOR = wxS("EditorValidator");
const wxString SET_EDITOR_MAX_LEN = wxS("EditorMaxLength");
const wxString SET_INITIAL_VALUE = wxS("InitialValue");

// 用来记录编辑属性类型，对应于wxPGProperty，这里不区分大小写
// 默认的属性类型，当前为wxStringProeprty
const wxString DEFAULT_PROPERTY = "";		// 如果该项不存在，则表示""
// 对应于wxStringProperty
const wxString STRING_PROPERTY = "string";
// 对应于wxIntProperty
const wxString INT_PROPERTY = "int";
// 对应于wxBoolProprety
const wxString BOOL_PROPERTY = "bool";
// 对应于wxEnumProperty
const wxString ENUM_PROPERTY = "enum";


// 用来标识编辑属性对应于编辑器类型，对应于wxPGEditor
// 属性默认编辑器
const wxString DEFAULT_EDITOR = "";		// 如果该项不存在，则表示""
// 对应于wxPGTextCtrlEditor
const wxString TEXTCTRL_EDITOR = "textctrl";
// 对应于wxPGSpinCtrlEditor
const wxString SPINCTRL_EDITOR = "spinctrl";
// 对应于wxPGCheckBoxEditor
const wxString CHECKBOX_EDITOR = "checkbox";
// 对应于wxPGChoiceEditor
const wxString CHOICE_EDITOR = "choice";




// 用来标识编辑属性时的Validator，对应于wxValidator
// 默认值，当前为没有Validator
const wxString DEFAULT_VALIDATOR = "";		// 如果该项不存在，则表示""



// 用来标识编辑器接受的字符串最大长度，对应于wxPGProperty的SetMaxLength函数
// 默认值，当前表示255
const wxString DEFAULT_MAXLENGTH = "";		// 如果该项不存在，则表示""
// 默认值对应的字符串大小
const int DEF_MAX_LENGTH = 255;


// 用来标识Property对应的属性，即wxPGProperty::SetAttribute函数
//
const wxString XML_ATTR_DEFAULT_VALUE = wxS("DefaultValue");
// 对应于wxPG_ATTR_HINT
const wxString XML_ATTR_HINT = wxS("Hint");
// 对应于wxPG_ATTR_MAX
const wxString XML_ATTR_MAX = wxS("Max");
// 对应于wxPG_ATTR_MIN
const wxString XML_ATTR_MIN = wxS("Min");
//// 对应于wxPG_ATTR_SPINCTRL_MOTIONSPIN
//const wxString XML_ATTR_SPINCTRL_MOTIONSPIN = wxS("MotionSpin");
// 对应于wxPG_ATTR_SPINCTRL_STEP
const wxString XML_ATTR_SPINCTRL_STEP = wxS("Step");
// 对应于wxPG_ATTR_SPINCTRL_WRAP
const wxString XML_ATTR_SPINCTRL_WRAP = wxS("Wrap");
// 对应于wxPG_ATTR_UNITS
const wxString XML_ATTR_UNITS = wxS("Units");
// 对应于wxPG_BOOL_USE_CHECKBOX
const wxString XML_BOOL_USE_CHECKBOX = wxS("UseCheckbox");
// 对应于wxPG_BOOL_USE_DOUBLE_CLICK_CYCLING
const wxString XML_BOOL_USE_DOUBLE_CLICK_CYCLING = wxS("UseDClickCycling");
// 对应于wxPG_DIR_DIALOG_MESSAGE
const wxString XML_DIR_DIALOG_MESSAGE = wxS("DialogMessage");
// 对应于wxPG_FILE_DIALOG_STYLE
const wxString XML_FILE_DIALOG_STYLE = wxS("DialogStyle");
// 对应于wxPG_FILE_DIALOG_TITLE
const wxString XML_FILE_DIALOG_TITLE = wxS("DialogTitle");
// 对应于wxPG_FILE_INITIAL_PATH
const wxString XML_FILE_INITIAL_PATH = wxS("InitialPath");
// 对应于wxPG_FILE_SHOW_FULL_PATH
const wxString XML_FILE_SHOW_FULL_PATH = wxS("ShowFullPath");
// 对应于wxPG_FILE_SHOW_RELATIVE_PATH
const wxString XML_FILE_SHOW_RELATIVE_PATH = wxS("ShowRelativePath");
// 对应于wxPG_FILE_WILDCARD
const wxString XML_FILE_WILDCARD = wxS("Wildcard");
// 对应于wxPG_FLOAT_PRECISION
const wxString XML_FLOAT_PRECISION = wxS("Precision");
// 对应于wxPG_UINT_BASE
const wxString XML_UINT_BASE = wxS("Base");
// 对应于wxPG_UINT_PREFIX
const wxString XML_UINT_PREFIX = wxS("Prefix");


// 属性的一些额外信息使用的标识符
// 用来标识枚举使用的所有值
const wxString ENUM_RANGE = wxS("range");
// 分割枚举值使用的分隔符
const wxString ENUM_RANGE_DELIMITER = wxS(",");


// 用来存储窗口属性编辑信息
struct AttributeProperty
{
	// 属性名
	wxString propertyName;
	// 属性类型
	wxString editorProperty;
	// 属性编辑器
	wxString editorName;
	// 属性验证
	wxString editorValidator;
	// 编辑器最大长度
	int editorMaxLength;
	// 初始值
	wxString initialValue;
	// 编辑器的属性设置
	std::map<wxString, wxString> editorAttributeList;
	// 关于属性的额外信息
	std::map<wxString, wxString> additionalInfos;

	AttributeProperty()
		: editorMaxLength(0)
	{

	}
};

#endif	// WINDOW_ATTRIBUTE_DEFINE_H
