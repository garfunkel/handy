#ifndef __HANDY_POPOVER_H__
#define __HANDY_POPOVER_H__

G_BEGIN_DECLS

#define HANDY_TYPE_POPOVER handy_popover_get_type()
G_DECLARE_FINAL_TYPE (HandyPopover, handy_popover, HANDY, POPOVER, GtkPopover)

HandyPopover *handy_popover_new();
void handy_popover_setup();

G_END_DECLS

#endif // __HANDY_POPOVER_H__
