#ifndef IMAGE_PROPERTY_H
#define IMAGE_PROPERTY_H

#include "wx/fontdlg.h"
#include <wx/bitmap.h>
#include <wx/propgrid/property.h>
#include <wx/string.h>
#include <wx/propgrid/editors.h>
#include <wx/msgdlg.h> 

class ImageData
{
public:
	ImageData()
	{
		m_x = m_y = 0;
	}

	ImageData(const wxString& imageName, int x, int y)
		: m_imageFile(imageName), m_x(x), m_y(y)
	{

	}

	wxString m_imageFile;
	int m_x;
	int m_y;
};

inline bool operator ==(const ImageData& left, const ImageData& right)
{
	return (left.m_imageFile == right.m_imageFile && left.m_x == right.m_x && left.m_y == right.m_y);
}

WX_PG_DECLARE_VARIANT_DATA(ImageData)

class MessageBoxDialogAdapter : public wxPGEditorDialogAdapter
{
public:
	MessageBoxDialogAdapter(const ImageData& imageData)
		: wxPGEditorDialogAdapter(), m_imageData(imageData)
	{

	}

	bool DoShowDialog(wxPropertyGrid* WXUNUSED(propGrid),
		wxPGProperty* WXUNUSED(property));

private:
	ImageData m_imageData;
};


class ImageProperty : public wxPGProperty
{
	WX_PG_DECLARE_PROPERTY_CLASS(ImageProperty)
public:

	ImageProperty(const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL,
		const ImageData& value = ImageData());
	
	~ImageProperty() override;

	wxVariant ChildChanged(wxVariant& thisValue,
		int childIndex,
		wxVariant& childValue) const override;

	void RefreshChildren() override;

	// Set what happens on button click
	virtual wxPGEditorDialogAdapter* GetEditorDialog() const
	{
		return new MessageBoxDialogAdapter(m_imageData);
	}

protected:
	ImageData m_imageData;
};

#endif	// IMAGE_PROPERTY_H