/***************************************************************
 * Name:      wxVLCMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-23
 * Copyright: (c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#include "wx_pch.h"
#include "wxVLCApp.h"
#include "wxVLCMain.h"
#include <wx/msgdlg.h>
#include <wx/filename.h>

#ifdef __WXGTK__
#include <gtk/gtk.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#define GET_XID(window) GDK_WINDOW_XID(window->GTKGetDrawingWindow())
#endif // GDK_WINDOWING_X11
#endif

//(*InternalHeaders(wxVLCFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxVLCFrame)
const long wxVLCFrame::ID_PNL_PLAYER = wxNewId();
const long wxVLCFrame::ID_STATICLINE1 = wxNewId();
const long wxVLCFrame::ID_STTCTXT_CURRTIME = wxNewId();
const long wxVLCFrame::ID_SLDR_TIMELINE = wxNewId();
const long wxVLCFrame::ID_STTCTXT_MOVIELENGTH = wxNewId();
const long wxVLCFrame::ID_BTN_PLAYPAUSE = wxNewId();
const long wxVLCFrame::ID_BTN_STOP = wxNewId();
const long wxVLCFrame::ID_BTN_BACKWARD = wxNewId();
const long wxVLCFrame::ID_BTN_FORWARD = wxNewId();
const long wxVLCFrame::ID_STATICTEXT1 = wxNewId();
const long wxVLCFrame::ID_SLDR_VOLUME = wxNewId();
const long wxVLCFrame::ID_PNL_CONTROLS = wxNewId();
const long wxVLCFrame::ID_MENUITEM1 = wxNewId();
const long wxVLCFrame::idMenuQuit = wxNewId();
const long wxVLCFrame::idMenuAbout = wxNewId();
const long wxVLCFrame::ID_STATUSBAR1 = wxNewId();
const long wxVLCFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxVLCFrame, wxFrame)
    //(*EventTable(wxVLCFrame)
    //*)
END_EVENT_TABLE()

wxVLCFrame::wxVLCFrame(wxWindow *parent, wxWindowID id)
{
    //(*Initialize(wxVLCFrame)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("wxVLC Media Player"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("./res/vlc.ico"))));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Player_Pnl = new wxImagePanel(this, ID_PNL_PLAYER, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PNL_PLAYER"));
    Player_Pnl->SetStretch(false);
    Player_Pnl->SetMinSize(wxSize(-1,300));
    Player_Pnl->SetBackgroundColour(wxColour(0,0,0));
    BoxSizer1->Add(Player_Pnl, 1, wxEXPAND, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer1->Add(StaticLine1, 0, wxALL|wxEXPAND, 5);
    Controls_Pnl = new wxPanel(this, ID_PNL_CONTROLS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PNL_CONTROLS"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    CurrTime_SttcTxt = new wxStaticText(Controls_Pnl, ID_STTCTXT_CURRTIME, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STTCTXT_CURRTIME"));
    BoxSizer3->Add(CurrTime_SttcTxt, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Timeline_Sldr = new wxSlider(Controls_Pnl, ID_SLDR_TIMELINE, 0, 0, 10000, wxDefaultPosition, wxDefaultSize, wxSL_BOTH|wxSL_SELRANGE, wxDefaultValidator, _T("ID_SLDR_TIMELINE"));
    Timeline_Sldr->Disable();
    BoxSizer3->Add(Timeline_Sldr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MovieLength_SttcTxt = new wxStaticText(Controls_Pnl, ID_STTCTXT_MOVIELENGTH, _("00:00:00"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STTCTXT_MOVIELENGTH"));
    BoxSizer3->Add(MovieLength_SttcTxt, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    Play_Pause_Btn = new wxButton(Controls_Pnl, ID_BTN_PLAYPAUSE, _("Play >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_PLAYPAUSE"));
    Play_Pause_Btn->Disable();
    BoxSizer4->Add(Play_Pause_Btn, 0, wxALL|wxEXPAND, 5);
    Stop_Btn = new wxButton(Controls_Pnl, ID_BTN_STOP, _("Stop []"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_STOP"));
    Stop_Btn->Disable();
    BoxSizer4->Add(Stop_Btn, 0, wxALL|wxEXPAND, 5);
    Backward_Btn = new wxButton(Controls_Pnl, ID_BTN_BACKWARD, _("Backward <<"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_BACKWARD"));
    Backward_Btn->Disable();
    BoxSizer4->Add(Backward_Btn, 0, wxALL|wxEXPAND, 5);
    Forward_Btn = new wxButton(Controls_Pnl, ID_BTN_FORWARD, _("Forward >>"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_FORWARD"));
    Forward_Btn->Disable();
    BoxSizer4->Add(Forward_Btn, 0, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(Controls_Pnl, ID_STATICTEXT1, _("Volume"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Volume_Sldr = new wxSlider(Controls_Pnl, ID_SLDR_VOLUME, 100, 0, 100, wxDefaultPosition, wxDLG_UNIT(Controls_Pnl,wxSize(50,-1)), wxSL_LABELS|wxSL_BOTH, wxDefaultValidator, _T("ID_SLDR_VOLUME"));
    BoxSizer4->Add(Volume_Sldr, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer4, 0, wxALL|wxEXPAND, 5);
    Controls_Pnl->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Controls_Pnl);
    BoxSizer2->SetSizeHints(Controls_Pnl);
    BoxSizer1->Add(Controls_Pnl, 0, wxEXPAND, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("&Open\tCtrl-O"), _("Open the video file"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    OpenFile_Dlg = new wxFileDialog(this, _("Select an audio/video file"), wxEmptyString, wxEmptyString, _("All files (*.*)|*.*"), wxFD_DEFAULT_STYLE|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    OpenFile_Dlg->Center();
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(3000, true);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();

    Player_Pnl->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&wxVLCFrame::OnToggleFullscreen,0,this);
    Player_Pnl->Connect(wxEVT_MOTION,(wxObjectEventFunction)&wxVLCFrame::OnMouseMove,0,this);
    Connect(ID_SLDR_TIMELINE,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVLCFrame::OnTimelineChanged);
    Connect(ID_SLDR_TIMELINE,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&wxVLCFrame::OnTimelineChanged);
    Connect(ID_BTN_PLAYPAUSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxVLCFrame::OnPlay_Pause);
    Connect(ID_BTN_STOP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxVLCFrame::OnStop);
    Connect(ID_BTN_BACKWARD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxVLCFrame::OnBackward);
    Connect(ID_BTN_FORWARD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxVLCFrame::OnForward);
    Connect(ID_SLDR_VOLUME,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&wxVLCFrame::OnVolumeChanged);
    Connect(ID_SLDR_VOLUME,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&wxVLCFrame::OnVolumeChanged);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxVLCFrame::OnOpen);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxVLCFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxVLCFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&wxVLCFrame::OnTimer1);
    //*)

    Controls_Wnd = new wxPopupWindow(this);
    BoxSizer = new wxBoxSizer(wxVERTICAL);
    Controls_Wnd->SetSizer(BoxSizer);

    Maximize();
    Player_Pnl->LoadFile(_T("./res/vlc.png"));
    Player_Pnl->CenterImage();

    // Setup vlc
    vlc_inst = libvlc_new(0, NULL);
    media_player = libvlc_media_player_new(vlc_inst);
    vlc_evt_man = libvlc_media_player_event_manager(media_player);
    libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEndReached, ::OnEndReached_VLC, NULL);
    libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPositionChanged, ::OnPositionChanged_VLC, NULL);
    libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerAudioVolume, ::OnAudioVolumeChanged_VLC, NULL);

    InitVLC();
}

wxVLCFrame::~wxVLCFrame()
{
    //(*Destroy(wxVLCFrame)
    //*)

    Controls_Wnd->Destroy();
}

void wxVLCFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxVLCFrame::OnAbout(wxCommandEvent& event)
{
    wxString build = wxbuildinfo(long_f);
    wxString about = _T("wxVLC is a wxWidgets GUI media player that\nuses libVLC framework as its core multimedia engine.");
    wxMessageBox(about + _T("\n\nBuilt using:\n") + build, _T("About wxVLC..."));
}

void wxVLCFrame::OnOpen(wxCommandEvent& event)
{
    if (OpenFile_Dlg->ShowModal() == wxID_OK)
    {
        libvlc_media_t *media;
        wxString filename(OpenFile_Dlg->GetPath());
        media = libvlc_media_new_path(vlc_inst, filename.ToUTF8());
        libvlc_media_player_set_media(media_player, media);
        Play();
        libvlc_media_release(media);
        SetTitle(wxFileName(filename).GetFullName() + _T(" - wxVLC Media Player") /*+ _T(" - ") + wxGetApp().GetAppDisplayName()*/);
    }
}

void wxVLCFrame::InitVLC()
{
#ifdef __WXGTK__
    gtk_widget_realize(Player_Pnl->GetHandle());
    libvlc_media_player_set_xwindow(media_player, GET_XID(Player_Pnl));
#elif defined(__WXOSX__)
    libvlc_media_player_set_nsobject(media_player, Player_Pnl->GetHandle());
#elif defined(__WXMSW__)
    libvlc_media_player_set_hwnd(media_player, Player_Pnl->GetHandle());
#endif

    libvlc_video_set_mouse_input(media_player, false);
    libvlc_video_set_key_input(media_player, false);
}

void wxVLCFrame::Play()
{
    libvlc_media_player_play(media_player);
    Play_Pause_Btn->SetLabel(_T("Pause ||"));
    Play_Pause_Btn->Enable();
    Stop_Btn->Enable();
    Backward_Btn->Enable();
    Forward_Btn->Enable();
    Timeline_Sldr->Enable();
}

void wxVLCFrame::Pause()
{
    libvlc_media_player_pause(media_player);
    Play_Pause_Btn->SetLabel(_T("Play >"));
}

void wxVLCFrame::Stop()
{
    Pause();
    libvlc_media_player_stop(media_player);
    Stop_Btn->Disable();
    Backward_Btn->Disable();
    Forward_Btn->Disable();
    Timeline_Sldr->SetValue(0);
    Timeline_Sldr->Disable();
    CurrTime_SttcTxt->SetLabel(_T("00:00:00"));
    BoxSizer3->Layout();
}

void wxVLCFrame::OnPlay_Pause(wxCommandEvent& event)
{
    if (libvlc_media_player_is_playing(media_player))
        Pause();
    else
        Play();
}

void wxVLCFrame::OnStop(wxCommandEvent& event)
{
    Stop();
}

void wxVLCFrame::OnVolumeChanged(wxScrollEvent& event)
{
    libvlc_audio_set_volume(media_player, Volume_Sldr->GetValue());
}

void wxVLCFrame::OnTimelineChanged(wxScrollEvent& event)
{
    libvlc_media_player_set_time(media_player, Timeline_Sldr->GetValue() * 1000);
    libvlc_time_t currTime = libvlc_media_player_get_time(media_player);
    CurrTime_SttcTxt->SetLabel(wxTimeSpan::Milliseconds(currTime).Format());
    BoxSizer3->Layout();
}

void wxVLCFrame::OnPositionChanged()
{
    libvlc_time_t currTime = libvlc_media_player_get_time(media_player);
    CurrTime_SttcTxt->SetLabel(wxTimeSpan::Milliseconds(currTime).Format());
    libvlc_time_t movieLength = libvlc_media_player_get_length(media_player);
    Timeline_Sldr->SetMax(movieLength / 1000);
    Timeline_Sldr->SetValue(currTime / 1000);
    MovieLength_SttcTxt->SetLabel(wxTimeSpan::Milliseconds(movieLength).Format());

    unsigned width = 0, height = 0;
    libvlc_video_get_size(media_player, 0, &width, &height);
    int video_track = libvlc_video_get_track(media_player);
    int audio_track = libvlc_audio_get_track(media_player);
    int subtitle = libvlc_video_get_spu(media_player);
    StatusBar1->SetStatusText(wxString::Format(_T("Video size: %d x %d     -     Video track: %d     -     Audio track: %d     -     Subtitle: %d"),
                              width, height, video_track, audio_track, subtitle));

    BoxSizer3->Layout();
}

void wxVLCFrame::OnAudioVolumeChanged()
{
    int volume = libvlc_audio_get_volume(media_player);
    Volume_Sldr->SetValue(volume);
}

void OnPositionChanged_VLC(const libvlc_event_t *event, void *data)
{
    wxVLCFrame *mainFrame = ((wxVLCFrame *)wxGetApp().GetTopWindow());
    mainFrame->CallAfter(&wxVLCFrame::OnPositionChanged);
}

void OnEndReached_VLC(const libvlc_event_t *event, void *data)
{
    wxVLCFrame *mainFrame = ((wxVLCFrame *)wxGetApp().GetTopWindow());
    mainFrame->CallAfter(&wxVLCFrame::Stop);
}

void OnAudioVolumeChanged_VLC(const libvlc_event_t *event, void *data)
{
    wxVLCFrame *mainFrame = ((wxVLCFrame *)wxGetApp().GetTopWindow());
    mainFrame->CallAfter(&wxVLCFrame::OnAudioVolumeChanged);
}

void wxVLCFrame::OnToggleFullscreen(wxMouseEvent& event)
{
    libvlc_state_t state = libvlc_media_player_get_state(media_player);

    if (IsFullScreen())
    {
        Controls_Wnd->Hide();
        BoxSizer->Detach(Controls_Pnl);
        Controls_Pnl->Reparent(this);
        BoxSizer1->Add(Controls_Pnl, 0, wxEXPAND, 5);
        StaticLine1->Show();
        ShowFullScreen(false);
    }
    else if (state != libvlc_NothingSpecial /*&& state != libvlc_Ended*/ && state != libvlc_Error)
    {
        StaticLine1->Hide();
        BoxSizer1->Detach(Controls_Pnl);
        Controls_Pnl->Reparent(Controls_Wnd);
        BoxSizer->Add(Controls_Pnl, 0, wxEXPAND, 5);
        ShowFullScreen(true);
        Controls_Wnd->Fit();

        wxSize ScreenSize = wxGetDisplaySize();
        wxSize Controls_Wnd_Size(Controls_Wnd->GetBestSize());
        Controls_Wnd->SetSize(ScreenSize.GetWidth(), wxDefaultCoord /*Controls_Wnd_Size.GetHeight()*/);
        Controls_Wnd->Position(wxPoint(0, ScreenSize.y), wxSize());
    }
}

void wxVLCFrame::OnBackward(wxCommandEvent& event)
{
    libvlc_time_t currTime = libvlc_media_player_get_time(media_player);
    currTime -= 60000;

    if (currTime < 0)
        currTime = 0;

    libvlc_media_player_set_time(media_player, currTime);
    OnPositionChanged();
}

void wxVLCFrame::OnForward(wxCommandEvent& event)
{
    libvlc_time_t currTime = libvlc_media_player_get_time(media_player);
    libvlc_time_t movieLength = libvlc_media_player_get_length(media_player);
    currTime += 60000;

    if (currTime > movieLength)
        currTime = movieLength - 1;

    libvlc_media_player_set_time(media_player, currTime);
    OnPositionChanged();
}

void wxVLCFrame::OnMouseMove(wxMouseEvent& event)
{
    if (IsFullScreen())
    {
        Controls_Wnd->Show();
        Timer1.StartOnce();
    }
}

void wxVLCFrame::OnTimer1(wxTimerEvent& event)
{
    if (IsFullScreen())
    {
        wxPoint pt;
        wxWindow *window = wxFindWindowAtPointer(pt);

        if (Controls_Wnd->IsDescendant(window))
            Timer1.StartOnce();
        else
        {
            Controls_Wnd->Hide();
            BoxSizer1->Layout();
        }
    }
}
