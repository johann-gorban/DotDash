#ifndef DOTDASH_CALLBACKS_H
#define DOTDASH_CALLBACKS_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "alphabet.h"

void	        callback_translate         (GtkWidget *, gpointer);
void            callback_copy              (GtkWidget *, gpointer);

const gchar     *get_text                  (GtkTextView *);
void	        text_translate             (const gchar *, gchar *);

#endif