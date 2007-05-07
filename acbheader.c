#include "acbheader.h"
#include "acbutils.h"
#include <string.h>

void acb_read_header(FILE *ifile, ACB_Header *header) {
	acb_read_signature(ifile, header->signature);
	
	//read the version
	header->version = acb_read_word(ifile);
	
	//read identifier
	header->identifier = acb_read_word(ifile);
	
	//read title...
	header->title = (ACB_String*)malloc(sizeof(ACB_String*));
	acb_read_title(ifile, header->title);
	char *title = (char*)malloc(header->title->length + 1);
	acb_string_to_utf8(header->title, (UTF8*)title);
	
	//read prefix...
	header->prefix = (ACB_String*)malloc(sizeof(ACB_String*));
	acb_read_prefix(ifile, header->prefix);

	//read the postfix
	header->postfix = (ACB_String*)malloc(sizeof(ACB_String*));
	acb_read_postfix(ifile, header->postfix);
	
	//read the description
	header->description = (ACB_String*)malloc(sizeof(ACB_String*));
	acb_read_description(ifile, header->description);
	
	//read the color count
	header->color_count = acb_read_color_count(ifile);
	
	//read the colors per page
	header->colors_per_page = acb_read_colors_per_page(ifile);
	
	//read the page selector offset
	header->page_selector_offset = acb_read_page_selector_offset(ifile);
	
	//read the color space identifier
	header->color_space = acb_read_color_space(ifile);
}