#include "telegraf-css.h"

void
load_css (){
	GtkCssProvider *Provider;

	Provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_string (Provider, 
					   ".WidgetRounded textview {border-radius: 10px;}");

	gtk_style_context_add_provider_for_display (gdk_display_get_default(), 
						    GTK_STYLE_PROVIDER(Provider),
						    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
