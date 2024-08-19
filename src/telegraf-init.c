#include "telegraf-init.h"
#include "telegraf-alphabet.h"
#include "telegraf-css.h"

void 
text_translate (const gchar *str1, gchar *str2){
	const gsize length = strlen (str1);
	str2[0] = '\0';
	for (size_t i = 0; i < length; i++) {
		if (str1[i] >= '0' && str1[i] <= '9'){
			strcat (str2, MORSE_DIGITS[str1[i] - '9']);
		} else if (str1[i] >= 'A' && str1[i] <= 'Z'){
			strcat (str2, MORSE_LETTERS[str1[i] - 'A']);
		} else if (str1[i] >= 'a' && str1[i] <= 'z'){
			strcat (str2, MORSE_LETTERS[str1[i] - 'a']);
		} else if (str1[i] == ' '){
			strcat (str2, " ");
		} else strcat (str2, "?");
		strcat (str2, " "); 
	}
}

const gchar*
get_text (GtkTextView *TextWidget){
	GtkTextBuffer *Buffer = gtk_text_view_get_buffer (TextWidget);

	GtkTextIter start, end;
	gtk_text_buffer_get_bounds (Buffer, &start, &end);

	const gchar *text = gtk_text_buffer_get_text (Buffer, &start, &end, FALSE);
	
	return text;
}

void
event_copy (GtkWidget *Widget, gpointer data) {
	GdkDisplay *Display;
	GdkClipboard *Clipboard;
	GtkTextView *TextView;

	Display = gdk_display_get_default ();

	Clipboard = gdk_display_get_clipboard (Display);

	TextView = (GtkTextView *) data;
	const gchar *text = get_text (TextView);

	gdk_clipboard_set_text (GDK_CLIPBOARD (Clipboard), text);
}

void 
event_translate (GtkWidget *Widget, gpointer data) {
	GtkTextView **TextWidgets = (GtkTextView **) data;

	GtkTextView *TextIn = TextWidgets[0];
	GtkTextView *TextOut = TextWidgets[1];

	const gchar *text_src = get_text (TextIn);

	gchar *text_translated = g_new (gchar, strlen (text_src) * 5 + 1);

	text_translate (text_src, text_translated);

	GtkTextBuffer *Buffer_out = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextOut));

	gtk_text_buffer_set_text (Buffer_out, text_translated, strlen (text_translated));
	gtk_text_view_set_buffer (TextOut, Buffer_out);
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
	gtk_window_set_title (GTK_WINDOW (Window), "Telegraf");

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

	g_signal_connect (ButtonRead, "clicked", G_CALLBACK (event_translate), TextWidgets);
	g_signal_connect (ButtonCopy, "clicked", G_CALLBACK (event_copy), TextOut);
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
