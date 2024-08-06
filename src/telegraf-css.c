#include "telegraf-css.h"

gchar* 
load_css (){
	GtkCssProvider *Provider;

	Provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (Provider, "./css/style.css");
	
	gchar *css_class = gtk_css_provider_to_string (Provider);
	return css_class;
}
