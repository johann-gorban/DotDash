#ifndef TELEGRAF_INIT_H
#define TELEGRAF_INIT_H

#include <gtk-4.0/gtk/gtk.h>

void	translate_to_morse      (const gchar *, gchar *);
void	print_text              (GtkWidget *, gpointer);
void	activate_application    (GtkApplication *, gpointer);

#endif