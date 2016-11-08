#ifndef __NOTIFICATION_HPP_INCLUDED__
#define __NOTIFICATION_HPP_INCLUDED__

#include <string>
#include <sstream>

#include <gtkmm.h>
#include <libnotify/notify.h>

namespace radiotray
{

class Notification
{
public:
    Notification() = delete;
    Notification(const char* app_name);

    ~Notification();

    bool init();
    void on_music_info_changed_signal(Glib::ustring station, Glib::ustring info);

private:
    std::string app_name;
    NotifyNotification* notification = nullptr;

    Glib::ustring last_text;
};

} // namespace radiotray

#endif