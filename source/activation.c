#include "activation.h"
#include "callbacks.h"

void
load_css (void){
	GtkCssProvider *Provider;

	Provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_string (Provider, 
					   ".WidgetRounded textview {border-radius: 10px;}");

	gtk_style_context_add_provider_for_display (gdk_display_get_default(), 
						    GTK_STYLE_PROVIDER(Provider),
						    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void 
activate_application (GtkApplication* app, gpointer user_data) {
/*--------------------------OBJECTS-----------------------------------------------------*/
	// GError *Error;
	GtkWidget *Window;
	GtkWidget *TextIn, *TextOut;
	GtkWidget *ScrollTextIn, *ScrollTextOut;
	GtkWidget *ButtonRead, *ButtonCopy;
	GtkWidget *Box, *BoxButton;
	
	GtkTextView **TextWidgets = g_new (GtkTextView*, 2);
/*--------------------------WINDOW------------------------------------------------------*/
	Window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (Window), "DotDash");

	gtk_window_set_default_size (GTK_WINDOW (Window), 350, 400);
	gtk_window_set_resizable (GTK_WINDOW (Window), FALSE);
/*--------------------------TEXTS-------------------------------------------------------*/
	TextIn = gtk_text_view_new ();
	TextOut = gtk_text_view_new ();

	gtk_text_view_set_editable (GTK_TEXT_VIEW (TextOut), FALSE);

	gtk_widget_set_margin_bottom (TextIn, 5);
	gtk_widget_set_margin_bottom (TextOut, 5);
	
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(TextIn), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(TextOut), GTK_WRAP_WORD_CHAR);

	TextWidgets[0] = GTK_TEXT_VIEW (TextIn);
	TextWidgets[1] = GTK_TEXT_VIEW (TextOut);
/*--------------------------SCROLLED----------------------------------------------------*/
	ScrollTextIn = gtk_scrolled_window_new ();
	ScrollTextOut = gtk_scrolled_window_new ();

	load_css();
	gtk_widget_add_css_class(ScrollTextIn, "WidgetRounded");
	gtk_widget_add_css_class(ScrollTextOut, "WidgetRounded");

	gtk_widget_set_size_request (ScrollTextIn, 250, 100); 
	gtk_widget_set_size_request (ScrollTextOut, 250, 100);

	gtk_widget_set_halign(ScrollTextIn, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(ScrollTextOut, GTK_ALIGN_CENTER);

	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW(ScrollTextIn), TextIn);
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW(ScrollTextOut), TextOut);
/*--------------------------BUTTON------------------------------------------------------*/
	ButtonCopy = gtk_button_new_with_label ("Copy");
	ButtonRead = gtk_button_new_with_label ("Read");

	gtk_widget_set_margin_start (ButtonCopy, 5);
	gtk_widget_set_margin_end (ButtonRead, 5);

	gtk_widget_set_size_request(ButtonCopy, 120, 30);
	gtk_widget_set_size_request(ButtonRead, 120, 30);

	g_signal_connect (ButtonRead, "clicked", G_CALLBACK (callback_translate), TextWidgets);
	g_signal_connect (ButtonCopy, "clicked", G_CALLBACK (callback_copy), TextOut);
/*--------------------------BOX-WITH-BUTTON---------------------------------------------*/
	BoxButton = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

	gtk_widget_set_valign (BoxButton, GTK_ALIGN_CENTER);
	gtk_widget_set_halign (BoxButton, GTK_ALIGN_CENTER);

	gtk_box_append (GTK_BOX(BoxButton), ButtonRead);
	gtk_box_append (GTK_BOX(BoxButton), ButtonCopy);
/*--------------------------BOX---------------------------------------------------------*/
	Box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	gtk_widget_set_valign (Box, GTK_ALIGN_CENTER);
	gtk_widget_set_halign (Box, GTK_ALIGN_CENTER);

	gtk_window_set_child (GTK_WINDOW(Window), Box);

	gtk_box_append (GTK_BOX(Box), ScrollTextIn);
	gtk_box_append (GTK_BOX(Box), ScrollTextOut);
	gtk_box_append (GTK_BOX(Box), BoxButton);
/*--------------------------PRESENTATION-------------------------------------------------*/
	gtk_window_present (GTK_WINDOW(Window));
}
