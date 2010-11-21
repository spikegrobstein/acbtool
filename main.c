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
		
	char *prefix = (char*)malloc(header->prefix->length * sizeof(char) + 1);
	acb_string_to_utf8(header->prefix, prefix);
	
	char *postfix = (char*)malloc(header->postfix->length * sizeof(char) + 1);
	acb_string_to_utf8(header->postfix, postfix);

	char *description = (char*)malloc(header->description->length * sizeof(char) + 1);
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
	
	acb_seek_to_first_color_record(ifile);
	
	char *color_format_line = "%-40s %-14s %-7s %-5s\n";
	
	printf(color_format_line, "Name", "Code", "Mode", "Components");
	
	for (i = 0; i < header->color_count; i++) {
		r = (ACB_Color_Record*)malloc(sizeof(ACB_Color_Record));
		
		acb_read_next_color_record(ifile, r, 0);
		
		char *color_name = (char*)malloc(r->name->length * sizeof(char) + 1);
		acb_string_to_utf8(r->name, color_name);
		
		printf(color_format_line, color_name, r->color_code, "", "");
			
		free(r);
	}
	
	fclose(ifile);
}
