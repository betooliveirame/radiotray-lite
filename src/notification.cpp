#include "notification.hpp"

namespace radiotray
{
Notification::Notification(const char* app_name)
    : app_name(app_name)
{
}

Notification::~Notification()
{
    if (notification != nullptr) {
        g_object_unref(G_OBJECT(notification));
    }

    if (notify_is_initted()) {
        notify_uninit();
    }
}

bool
Notification::init()
{
    bool initialized = notify_init(app_name.c_str());

    return initialized;
}

void
Notification::on_music_info_changed_signal(Glib::ustring station, Glib::ustring info)
{
    std::stringstream ss;

    ss << notify_get_app_name() << " - " << station;
    auto summary = Glib::ustring(ss.str());

    auto text = info;
    if ((not last_text.empty()) and text == last_text) {
        return;
    }

    if (notification == nullptr) {
        notification = notify_notification_new(summary.c_str(), text.c_str(), nullptr);
        if (notification != nullptr) {
            notify_notification_set_timeout(notification, NOTIFY_EXPIRES_DEFAULT);
            notify_notification_set_urgency(notification, NOTIFY_URGENCY_LOW);
            notify_notification_show(notification, nullptr);
        }
    } else {
        auto rc = notify_notification_update(notification, summary.c_str(), text.c_str(), nullptr);
        if (rc) {
            notify_notification_show(notification, nullptr);
        }
    }

    last_text = text;
}

} // namespace radiotray