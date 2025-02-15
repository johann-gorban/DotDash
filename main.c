#include <gtk/gtk.h>
#include "activation.h"

#define APPLICATION_ID "gnome.DotDash"

gint main(gint argc, gchar **argv) {
	GtkApplication *app;
	gint status;
	
	app = gtk_application_new(APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate_application), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
