/***************************************************************
 * Name:      wxVLCMain.h
 * Purpose:   Defines Application Frame
 * Author:    Tomay (tomay3000@gmail.com)
 * Created:   2018-05-23
 * Copyright: (c) Tomay
 * License:   wxWindows licence
 **************************************************************/

#ifndef WXVLCMAIN_H
#define WXVLCMAIN_H

#include <vlc/vlc.h>
#include "imagepanel.h"
#include <wx/popupwin.h>

//(*Headers(wxVLCFrame)
//#include "wx/wxImagePanel.h"
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
//*)

class wxVLCFrame: public wxFrame
{
public:

    wxVLCFrame(wxWindow *parent, wxWindowID id = -1);
    virtual ~wxVLCFrame();

private:

    //(*Handlers(wxVLCFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnPlay_Pause(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnVolumeChanged(wxScrollEvent& event);
    void OnTimelineChanged(wxScrollEvent& event);
    void OnToggleFullscreen(wxMouseEvent& event);
    void OnBackward(wxCommandEvent& event);
    void OnForward(wxCommandEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnTimer1(wxTimerEvent& event);
    //*)

    //(*Identifiers(wxVLCFrame)
    static const long ID_PNL_PLAYER;
    static const long ID_STATICLINE1;
    static const long ID_STTCTXT_CURRTIME;
    static const long ID_SLDR_TIMELINE;
    static const long ID_STTCTXT_MOVIELENGTH;
    static const long ID_BTN_PLAYPAUSE;
    static const long ID_BTN_STOP;
    static const long ID_BTN_BACKWARD;
    static const long ID_BTN_FORWARD;
    static const long ID_STATICTEXT1;
    static const long ID_SLDR_VOLUME;
    static const long ID_PNL_CONTROLS;
    static const long ID_MENUITEM1;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    static const long ID_TIMER1;
    //*)

    //(*Declarations(wxVLCFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxButton* Backward_Btn;
    wxButton* Forward_Btn;
    wxButton* Play_Pause_Btn;
    wxButton* Stop_Btn;
    wxFileDialog* OpenFile_Dlg;
    wxImagePanel* Player_Pnl;
    wxMenuItem* MenuItem3;
    wxPanel* Controls_Pnl;
    wxSlider* Timeline_Sldr;
    wxSlider* Volume_Sldr;
    wxStaticLine* StaticLine1;
    wxStaticText* CurrTime_SttcTxt;
    wxStaticText* MovieLength_SttcTxt;
    wxStaticText* StaticText1;
    wxStatusBar* StatusBar1;
    wxTimer Timer1;
    //*)

private:
    wxPopupWindow *Controls_Wnd;
    wxBoxSizer *BoxSizer;

private:
    void InitVLC();

public:
    void Play();
    void Pause();
    void Stop();
    void OnPositionChanged();
    void OnAudioVolumeChanged();

private:
    libvlc_media_player_t *media_player;
    libvlc_instance_t *vlc_inst;
    libvlc_event_manager_t *vlc_evt_man;

    DECLARE_EVENT_TABLE()
};

void OnPositionChanged_VLC(const libvlc_event_t *event, void *data);
void OnEndReached_VLC(const libvlc_event_t *event, void *data);
void OnAudioVolumeChanged_VLC(const libvlc_event_t *event, void *data);

#endif // WXVLCMAIN_H
