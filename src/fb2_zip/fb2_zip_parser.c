#include "../fb2_zip/fb2_zip_chunks.h"

int parse_fb2_zip(char* file_path)
{
	FB2_READER_TEXT_VIEW* book_text_view	= &(GLOBAL_FB2_READER.book_text_view);
	GtkTextBuffer* text_buff				= book_text_view->text_buff;

	int zip_error = 0;
	struct zip* f = zip_open(file_path, ZIP_CHECKCONS, &zip_error);
	if(f != NULL)
	{
		zip_uint64_t file_count = zip_get_num_entries(f, 0);

		struct zip_stat st;
		zip_stat_init(&st);

		for(size_t i=0; i<file_count; i++)
		{
			zip_stat_index(f, i, 0,  &st);
			const char* z_file_name = st.name;
			if(test_file_type((char*)z_file_name, ".fb2") == TRUE)
			{
				struct zip_file* zf	= zip_fopen_index(f, i, 0);
				if(zf != NULL)
				{
					char buff[2048];
					zip_int64_t rc			= 0;
					xmlParserCtxtPtr ctxt	= xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL);

					while((rc = zip_fread(zf, buff, sizeof(buff))) > 0)
					{
						xmlParseChunk(ctxt, buff, rc, 0);
					}
					zip_fclose(zf);
					xmlParseChunk(ctxt, buff, 0, 1);

					xmlDocPtr xml_doc	= ctxt->myDoc;

					xmlFreeParserCtxt(ctxt);

					if(xml_doc != NULL)
					{
						xmlNode* file_tree	= xml_doc->children;
						int xml_state		= ctxt->wellFormed;

						if(xml_state)
						{
							GtkTextIter text_buff_end;
							gtk_text_buffer_get_end_iter(text_buff, &text_buff_end);

							parse_function_book(book_text_view, file_tree, &text_buff_end);
							break;
						}

						xmlFreeDoc(xml_doc);
					}
					fprintf(stderr, _C("ERROR: failed to parse fb2 file: %s\n"), st.name);
				}
				else
					fprintf(stderr, _C("ERROR: failed to unpack fb2 file: %s\n"), z_file_name);
			}
		}
		zip_close(f);
	}
	else
		fprintf(stderr, _C("ERROR: failed to open zip file: %s; error code: %d\n"), file_path, zip_error);

	return 0;
}
