/***************************************************************
 * Name:      imagepanel.cpp
 * Purpose:   Source file for wxImagePanel Class
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-31
 * Copyright: (c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "imagepanel.h"

/*BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
    // Catch paint events
    EVT_PAINT(wxImagePanel::PaintEvent)
    //Size event
    EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()*/

//wxIMPLEMENT_DYNAMIC_CLASS_XTI(wxImagePanel, wxPanel, "imagepanel.h");

void wxImagePanel::Init()
{
    m_image = wxNullImage;
    m_bStretch = false;
    m_bCenterImage = false;

    //Connect(wxEVT_PAINT, wxPaintEventHandler(wxImagePanel::PaintEvent), NULL, this);
    Bind(wxEVT_PAINT, &wxImagePanel::PaintEvent, this);
    //Connect(wxEVT_SIZE, wxSizeEventHandler(wxImagePanel::OnSize), NULL, this);
    Bind(wxEVT_SIZE, &wxImagePanel::OnSize, this);

    // Flicker-free drawing requires this
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

wxImagePanel::wxImagePanel() : wxPanel()
{
    Init();
}

wxImagePanel::wxImagePanel(wxWindow *parent,
                           wxWindowID winid /*= wxID_ANY*/,
                           const wxPoint &pos /*= wxDefaultPosition*/,
                           const wxSize &size /*= wxDefaultSize*/,
                           long style /*= wxTAB_TRAVERSAL | wxNO_BORDER | wxCLIP_CHILDREN*/,
                           const wxString &name /*= _T("ImagePanel")*/) :
    wxPanel(parent, winid, pos, size, style, name)
{
    Init();
}

wxImagePanel::wxImagePanel(wxWindow *parent,
                           const wxString &file,
                           wxBitmapType type /*= wxBITMAP_TYPE_ANY*/) :
    wxPanel(parent)
{
    Init();

    // Load the file... ideally add a check to see if loading was successful
    m_image.LoadFile(file, type);
}

wxImagePanel::~wxImagePanel()
{
    //Disconnect(wxEVT_PAINT, wxPaintEventHandler(wxImagePanel::PaintEvent), NULL, this);
    Unbind(wxEVT_PAINT, &wxImagePanel::PaintEvent, this);
    //Disconnect(wxEVT_SIZE, wxSizeEventHandler(wxImagePanel::OnSize), NULL, this);
    Unbind(wxEVT_SIZE, &wxImagePanel::OnSize, this);
}

void wxImagePanel::LoadFile(const wxString &file, wxBitmapType type /*= wxBITMAP_TYPE_ANY*/)
{
    // Load the file... ideally add a check to see if loading was successful
    m_image.LoadFile(file, type);
}

void wxImagePanel::LoadFile(wxInputStream &stream, wxBitmapType type /*= wxBITMAP_TYPE_ANY*/)
{
    // Load the file... ideally add a check to see if loading was successful
    m_image.LoadFile(stream, type);
}

/* Called by the system of wxWidgets when the panel needs
   to be redrawn. You can also trigger this call by calling Refresh()/Update(). */
void wxImagePanel::PaintEvent(wxPaintEvent &WXUNUSED(event))
{
    // Depending on your system you may need to look at double-buffered dcs
    wxBufferedPaintDC bpdc(this);
    Render(bpdc);
}

/* Alternatively, you can use a clientDC to paint on the panel at any time.
   Using this generally does not free you from catching paint events,
   since it is possible that e.g. the window manager throws away your drawing
   when the window comes to the background, and expects you will redraw it
   when the window comes back (by sending a paint event). */
void wxImagePanel::PaintNow()
{
    // Depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    wxBufferedDC bdc(&dc);
    Render(bdc);
}

/* Here we do the actual rendering. I put it in a separate method so that it
   can work no matter what type of DC (e.g. wxPaintDC or wxClientDC) is used. */
void wxImagePanel::Render(wxDC &dc)
{
    if (!m_image.IsOk())
        return;

    int panelWidth, panelHeight;
    GetClientSize(&panelWidth, &panelHeight);
    wxPoint pos;
    wxImage image = m_image;
    wxBitmap bitmap;

    // Fill the dc with the background colour
    dc.SetBackground(GetBackgroundColour());
    dc.Clear();

    // Should we stretch the image?
    if (m_bStretch)
    {
        // Make sure we do not attempt to create a bitmap
        // with invalid size (width and/or height < 1)
        if (panelWidth < 1)
            panelWidth = 1;

        if (panelHeight < 1)
            panelHeight = 1;

        if (image.IsOk())
            image.Rescale(panelWidth, panelHeight);
    }
    // Should we center the image?
    else if (m_bCenterImage)
    {
        pos.x = (panelWidth - image.GetWidth()) / 2;
        pos.y = (panelHeight - image.GetHeight()) / 2;
    }

    if (image.IsOk())
    {
        bitmap = wxBitmap(image);
        dc.DrawBitmap(bitmap, pos.x, pos.y, false);
    }
}

/* Here we call refresh to tell the panel to draw itself again.
   So when the user resizes the image panel the image should be resized too. */
void wxImagePanel::OnSize(wxSizeEvent& event)
{
    Refresh();

    //skip the event.
    event.Skip();
}
