#include <gtk/gtk.h>
#include <vte/vte.h>

#include "handy-popover.h"

struct _HandyPopover {
	GtkPopover parent_instance;

	GtkBox *container_box;

	GtkBox *icon_menu_container_box;
	GtkModelButton *split_h_button;
	GtkModelButton *split_v_button;
	GtkSeparator *icon_menu_separator;
	GtkModelButton *copy_button;
	GtkModelButton *cut_button;
	GtkModelButton *paste_button;
	GtkModelButton *save_button;

	GtkSeparator *container_separator;

	GtkBox *menu_container_box;

	GtkBox *tab_menu_box;
	GtkModelButton *reset_button;
	GtkModelButton *new_tab_button;
	GtkModelButton *rename_tab_button;
	GtkModelButton *close_tab_button;

	GtkSeparator *menu_separator;

	GtkBox *handy_menu_box;
	GtkModelButton *fullscreen_button;
	GtkModelButton *prefs_button;
	GtkModelButton *about_button;
	GtkModelButton *quit_button;
};

G_DEFINE_TYPE(HandyPopover, handy_popover, GTK_TYPE_POPOVER)

static void handy_popover_init(HandyPopover *popover) {
	// initialisation goes here
}

static void handy_popover_class_init(HandyPopoverClass *class) {
	// virtual function overrides go here
	// property and signal definitions go here
}

HandyPopover *handy_popover_new() {
	return g_object_new(HANDY_TYPE_POPOVER, NULL);
}

void handy_popover_setup(HandyPopover *popover) {
	popover->container_box = (GtkBox *)gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	g_object_set(G_OBJECT(popover->container_box), "margin", 5, NULL);

	popover->icon_menu_container_box = (GtkBox *)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GFile *file = g_file_new_for_path("split-horizontal.svg");
	popover->split_h_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Split Horizontally", "icon", g_file_icon_new(file), "iconic", TRUE, "centered", TRUE, NULL);
	file = g_file_new_for_path("split-vertical.svg");
	popover->split_v_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Split Vertically", "icon", g_file_icon_new(file), "iconic", TRUE, "centered", TRUE, NULL);
	popover->icon_menu_separator = (GtkSeparator *)gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	popover->copy_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Copy", "icon", g_themed_icon_new("edit-copy"), "iconic", TRUE, "centered", TRUE, NULL);
	popover->cut_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Cut", "icon", g_themed_icon_new("edit-cut"), "iconic", TRUE, "centered", TRUE, NULL);
	popover->paste_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Paste", "icon", g_themed_icon_new("edit-paste"), "iconic", TRUE, "centered", TRUE, NULL);
	popover->save_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Save to File...", "icon", g_themed_icon_new("document-save-as"), "iconic", TRUE, "centered", TRUE, NULL);

	popover->container_separator = (GtkSeparator *)gtk_separator_new(GTK_ORIENTATION_VERTICAL);

	popover->menu_container_box = (GtkBox *)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	popover->tab_menu_box = (GtkBox *)gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	popover->reset_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Reset", NULL);
	popover->new_tab_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "New Tab", NULL);
	popover->rename_tab_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Rename Tab", NULL);
	popover->close_tab_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Close Tab", NULL);

	popover->menu_separator = (GtkSeparator *)gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	popover->handy_menu_box = (GtkBox *)gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	popover->fullscreen_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Full Screen", NULL);
	popover->prefs_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Preferences", NULL);
	popover->about_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "About", NULL);
	popover->quit_button = (GtkModelButton *)g_object_new(GTK_TYPE_MODEL_BUTTON, "text", "Quit", NULL);

	gtk_container_add(GTK_CONTAINER(popover), GTK_WIDGET(popover->container_box));
	gtk_container_add(GTK_CONTAINER(popover->container_box), GTK_WIDGET(popover->icon_menu_container_box));
	gtk_container_add(GTK_CONTAINER(popover->container_box), GTK_WIDGET(popover->container_separator));
	gtk_container_add(GTK_CONTAINER(popover->container_box), GTK_WIDGET(popover->menu_container_box));

	gtk_container_add(GTK_CONTAINER(popover->icon_menu_container_box), GTK_WIDGET(popover->split_h_button));
	gtk_container_add(GTK_CONTAINER(popover->icon_menu_container_box), GTK_WIDGET(popover->split_v_button));
	gtk_box_pack_start(popover->icon_menu_container_box, GTK_WIDGET(popover->icon_menu_separator), TRUE, FALSE, 0);
	gtk_box_pack_end(popover->icon_menu_container_box, GTK_WIDGET(popover->save_button), FALSE, FALSE, 0);
	gtk_box_pack_end(popover->icon_menu_container_box, GTK_WIDGET(popover->paste_button), FALSE, FALSE, 0);
	gtk_box_pack_end(popover->icon_menu_container_box, GTK_WIDGET(popover->cut_button), FALSE, FALSE, 0);
	gtk_box_pack_end(popover->icon_menu_container_box, GTK_WIDGET(popover->copy_button), FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(popover->menu_container_box), GTK_WIDGET(popover->tab_menu_box));
	gtk_box_pack_start(popover->menu_container_box, GTK_WIDGET(popover->menu_separator), TRUE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(popover->menu_container_box), GTK_WIDGET(popover->handy_menu_box));

	gtk_container_add(GTK_CONTAINER(popover->tab_menu_box), GTK_WIDGET(popover->reset_button));
	gtk_container_add(GTK_CONTAINER(popover->tab_menu_box), GTK_WIDGET(popover->new_tab_button));
	gtk_container_add(GTK_CONTAINER(popover->tab_menu_box), GTK_WIDGET(popover->rename_tab_button));
	gtk_container_add(GTK_CONTAINER(popover->tab_menu_box), GTK_WIDGET(popover->close_tab_button));

	gtk_container_add(GTK_CONTAINER(popover->handy_menu_box), GTK_WIDGET(popover->fullscreen_button));
	gtk_container_add(GTK_CONTAINER(popover->handy_menu_box), GTK_WIDGET(popover->prefs_button));
	gtk_container_add(GTK_CONTAINER(popover->handy_menu_box), GTK_WIDGET(popover->about_button));
	gtk_container_add(GTK_CONTAINER(popover->handy_menu_box), GTK_WIDGET(popover->quit_button));

	gtk_popover_set_constrain_to(GTK_POPOVER(popover), GTK_POPOVER_CONSTRAINT_NONE);
	gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
}
