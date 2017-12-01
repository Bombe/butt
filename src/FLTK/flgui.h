// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef flgui_h
#define flgui_h
#include <FL/Fl.H>
#include "FL/Fl_My_Double_Window.H"
#include <stdlib.h> 
#include "config.h"
#include "flgui.h"
#include "fl_timer_funcs.h"
#include "FL/Fl_My_Value_Slider.H"
#include <FL/Fl_Group.H>
#include "Fl_ILM216.h"
#include "fl_callbacks.h"
#include "cfg.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Round_Button.H>

class flgui {
public:
  bool info_visible; 
  Fl_Text_Buffer *info_buffer; 
  flgui();
  Fl_My_Double_Window *window_main;
private:
  inline void cb_window_main_i(Fl_My_Double_Window*, void*);
  static void cb_window_main(Fl_My_Double_Window*, void*);
public:
  Fl_My_Value_Slider *slider_gain;
private:
  inline void cb_slider_gain_i(Fl_My_Value_Slider*, void*);
  static void cb_slider_gain(Fl_My_Value_Slider*, void*);
public:
  Fl_ILM216 *lcd;
private:
  inline void cb_lcd_i(Fl_ILM216*, void*);
  static void cb_lcd(Fl_ILM216*, void*);
public:
  Fl_Button *button_connect;
private:
  inline void cb_button_connect_i(Fl_Button*, void*);
  static void cb_button_connect(Fl_Button*, void*);
  Fl_Button *button_disconnect;
  inline void cb_button_disconnect_i(Fl_Button*, void*);
  static void cb_button_disconnect(Fl_Button*, void*);
  Fl_Button *button_record;
  inline void cb_button_record_i(Fl_Button*, void*);
  static void cb_button_record(Fl_Button*, void*);
public:
  Fl_Button *button_info;
private:
  inline void cb_button_info_i(Fl_Button*, void*);
  static void cb_button_info(Fl_Button*, void*);
public:
  Fl_Group *LEDs_dark;
  Fl_Box *right_1_dark;
  Fl_Box *right_2_dark;
  Fl_Box *right_3_dark;
  Fl_Box *right_4_dark;
  Fl_Box *right_5_dark;
  Fl_Box *right_6_dark;
  Fl_Box *right_7_dark;
  Fl_Box *right_8_dark;
  Fl_Box *right_9_dark;
  Fl_Box *left_1_dark;
  Fl_Box *left_2_dark;
  Fl_Box *left_3_dark;
  Fl_Box *left_4_dark;
  Fl_Box *left_5_dark;
  Fl_Box *left_6_dark;
  Fl_Box *left_7_dark;
  Fl_Box *left_8_dark;
  Fl_Box *left_9_dark;
  Fl_Group *LEDs_light;
  Fl_Box *right_1_light;
  Fl_Box *right_2_light;
  Fl_Box *right_3_light;
  Fl_Box *right_4_light;
  Fl_Box *right_5_light;
  Fl_Box *right_6_light;
  Fl_Box *right_7_light;
  Fl_Box *right_8_light;
  Fl_Box *right_9_light;
  Fl_Box *left_1_light;
  Fl_Box *left_2_light;
  Fl_Box *left_3_light;
  Fl_Box *left_4_light;
  Fl_Box *left_5_light;
  Fl_Box *left_6_light;
  Fl_Box *left_7_light;
  Fl_Box *left_8_light;
  Fl_Box *left_9_light;
  Fl_Text_Display *info_output;
  Fl_Button *button_cfg;
private:
  inline void cb_button_cfg_i(Fl_Button*, void*);
  static void cb_button_cfg(Fl_Button*, void*);
public:
  Fl_Box *VU_Text;
  Fl_Box *R_VU;
  Fl_Box *L_VU;
  Fl_My_Double_Window *window_cfg;
private:
  inline void cb_window_cfg_i(Fl_My_Double_Window*, void*);
  static void cb_window_cfg(Fl_My_Double_Window*, void*);
public:
  Fl_Tabs *Settings;
  Fl_Choice *choice_cfg_act_srv;
private:
  inline void cb_choice_cfg_act_srv_i(Fl_Choice*, void*);
  static void cb_choice_cfg_act_srv(Fl_Choice*, void*);
  inline void cb_ADD_i(Fl_Button*, void*);
  static void cb_ADD(Fl_Button*, void*);
public:
  Fl_Button *button_cfg_edit_srv;
private:
  inline void cb_button_cfg_edit_srv_i(Fl_Button*, void*);
  static void cb_button_cfg_edit_srv(Fl_Button*, void*);
public:
  Fl_Button *button_cfg_del_srv;
private:
  inline void cb_button_cfg_del_srv_i(Fl_Button*, void*);
  static void cb_button_cfg_del_srv(Fl_Button*, void*);
public:
  Fl_Choice *choice_cfg_act_icy;
private:
  inline void cb_choice_cfg_act_icy_i(Fl_Choice*, void*);
  static void cb_choice_cfg_act_icy(Fl_Choice*, void*);
  inline void cb_ADD1_i(Fl_Button*, void*);
  static void cb_ADD1(Fl_Button*, void*);
public:
  Fl_Button *button_cfg_edit_icy;
private:
  inline void cb_button_cfg_edit_icy_i(Fl_Button*, void*);
  static void cb_button_cfg_edit_icy(Fl_Button*, void*);
public:
  Fl_Button *button_cfg_del_icy;
private:
  inline void cb_button_cfg_del_icy_i(Fl_Button*, void*);
  static void cb_button_cfg_del_icy(Fl_Button*, void*);
public:
  Fl_Input *input_log_filename;
private:
  inline void cb_input_log_filename_i(Fl_Input*, void*);
  static void cb_input_log_filename(Fl_Input*, void*);
  inline void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
  inline void cb_Import_i(Fl_Button*, void*);
  static void cb_Import(Fl_Button*, void*);
  inline void cb_Save_i(Fl_Button*, void*);
  static void cb_Save(Fl_Button*, void*);
  inline void cb_Export_i(Fl_Button*, void*);
  static void cb_Export(Fl_Button*, void*);
public:
  Fl_Choice *choice_cfg_dev;
private:
  inline void cb_choice_cfg_dev_i(Fl_Choice*, void*);
  static void cb_choice_cfg_dev(Fl_Choice*, void*);
public:
  Fl_Choice *choice_cfg_channel;
  static Fl_Menu_Item menu_choice_cfg_channel[];
private:
  inline void cb_Stereo_i(Fl_Menu_*, void*);
  static void cb_Stereo(Fl_Menu_*, void*);
  inline void cb_Mono_i(Fl_Menu_*, void*);
  static void cb_Mono(Fl_Menu_*, void*);
public:
  Fl_Choice *choice_cfg_samplerate;
private:
  inline void cb_choice_cfg_samplerate_i(Fl_Choice*, void*);
  static void cb_choice_cfg_samplerate(Fl_Choice*, void*);
public:
  Fl_Choice *choice_cfg_source_channel;
  Fl_Choice *choice_cfg_codec;
  static Fl_Menu_Item menu_choice_cfg_codec[];
private:
  inline void cb_MP3_i(Fl_Menu_*, void*);
  static void cb_MP3(Fl_Menu_*, void*);
  inline void cb_OGG_i(Fl_Menu_*, void*);
  static void cb_OGG(Fl_Menu_*, void*);
  inline void cb_OPUS_i(Fl_Menu_*, void*);
  static void cb_OPUS(Fl_Menu_*, void*);
  inline void cb_AAC_i(Fl_Menu_*, void*);
  static void cb_AAC(Fl_Menu_*, void*);
public:
  Fl_Choice *choice_cfg_bitrate;
private:
  inline void cb_choice_cfg_bitrate_i(Fl_Choice*, void*);
  static void cb_choice_cfg_bitrate(Fl_Choice*, void*);
  static Fl_Menu_Item menu_choice_cfg_bitrate[];
public:
  Fl_Choice *choice_rec_codec;
  static Fl_Menu_Item menu_choice_rec_codec[];
private:
  inline void cb_MP31_i(Fl_Menu_*, void*);
  static void cb_MP31(Fl_Menu_*, void*);
  inline void cb_OGG1_i(Fl_Menu_*, void*);
  static void cb_OGG1(Fl_Menu_*, void*);
  inline void cb_OPUS1_i(Fl_Menu_*, void*);
  static void cb_OPUS1(Fl_Menu_*, void*);
  inline void cb_AAC1_i(Fl_Menu_*, void*);
  static void cb_AAC1(Fl_Menu_*, void*);
  inline void cb_FLAC_i(Fl_Menu_*, void*);
  static void cb_FLAC(Fl_Menu_*, void*);
  inline void cb_WAV_i(Fl_Menu_*, void*);
  static void cb_WAV(Fl_Menu_*, void*);
public:
  Fl_Choice *choice_rec_bitrate;
private:
  inline void cb_choice_rec_bitrate_i(Fl_Choice*, void*);
  static void cb_choice_rec_bitrate(Fl_Choice*, void*);
  static Fl_Menu_Item menu_choice_rec_bitrate[];
public:
  Fl_Button *button_advanced;
private:
  inline void cb_button_advanced_i(Fl_Button*, void*);
  static void cb_button_advanced(Fl_Button*, void*);
public:
  Fl_Value_Input *input_cfg_buffer;
private:
  inline void cb_input_cfg_buffer_i(Fl_Value_Input*, void*);
  static void cb_input_cfg_buffer(Fl_Value_Input*, void*);
public:
  Fl_Choice *choice_cfg_resample_mode;
private:
  inline void cb_choice_cfg_resample_mode_i(Fl_Choice*, void*);
  static void cb_choice_cfg_resample_mode(Fl_Choice*, void*);
  static Fl_Menu_Item menu_choice_cfg_resample_mode[];
public:
  Fl_Input *input_cfg_song_file;
private:
  inline void cb_input_cfg_song_file_i(Fl_Input*, void*);
  static void cb_input_cfg_song_file(Fl_Input*, void*);
public:
  Fl_Button *button_songfile_browse;
private:
  inline void cb_button_songfile_browse_i(Fl_Button*, void*);
  static void cb_button_songfile_browse(Fl_Button*, void*);
public:
  Fl_Check_Button *check_song_update_active;
private:
  inline void cb_check_song_update_active_i(Fl_Check_Button*, void*);
  static void cb_check_song_update_active(Fl_Check_Button*, void*);
public:
  Fl_Input *input_cfg_song;
private:
  inline void cb_input_cfg_song_i(Fl_Input*, void*);
  static void cb_input_cfg_song(Fl_Input*, void*);
  inline void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
public:
  Fl_Check_Button *check_cfg_connect;
private:
  inline void cb_check_cfg_connect_i(Fl_Check_Button*, void*);
  static void cb_check_cfg_connect(Fl_Check_Button*, void*);
public:
  Fl_Input *input_rec_filename;
private:
  inline void cb_input_rec_filename_i(Fl_Input*, void*);
  static void cb_input_rec_filename(Fl_Input*, void*);
public:
  Fl_Input *input_rec_folder;
private:
  inline void cb_input_rec_folder_i(Fl_Input*, void*);
  static void cb_input_rec_folder(Fl_Input*, void*);
public:
  Fl_Button *button_rec_browse;
private:
  inline void cb_button_rec_browse_i(Fl_Button*, void*);
  static void cb_button_rec_browse(Fl_Button*, void*);
public:
  Fl_Value_Input *input_rec_split_time;
private:
  inline void cb_input_rec_split_time_i(Fl_Value_Input*, void*);
  static void cb_input_rec_split_time(Fl_Value_Input*, void*);
public:
  Fl_Box *text_rec_split_time;
  Fl_Check_Button *check_sync_to_full_hour;
private:
  inline void cb_check_sync_to_full_hour_i(Fl_Check_Button*, void*);
  static void cb_check_sync_to_full_hour(Fl_Check_Button*, void*);
  inline void cb_Split_i(Fl_Button*, void*);
  static void cb_Split(Fl_Button*, void*);
public:
  Fl_Check_Button *check_cfg_rec;
private:
  inline void cb_check_cfg_rec_i(Fl_Check_Button*, void*);
  static void cb_check_cfg_rec(Fl_Check_Button*, void*);
public:
  Fl_Button *button_gui_text_color;
private:
  inline void cb_button_gui_text_color_i(Fl_Button*, void*);
  static void cb_button_gui_text_color(Fl_Button*, void*);
public:
  Fl_Button *button_gui_bg_color;
private:
  inline void cb_button_gui_bg_color_i(Fl_Button*, void*);
  static void cb_button_gui_bg_color(Fl_Button*, void*);
public:
  Fl_Check_Button *check_gui_attach;
private:
  inline void cb_check_gui_attach_i(Fl_Check_Button*, void*);
  static void cb_check_gui_attach(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *check_gui_ontop;
private:
  inline void cb_check_gui_ontop_i(Fl_Check_Button*, void*);
  static void cb_check_gui_ontop(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *check_gui_lcd_auto;
private:
  inline void cb_check_gui_lcd_auto_i(Fl_Check_Button*, void*);
  static void cb_check_gui_lcd_auto(Fl_Check_Button*, void*);
public:
  Fl_Double_Window *window_add_srv;
  Fl_Input *input_add_srv_name;
  Fl_Input *input_add_srv_addr;
  Fl_Int_Input *input_add_srv_port;
  Fl_Input *input_add_srv_pwd;
  Fl_Input *input_add_srv_mount;
  Fl_Input *input_add_srv_usr;
  Fl_Round_Button *radio_add_srv_shoutcast;
private:
  inline void cb_radio_add_srv_shoutcast_i(Fl_Round_Button*, void*);
  static void cb_radio_add_srv_shoutcast(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *radio_add_srv_icecast;
private:
  inline void cb_radio_add_srv_icecast_i(Fl_Round_Button*, void*);
  static void cb_radio_add_srv_icecast(Fl_Round_Button*, void*);
  inline void cb_Cancel_i(Fl_Button*, void*);
  static void cb_Cancel(Fl_Button*, void*);
public:
  Fl_Button *button_add_srv_add;
private:
  inline void cb_button_add_srv_add_i(Fl_Button*, void*);
  static void cb_button_add_srv_add(Fl_Button*, void*);
public:
  Fl_Button *button_add_srv_save;
private:
  inline void cb_button_add_srv_save_i(Fl_Button*, void*);
  static void cb_button_add_srv_save(Fl_Button*, void*);
public:
  Fl_Button *button_cfg_show_pw;
private:
  inline void cb_button_cfg_show_pw_i(Fl_Button*, void*);
  static void cb_button_cfg_show_pw(Fl_Button*, void*);
public:
  Fl_Double_Window *window_add_icy;
  Fl_Input *input_add_icy_name;
  Fl_Input *input_add_icy_desc;
  Fl_Input *input_add_icy_genre;
  Fl_Input *input_add_icy_url;
  Fl_Input *input_add_icy_icq;
  Fl_Input *input_add_icy_irc;
  Fl_Input *input_add_icy_aim;
  Fl_Check_Button *check_add_icy_pub;
private:
  inline void cb_Cancel1_i(Fl_Button*, void*);
  static void cb_Cancel1(Fl_Button*, void*);
public:
  Fl_Button *button_add_icy_add;
private:
  inline void cb_button_add_icy_add_i(Fl_Button*, void*);
  static void cb_button_add_icy_add(Fl_Button*, void*);
public:
  Fl_Button *button_add_icy_save;
private:
  inline void cb_button_add_icy_save_i(Fl_Button*, void*);
  static void cb_button_add_icy_save(Fl_Button*, void*);
public:
  ~flgui();
};
#endif
