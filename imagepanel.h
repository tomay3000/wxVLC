/***************************************************************
 * Name:      imagepanel.h
 * Purpose:   Header file for wxImagePanel Class
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-31
 * Copyright: (c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <wx/panel.h>
#include <wx/dcbuffer.h>
#include <wx/stream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

class wxImagePanel : public wxPanel
{
protected:
    void Init();

public:
    wxImagePanel();

    wxImagePanel(wxWindow *parent,
                 wxWindowID winid = wxID_ANY,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize,
                 long style = wxTAB_TRAVERSAL | wxNO_BORDER | wxCLIP_CHILDREN,
                 const wxString &name = _T("ImagePanel"));

    wxImagePanel(wxWindow *parent, const wxString &file, wxBitmapType type = wxBITMAP_TYPE_ANY);

    virtual ~wxImagePanel();

    void LoadFile(const wxString &file, wxBitmapType type = wxBITMAP_TYPE_ANY);
    void LoadFile(wxInputStream &stream, wxBitmapType type = wxBITMAP_TYPE_ANY);
    void PaintEvent(wxPaintEvent &event);
    void PaintNow();
    void Render(wxDC &dc);
    void OnSize(wxSizeEvent &event);

    inline void SetImage(wxImage &image)
    {
        m_image = image;
        Refresh();
    }

    inline void SetNullImage()
    {
        SetImage(wxNullImage);
    }

    inline wxImage GetImage(void) const
    {
        return m_image;
    }

    inline void SetStretch(bool bStretch)
    {
        m_bStretch = bStretch;
        Refresh();
    }

    inline void StretchImage()
    {
        SetStretch(true);
    }

    inline bool GetStretch(void) const
    {
        return m_bStretch;
    }

    inline void SetCenterImage(bool bCenterImage)
    {
        m_bCenterImage = bCenterImage;
        Refresh();
    }

    inline void CenterImage()
    {
        return SetCenterImage(true);
    }

    inline bool GetCenterImage(void) const
    {
        return m_bCenterImage;
    }

protected:
    wxImage m_image;
    bool m_bStretch;
    bool m_bCenterImage;

    //DECLARE_EVENT_TABLE()

    /*private:
        wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxImagePanel);*/
};

#endif // IMAGEPANEL_H_INCLUDED
