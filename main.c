#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "acbutils.h"
#include "acbheader.h"
#include "acbcolorrecord.h"
#include "errors.h"

// options that are common between all actions
#define COMMON_OPTIONS		{ "verbose", no_argument, NULL, 'v' }, \
													{ "hex", no_argument, NULL, 'x' }, \
													{ "suppress-headers", no_argument, NULL, 'S' }, \
													{ "quiet", no_argument, NULL, 'q' }

void print_usage();
void dump_action(int argc, char **argv);
void get_action(int argc, char **argv);

char *executable_name = NULL; // the name of the executable

// global commandline flags
int verbosity = 0; // verbosity level
int quiet = 0;
int suppress_headers = 0;
int hex_output = 0;

int main(int argc, char **argv) {
	char *action = NULL;
	
	// fetch the executable name (global var)
	executable_name = *argv++;
	argc--;
	
	// check minimum arguments
	if (argc < 1) {
		print_usage();
	}
	
	action = *argv;
	
	// we don't shift argc or argv when reading the action because getopt
	// expects argv[0] to be the executable name. right now, it's the action.

	printf("Action: %s\n", action);

	if (strcmp(action, "help") == 0) {
		printf("helping you...\n");
		exit(EXIT_SUCCESS);
	} else if (strcmp(action, "dump") == 0) {
		dump_action(argc, argv);
	} else if (strcmp(action, "get") == 0) {
		get_action(argc, argv); 
	} else {
		printf("unknown action: %s\n", action);
		print_usage();
		exit(EXIT_SUCCESS);
	}
	
	exit(EXIT_SUCCESS);
}

void print_usage() {
	printf("USAGE!\n");
	printf("%s <action> [options] <filename>\n", executable_name);
	
	exit(EXIT_SUCCESS);
}

#pragma mark -
#pragma mark ****ACTIONS****

void dump_action(int argc, char **argv) {
	// flags:
	int header_only = 0;
	
	// getopt stuff:
	static struct option longopts[] = {
		COMMON_OPTIONS,
		{ "header-only", no_argument, NULL, 'h' },
		{ NULL, 0, NULL, 0 }
	};
	
	int ch; // getopt handle
	int ind; // getopt index
	
	while ((ch = getopt_long(argc, argv, "vxSqh", longopts, &ind)) != -1) {
		switch (ch) {
			case 'v':
				verbosity++;
				break;
				
			case 'x':
				hex_output++;
				break;
				
			case 'S':
				suppress_headers++;
				break;
				
			case 'q':
				quiet++;
				break;
				
			case 'h':
				header_only++;
				break;
				
			default:
				printf("Unknown option!\n");
				exit(EXIT_ERROR_CLI);
		}
	}
	
	argc -= optind;
	argv += optind;
	
	// now, process the files!
	
	char *filename = argv[0];
	
	if (!filename) {
		// the filename was blank
		printf("No filename provided!\n");
		exit(EXIT_ERROR_NO_IFILE);
	}

	printf("Opening %s\n", filename);

	FILE *ifile = NULL;
	
	if (!(ifile = fopen(filename, "r"))) {
		perror(filename);
		exit(EXIT_ERROR_IFILE);
	}
		
	ACB_Header *header = (ACB_Header*)malloc(sizeof(ACB_Header));
	
	acb_read_header(ifile, header);
	
	char *title = (char*)malloc(header->title->length * sizeof(char) + 1);
	acb_string_to_string(header->title, title);
		
	char *prefix = (char*)malloc(header->prefix->length * sizeof(char) + 1);
	acb_string_to_string(header->prefix, prefix);
	
	char *postfix = (char*)malloc(header->postfix->length * sizeof(char) + 1);
	acb_string_to_string(header->postfix, postfix);

	char *description = (char*)malloc(header->description->length * sizeof(char) + 1);
	acb_string_to_string(header->description, description);
	
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
	
	if (!header_only) {
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
			acb_string_to_string(r->name, color_name);

			printf(color_format_line, color_name, r->color_code, "", "");

			free(color_name);
			//free(r->name->string); // FIXME: memory leak. no idea why, but this should work, but it complains about not being malloc()'d
			free(r->name);
			free(r);
		}
	}
	
	fclose(ifile);
}

// handler for "get" action
void get_action(int argc, char **argv) {
	// flags:
	int get_title = 0;
	int get_prefix = 0;
	int get_postfix = 0;
	int get_description = 0;
	int get_version = 0;
	int get_identifier = 0;
	int get_colors_per_page = 0;
	int get_page_selector_offset = 0;
	int get_color_space = 0;
	int get_color_count = 0;
	
	// getopt stuff:
	static struct option longopts[] = {
		COMMON_OPTIONS,
		{ "title", no_argument, NULL, 't' },
		{ "prefix", no_argument, NULL, 'e' },
		{ "postfix", no_argument, NULL, 'X' },
		{ "description", no_argument, NULL, 'd' },
		{ "version", no_argument, NULL, 'r' },
		{ "identifier", no_argument, NULL, 'i' },
		{ "colors-per-page", no_argument, NULL, 'p' },
		{ "page-selector-offset", no_argument, NULL, 'o' },
		{ "color-space", no_argument, NULL, 's' },
		{ "color-count", no_argument, NULL, 'c' },
		{ NULL, 0, NULL, 0 }
	};
	
	int ch; // getopt handle
	int ind; // getopt index
	
	while ((ch = getopt_long(argc, argv, "vxSqteXdriposc", longopts, &ind)) != -1) {
		switch (ch) {
			case 'v':
				verbosity++;
				break;
				
			case 'x':
				hex_output++;
				break;
				
			case 'S':
				suppress_headers++;
				break;
				
			case 'q':
				quiet++;
				break;
				
			case 't':
				get_title++;
				break;
				
			case 'e':
				get_prefix++;
				break;
			
			case 'X':
				get_postfix++;
				break;
				
			case 'd':
				get_description++;
				break;
				
			case 'r':
				get_version++;
				break;
			
			case 'i':
				get_identifier++;
				break;
			
			case 'p':
				get_colors_per_page++;
				break;
			
			case 'o':
				get_page_selector_offset++;
				break;
			
			case 's':
				get_color_space++;
				break;
				
			case 'c':
				get_color_count++;
				break;
			
			default:
				printf("Unknown option!\n");
				exit(EXIT_ERROR_CLI);
		}
	}
	
	argc -= optind;
	argv += optind;
	
	// now, process the files!
	
	char *filename = argv[0];
	
	if (!filename) {
		// the filename was blank
		printf("No filename provided!\n");
		exit(EXIT_ERROR_NO_IFILE);
	}

	printf("Opening %s\n", filename);

	FILE *ifile = NULL;
	
	if (!(ifile = fopen(filename, "r"))) {
		perror(filename);
		exit(EXIT_ERROR_IFILE);
	}
	
	// read the header
	ACB_Header *header = (ACB_Header*)malloc(sizeof(ACB_Header));
	acb_read_header(ifile, header);
	
	if (get_title) {
		char *title = (char*)malloc(header->title->length * sizeof(char) + 1);
		acb_string_to_string(header->title, title);
		
		if (!suppress_headers) { printf("Title: "); }
		printf("%s\n", title);
		
		free(title);
		free(header->title);
	}
	
	if (get_prefix) {
		char *prefix = (char*)malloc(header->prefix->length * sizeof(char) + 1);
		acb_string_to_string(header->prefix, prefix);
		
		if (!suppress_headers) { printf("Prefix: "); }
		printf("%s\n", prefix);
		
		free(prefix);
		free(header->title);
	}
	

	


	/*
	char *postfix = (char*)malloc(header->postfix->length * sizeof(char) + 1);
	acb_string_to_string(header->postfix, postfix);

	char *description = (char*)malloc(header->description->length * sizeof(char) + 1);
	acb_string_to_string(header->description, description);
	
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
	*/
	
}