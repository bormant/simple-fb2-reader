#include "reader_chunks.h"

int reader_close_app()
{
	GKeyFile* app_config				= GLOBAL_FB2_READER.app_config;
	char* app_config_path				= GLOBAL_FB2_READER.app_config_path;
	GtkWidget* main_wnd					= GLOBAL_FB2_READER.main_wnd;
	GtkTextBuffer* text_buff			= GLOBAL_FB2_READER.book_text_view.text_buff;
	GtkTextTagTable* text_tag_table		= gtk_text_buffer_get_tag_table(text_buff);
	GtkTextTag* default_tag				= gtk_text_tag_table_lookup(text_tag_table, "default_tag");
	//**************************************************************************************************
	GValue main_wnd_maximize = G_VALUE_INIT;
	g_value_init(&main_wnd_maximize, G_TYPE_BOOLEAN);
	g_object_get_property(G_OBJECT(main_wnd), "is-maximized", &main_wnd_maximize);
	g_key_file_set_boolean(app_config, "app",				"maximize",	g_value_get_boolean(&main_wnd_maximize));
	//**************************************************************************************************
	GValue value = G_VALUE_INIT;
	g_value_init(&value, G_TYPE_DOUBLE);
	g_object_get_property(G_OBJECT(default_tag), "scale", &value);
	double font_scale = g_value_get_double(&value);
	g_key_file_set_double(app_config, "app",				"font_scale",		font_scale);
	g_value_unset(&value);
	//**************************************************************************************************
	//g_key_file_set_string(app_config, "app",				"color_theme",		"default_theme");
	//**************************************************************************************************
	gint main_wnd_width = 0;
	gint main_wnd_height = 0;
	gtk_window_get_size(GTK_WINDOW(main_wnd), &main_wnd_width, &main_wnd_height);
	g_key_file_set_integer(app_config, "app",				"width",			main_wnd_width);
	g_key_file_set_integer(app_config, "app",				"height",			main_wnd_height);
	//**************************************************************************************************
	gint main_wnd_x_pos = 0;
	gint main_wnd_y_pos = 0;
	gtk_window_get_position(GTK_WINDOW(main_wnd), &main_wnd_x_pos, &main_wnd_y_pos);
	g_key_file_set_integer(app_config, "app",				"x_pos",			main_wnd_x_pos);
	g_key_file_set_integer(app_config, "app",				"y_pos",			main_wnd_y_pos);
	//**************************************************************************************************
	gsize app_config_len	= 0;
	char* app_config_data	= g_key_file_to_data(app_config, &app_config_len, NULL);
	//**************************************************************************************************
	FILE* f = fopen(app_config_path, "wb");
	fwrite(app_config_data, 1, app_config_len,  f);
	fclose(f);
	g_free(app_config_data);

	return 0;
}
