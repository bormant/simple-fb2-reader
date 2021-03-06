#include "body_chunks.h"

int parse_image(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	GtkTextBuffer* text_buff		= obj->text_buff;
	GHashTable* binary_hash_table	= obj->binary_hash_table;
	xmlAttr* properties				= parent_node->properties;

	parse_id_attribute(obj, parent_node, text_buff_end);

	GtkTextMark* start_tag_mark		= gtk_text_buffer_create_mark(text_buff, NULL, text_buff_end, TRUE);
	char* image_title				= NULL;
	GdkPixbuf* image				= NULL;


	while(properties != NULL)
	{
		if(properties->type == XML_ATTRIBUTE_NODE)
		{
			if(strcmp((char*)properties->name, "href") == 0)
			{
				char* image_id = (char*)(properties->children->content);
				if(*image_id == '#') // local
				{
					image_id++;

					image = g_hash_table_lookup(binary_hash_table, image_id);
					if(image == NULL)
						fprintf(stderr, _C("Image %s not found in table\n"), image_id);
				}
				else
					fputs(_C("Not local links not supported\n"), stderr);

				break;
			}
			else if(strcmp((char*)properties->name, "title") == 0)
				image_title = (char*)properties->children->content;
		}

		properties = properties->next;
	}

	if(image != NULL)
		gtk_text_buffer_insert_pixbuf(text_buff, text_buff_end, image);

	gtk_text_buffer_insert(text_buff, text_buff_end, "\n", -1);
	if(image_title != NULL)
		gtk_text_buffer_insert(text_buff, text_buff_end, image_title, -1);

	GtkTextIter start_tag_iter;
	gtk_text_buffer_get_iter_at_mark(text_buff, &start_tag_iter, start_tag_mark);
	gtk_text_buffer_delete_mark(text_buff, start_tag_mark);
	gtk_text_buffer_apply_tag_by_name(text_buff, "image_tag", &start_tag_iter, text_buff_end);

	return 0;
}
