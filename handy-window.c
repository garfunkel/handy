#include <stdlib.h>

#include <glib-object.h>
#include <gtk/gtk.h>
#include <vte/vte.h>

#include "handy-window.h"
#include "handy-popover.h"

static void on_terminal_spawn(VteTerminal *terminal, GPid pid, GError *error, gpointer user_data) {
	if (error)
		perror(error->message);
}

struct _HandyWindow {
	GtkApplicationWindow parent_instance;

	GtkNotebook *tab_container;
	HandyPopover *terminal_popover;
};

G_DEFINE_TYPE(HandyWindow, handy_window, GTK_TYPE_APPLICATION_WINDOW)

enum {
	HANDY_WINDOW_SIGNAL,
	LAST_SIGNAL
};

static guint handy_window_signals[LAST_SIGNAL] = { 0 };

static void handy_window_init(HandyWindow *window) {
	// initialisation goes here
}

static void handy_window_class_init(HandyWindowClass *class) {
	// virtual function overrides go here
	// property and signal definitions go here
	handy_window_signals[HANDY_WINDOW_SIGNAL] = g_signal_new("bla", G_TYPE_FROM_CLASS(class), 0, 0, NULL, NULL, NULL, G_TYPE_NONE, 0);
}

HandyWindow *handy_window_new() {
	return g_object_new(HANDY_TYPE_WINDOW, NULL);
}

gboolean on_button_press(VteTerminal *terminal, GdkEvent *event, gpointer user_data) {
	if (event->type == GDK_BUTTON_PRESS && event->button.button == GDK_BUTTON_SECONDARY) {
		GdkRectangle *r = malloc(sizeof(GdkRectangle));

		r->x = event->button.x;
		r->y = event->button.y;
		r->width = 0;
		r->height = 0;

		gtk_popover_set_relative_to(GTK_POPOVER(((HandyWindow *)user_data)->terminal_popover), GTK_WIDGET(terminal));
		gtk_popover_set_pointing_to(GTK_POPOVER(((HandyWindow *)user_data)->terminal_popover), r);
		gtk_popover_popup(GTK_POPOVER(((HandyWindow *)user_data)->terminal_popover));
		gtk_widget_show_all(GTK_WIDGET(((HandyWindow *)user_data)->terminal_popover));
	}

	return FALSE;
}

void handy_window_new_terminal(HandyWindow *window) {
	GtkWidget *terminal = vte_terminal_new();
	char *argv[] = {vte_get_user_shell(), NULL};

	vte_terminal_spawn_async(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT,
	                         g_get_home_dir(), argv, NULL,
	                         G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, -1,
	                         NULL, on_terminal_spawn, window);

	gtk_notebook_append_page(window->tab_container, terminal, NULL);
	gtk_notebook_set_tab_reorderable(window->tab_container, terminal, TRUE);

	g_signal_connect(terminal, "button-press-event", (GCallback)on_button_press, window);
	g_signal_emit(window, handy_window_signals[HANDY_WINDOW_SIGNAL], 0);
}

static void handy_window_setup_terminals(HandyWindow *window, int num_terminals) {
	for (int i = 0; i < num_terminals; i++) {
		handy_window_new_terminal(window);
	}
}

void c(HandyWindow *window) {
}

void handy_window_setup(HandyWindow *window) {
	gtk_window_set_title(GTK_WINDOW(window), "Handy");
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_move(GTK_WINDOW(window), 0, 0);
	gtk_window_resize(GTK_WINDOW(window), 1920, 500);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);

	window->tab_container = (GtkNotebook *)gtk_notebook_new();

	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(window->tab_container));
	gtk_notebook_set_tab_pos(window->tab_container, GTK_POS_BOTTOM);
	gtk_notebook_set_show_border(window->tab_container, FALSE);

	g_signal_connect(window, "bla", (GCallback)c, NULL);

	handy_window_setup_terminals(window, 10);

	window->terminal_popover = (HandyPopover *)handy_popover_new();

	handy_popover_setup(window->terminal_popover);
}

void handy_window_show_hide(const char *keystring, void *user_data) {
	printf("Handle %s (%p)!\n", keystring, user_data);
}
