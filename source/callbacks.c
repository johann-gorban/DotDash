#include "callbacks.h"

void
callback_translate  (GtkWidget *Widget , gpointer data) {
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
callback_copy   (GtkWidget *Widget, gpointer data) {
	GdkDisplay *Display;
	GdkClipboard *Clipboard;
	GtkTextView *TextView;

	Display = gdk_display_get_default ();

	Clipboard = gdk_display_get_clipboard (Display);

	TextView = (GtkTextView *) data;
	const gchar *text = get_text (TextView);

	gdk_clipboard_set_text (GDK_CLIPBOARD (Clipboard), text);
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