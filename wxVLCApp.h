/***************************************************************
 * Name:      wxVLCApp.h
 * Purpose:   Defines Application Class
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-23
* Copyright:
(c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#ifndef WXVLCAPP_H
#define WXVLCAPP_H

#include <wx/app.h>

class wxVLCApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxDECLARE_APP(wxVLCApp);

#endif // WXVLCAPP_H
