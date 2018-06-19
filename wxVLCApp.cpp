/***************************************************************
 * Name:      wxVLCApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-23
 * Copyright: (c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#include "wx_pch.h"
#include "wxVLCApp.h"

//(*AppHeaders
#include "wxVLCMain.h"
#include <wx/image.h>
//*)

wxIMPLEMENT_APP(wxVLCApp);

bool wxVLCApp::OnInit()
{
#ifdef GDK_WINDOWING_X11
    XInitThreads();
#endif // GDK_WINDOWING_X11

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        wxVLCFrame *Frame = new wxVLCFrame(NULL);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
