#include "telegraf-init.h"
#include "telegraf-alphabet.h"
#include "telegraf-css.h"

void 
translate_to_code (const gchar *str1, gchar *str2){
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
			strcat (str2, "/");
		} else strcat (str2, "?");
		strcat (str2, " "); 
	}
}

void 
translate_text (GtkWidget *Widget, gpointer data) {
	GtkTextView **TextWidgets = (GtkTextView **) data;
	GtkTextView *TextIn = TextWidgets[0];
	GtkTextView *TextOut = TextWidgets[1];
	GtkTextBuffer *Buffer = gtk_text_view_get_buffer (TextIn);
	GtkTextIter start, end;
	gtk_text_buffer_get_bounds (Buffer, &start, &end);
	const gchar *text_src = gtk_text_buffer_get_text (Buffer, &start, &end, FALSE);
	gchar *text_translated = g_new (gchar, strlen (text_src) * 5 + 1);
	translate_to_code (text_src, text_translated);
	GtkTextBuffer *Buffer_out = gtk_text_view_get_buffer (GTK_TEXT_VIEW(TextOut));
	gtk_text_buffer_set_text (Buffer_out, text_translated, strlen (text_translated));
	gtk_text_view_set_buffer (TextOut, Buffer_out);
}

void 
activate_application (GtkApplication* app, gpointer user_data) {
	GtkWidget *Window;
	GtkWidget *Button;
	GtkWidget *Box;
	GtkWidget *TextIn, *TextOut;
	GtkWidget *ScrollTextIn, *ScrollTextOut;
	GtkTextView **TextWidgets = g_new (GtkTextView*, 2);
/*--------------------------WINDOW------------------------------------------------------*/
	Window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (Window), "Telegraf");
	gtk_window_set_default_size (GTK_WINDOW (Window), 350, 400);
	gtk_window_set_resizable (GTK_WINDOW (Window), FALSE);
/*--------------------------TEXTS-------------------------------------------------------*/
	TextIn = gtk_text_view_new ();
	TextOut = gtk_text_view_new ();

	gtk_widget_set_margin_bottom (TextIn, 5);
	gtk_widget_set_margin_bottom (TextOut, 3);
	
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(TextIn), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(TextOut), GTK_WRAP_WORD_CHAR);

	TextWidgets[0] = GTK_TEXT_VIEW (TextIn);
	TextWidgets[1] = GTK_TEXT_VIEW (TextOut);
/*--------------------------SCROLLED----------------------------------------------------*/
	ScrollTextIn = gtk_scrolled_window_new ();
	ScrollTextOut = gtk_scrolled_window_new ();

	gtk_widget_set_size_request (ScrollTextIn, 0, 100);

	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW(ScrollTextIn), TextIn);
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW(ScrollTextOut), TextOut);
/*--------------------------BUTTON------------------------------------------------------*/
	Button = gtk_button_new_with_label ("Read");
	gtk_widget_set_margin_top (Button, 3);

	g_signal_connect (Button, "clicked", G_CALLBACK(translate_text), TextWidgets);
/*--------------------------BOX---------------------------------------------------------*/
	Box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	gtk_box_set_homogeneous (GTK_BOX(Box), TRUE);

	gtk_widget_set_size_request (Box, 300, 150);

	gtk_widget_set_valign (Box, GTK_ALIGN_CENTER);
	gtk_widget_set_halign (Box, GTK_ALIGN_CENTER);

	gtk_window_set_child (GTK_WINDOW(Window), Box);

	gtk_box_append (GTK_BOX(Box), ScrollTextIn);
	gtk_box_append (GTK_BOX(Box), ScrollTextOut);
	gtk_box_append (GTK_BOX(Box), Button);
/*--------------------------PRESENTATION-------------------------------------------------*/
	gtk_window_present (GTK_WINDOW(Window));
}