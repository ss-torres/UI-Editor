#include "ImageProperty.h"

#include <wx/propgrid/props.h>
#include <wx/propgrid/advprops.h>

WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(ImageData)

WX_PG_IMPLEMENT_PROPERTY_CLASS(ImageProperty, wxPGProperty,
			ImageData, const ImageData&, TextCtrlAndButton)

ImageProperty::ImageProperty(const wxString& label, const wxString& name, const ImageData& value)
	: wxPGProperty(label, name), m_imageData(value)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild(new wxFileProperty(wxS("Image"), wxPG_LABEL, value.m_imageFile));
	AddPrivateChild(new wxIntProperty(wxS("X"), wxPG_LABEL, value.m_x));
	AddPrivateChild(new wxIntProperty(wxS("Y"), wxPG_LABEL, value.m_y));
}

ImageProperty::~ImageProperty()
{

}

wxVariant ImageProperty::ChildChanged(wxVariant & thisValue, int childIndex, wxVariant & childValue) const
{
	ImageData imageData;
	imageData << thisValue;
	switch (childIndex)
	{
	case 0: imageData.m_imageFile = childValue.GetString(); break;
	case 1: imageData.m_x = childValue.GetInteger(); break;
	case 2: imageData.m_y = childValue.GetInteger(); break;
	}
	wxVariant newVariant;
	newVariant << imageData;
	return newVariant;
}

void ImageProperty::RefreshChildren()
{
	if (!GetChildCount()) return;
	const ImageData& imageData = ImageDataRefFromVariant(m_value);
	Item(0)->SetValue(imageData.m_imageFile);
	Item(1)->SetValue(imageData.m_x);
	Item(2)->SetValue(imageData.m_y);
}

bool MessageBoxDialogAdapter::DoShowDialog(wxPropertyGrid * WXUNUSED(propertyGrid), wxPGProperty * WXUNUSED(property))
{
	int value = wxMessageBox("test", "this is a test");

	if (value == wxOK)
	{
		m_imageData.m_imageFile = "C/test.png";
		m_imageData.m_x = 10;
		m_imageData.m_y = 35;

		wxVariant newVariant;
		newVariant << m_imageData;
		SetValue(newVariant);

		return true;
	}

	return false;
}
