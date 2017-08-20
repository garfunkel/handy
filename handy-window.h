#ifndef __HANDY_WINDOW_H__
#define __HANDY_WINDOW_H__

G_BEGIN_DECLS

#define HANDY_TYPE_WINDOW handy_window_get_type()
G_DECLARE_FINAL_TYPE (HandyWindow, handy_window, HANDY, WINDOW, GtkApplicationWindow)

HandyWindow *handy_window_new();
void handy_window_setup(HandyWindow *window);
void handy_window_show_hide(const char *keystring, void *user_data);

G_END_DECLS

#endif // __HANDY_WINDOW_H__
