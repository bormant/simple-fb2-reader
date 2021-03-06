#include "callbacks_chunk.h"

void search_wnd_close_button_clicked_cb(GtkButton* widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
}

gboolean search_wnd_key_press_event_cb(GtkWidget* widget, GdkEvent* event, gpointer user_data)
{
	GdkEventKey key_event = event->key;
	if(key_event.keyval == GDK_KEY_Escape)
		gtk_widget_hide(widget);
	else if(key_event.keyval == GDK_KEY_Return)
	{
		//search_wnd_search_button_clicked_cb(NULL, NULL);
		// TODO следующая позиция поиска по enter
	}

	return FALSE;
}


void search_wnd_search_button_clicked_cb(GtkButton* button, gpointer user_data)
{
	GtkTextBuffer* text_buff		= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextView* text_view			= GLOBAL_FB2_READER.book_text_view.text_view;
	GtkTextIter* last_search_pos	= GLOBAL_SEARCH_WND.last_pos;
	GtkCheckButton* case_sensitive	= GLOBAL_SEARCH_WND.case_sensitive;
	GtkRadioButton* backward		= GLOBAL_SEARCH_WND.backward;
	GtkRadioButton* forward			= GLOBAL_SEARCH_WND.forward;

	const char* query = gtk_entry_get_text(GTK_ENTRY(user_data));

	GtkTextIter text_buff_match_start_iter;
	GtkTextIter text_buff_match_end_iter;

	gboolean search_success = FALSE;
	GtkTextSearchFlags case_sensitive_flag;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(case_sensitive)) == TRUE)
		case_sensitive_flag = GTK_TEXT_SEARCH_VISIBLE_ONLY;
	else
		case_sensitive_flag = GTK_TEXT_SEARCH_CASE_INSENSITIVE;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(forward)) == TRUE)
		search_success = gtk_text_iter_forward_search(last_search_pos, query, case_sensitive_flag, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(backward)) == TRUE)
		search_success = gtk_text_iter_backward_search(last_search_pos, query, case_sensitive_flag, &text_buff_match_start_iter, &text_buff_match_end_iter, NULL);

	if(search_success == TRUE)
	{
		gtk_text_buffer_select_range(text_buff, &text_buff_match_start_iter, &text_buff_match_end_iter);

		gtk_text_view_scroll_to_iter(text_view, &text_buff_match_start_iter, 0.f, TRUE, 0.f, 0.5f);

		//*last_search_pos = text_buff_match_end_iter;

		gtk_text_iter_free(last_search_pos);

		GLOBAL_SEARCH_WND.last_pos = gtk_text_iter_copy(&text_buff_match_end_iter);
	}
	else
		gtk_text_buffer_get_start_iter(text_buff, last_search_pos);
}


void search_query_changed_cb(GtkEditable* editable, gpointer user_data)
{
	GtkTextBuffer* text_buff		= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextIter* last_search_pos	= GLOBAL_SEARCH_WND.last_pos;
	gtk_text_buffer_get_start_iter(text_buff, last_search_pos);
}

