#include "../chunks.h"

int init_main_wnd(GtkBuilder* builder, FB2_READER* obj)
{
	memset(obj, 0, sizeof(*obj));

	create_config_dir();
	init_app_config(obj);
	init_main_reader_book_view(builder, obj);


	obj->main_wnd						= GTK_WIDGET(				gtk_builder_get_object(builder, "main_wnd"));
	obj->filechooserdialog				= GTK_FILE_CHOOSER_DIALOG(	gtk_builder_get_object(builder, "book_filechooserdialog"));
	obj->navigation_dialog				= GTK_DIALOG(				gtk_builder_get_object(builder, "navigation_dialog"));
	obj->about_dialog					= GTK_ABOUT_DIALOG(			gtk_builder_get_object(builder, "reader_aboutdialog"));
	obj->sections_treeview				= GTK_TREE_VIEW(			gtk_builder_get_object(builder, "books_section_treeview"));
	obj->forget_books_dialog			= GTK_MESSAGE_DIALOG(		gtk_builder_get_object(builder, "forget_all_books_message_dialog"));


	assert(obj->main_wnd				!= NULL);
	assert(obj->filechooserdialog		!= NULL);
	assert(obj->navigation_dialog		!= NULL);
	assert(obj->about_dialog			!= NULL);
	assert(obj->sections_treeview		!= NULL);
	assert(obj->forget_books_dialog		!= NULL);


	gtk_about_dialog_set_version(obj->about_dialog, PACKAGE_VERSION);

	const char* conf_dir				= g_get_user_config_dir();
	assert(conf_dir != NULL);

	char* color_theme = g_key_file_get_string(obj->app_config, "app", "color_theme", NULL);
	reader_set_color_theme(obj, (const char*)color_theme);
	g_free(color_theme);

	gint main_wnd_x_pos = g_key_file_get_integer(obj->app_config, "app", "x_pos", NULL);
	gint main_wnd_y_pos = g_key_file_get_integer(obj->app_config, "app", "y_pos", NULL);
	gtk_window_move(GTK_WINDOW(obj->main_wnd), main_wnd_x_pos, main_wnd_y_pos);

	gint main_wnd_width = g_key_file_get_integer(obj->app_config, "app", "width", NULL);
	gint main_wnd_height = g_key_file_get_integer(obj->app_config, "app", "height", NULL);
	gtk_window_resize(GTK_WINDOW(obj->main_wnd), main_wnd_width, main_wnd_height);


	if(g_key_file_get_boolean(obj->app_config, "app", "maximize", NULL) == TRUE)
		gtk_window_maximize(GTK_WINDOW(obj->main_wnd));

	//create_fb2_tags(obj->text_buff);

	obj->cursor_link				= gdk_cursor_new(GDK_HAND2);
	obj->cursor_watch				= gdk_cursor_new(GDK_WATCH);
	obj->clipboard					= gtk_clipboard_get(0);

	gtk_widget_show_all(obj->main_wnd);

	return 0;
}

