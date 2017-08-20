#include <stdio.h>

#include <gtk/gtk.h>
#include <keybinder.h>

#include "handy-window.h"

void handy_show_hide(const char *keystring, void *user_data) {
	HandyWindow *window = (HandyWindow *)user_data;

	gtk_widget_set_visible(GTK_WIDGET(window), !gtk_widget_get_visible(GTK_WIDGET(window)));

	printf("Handle %s (%p)!\n", keystring, user_data);
}

static void activate(GtkApplication *app, gpointer user_data) {
	GList *list = gtk_application_get_windows(app);

	if (list) {
		gtk_window_present(GTK_WINDOW(list->data));
	} else {
		HandyWindow *window = handy_window_new(app);

		handy_window_setup(window);

		gtk_window_set_application(GTK_WINDOW(window), app);
		gtk_widget_show_all(GTK_WIDGET(window));

		keybinder_init();
		keybinder_bind("F10", handy_show_hide, window);
	}
}

int main(int argc, char **argv) {
	GtkApplication *app = gtk_application_new("org.simonallen.handy", 0);

	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	int status = g_application_run(G_APPLICATION(app), argc, argv);

	g_object_unref(app);

	return status;
}
