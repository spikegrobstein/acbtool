#include <stdio.h>
#include <stdlib.h>

#include "acbutils.h"
#include "acbheader.h"
#include "acbcolorrecord.h"

int main(int argc, char **argv) {
	char *filename = argv[1];

	printf("Opening %s\n", filename);

	FILE *ifile = NULL;
	
	if (!(ifile = fopen(filename, "r"))) {
		perror(filename);
		exit(1);
	}
		
	ACB_Header *header = (ACB_Header*)malloc(sizeof(ACB_Header));
	
	acb_read_header(ifile, header);
	
	char *title = (char*)malloc(header->title->length * sizeof(char) + 1);
	acb_string_to_utf8(header->title, title);
		
	UTF8 *prefix = (UTF8*)malloc(header->prefix->length * sizeof(UTF8) + 1);
	acb_string_to_utf8(header->prefix, prefix);
	
	UTF8 *postfix = (UTF8*)malloc(header->postfix->length * sizeof(UTF8) + 1);
	acb_string_to_utf8(header->postfix, postfix);

	UTF8 *description = (UTF8*)malloc(header->description->length * sizeof(UTF8) + 1);
	acb_string_to_utf8(header->description, description);
	
	printf("signature:            %s\n", header->signature);
	printf("version:              0x%04X\n", header->version);
	printf("identifier:           0x%04X\n", header->identifier);
	printf("title:                %s\n", title);
	printf("prefix:               %s\n", prefix);
	printf("postfix:              %s\n", postfix);
	printf("description:          %s\n", description);
	printf("color count:          %d\n", header->color_count);
	printf("colors per page:      %d\n", header->colors_per_page);
	printf("page selector offset: %d\n", header->page_selector_offset);
	printf("color space:          %d\n", header->color_space);
	
	//ok, let's experiment with reading color records...
	int i = 0;
	ACB_Color_Record *r = NULL;
	
	for (i = 0; i < header->color_count; i++) {
		r = (ACB_Color_Record*)malloc(sizeof(ACB_Color_Record));
		
		r->name = (ACB_String*)malloc(sizeof(ACB_String));
		
		free(r);
	}
	
	fclose(ifile);
}
