#ifndef TELEGRAF_INIT_H
#define TELEGRAF_INIT_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>

const gchar     *get_text               (GtkTextView *);

void	        text_translate          (const gchar *, gchar *);

void	        event_translate         (GtkWidget *, gpointer);
void            event_copy              (GtkWidget *, gpointer);

void	        activate_application    (GtkApplication *, gpointer);

#endif
