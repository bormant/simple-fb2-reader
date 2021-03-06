#include "section_chunks.h"

int parse_style(FB2_READER_BOOK_VIEW* obj, xmlNode* parent_node, GtkTextIter* text_buff_end)
{
	g_return_val_if_fail(parent_node != NULL, -1);
	g_return_val_if_fail(text_buff_end != NULL, -2);

	xmlNode* node				= parent_node->children;

	//fputs(_C("tag <style> not fully supported!\n"), stderr);
	parse_formated_text(obj, node, text_buff_end);

	return 0;
}
