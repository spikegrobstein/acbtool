#ifndef __ACBUTILS_H__
#define __ACBUTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acbcolorrecord.h"
#include "acbstring.h"
#include "types.h"

//constants:
#define WORD_LENGTH							0x02	/*	u16	*/
#define LONGWORD_LENGTH					0x04	/*	u32	*/
#define CHAR_LENGTH							0x02	/*	bytes per character */

#define ACB_SIGNATURE_OFFSET  	0x00
#define ACB_SIGNATURE_LENGTH		0x04

#define ACB_VERSION_OFFSET			0x04
#define ACB_VERSION_LENGTH			WORD_LENGTH

#define ACB_IDENTIFIER_OFFSET		0x06
#define ACB_IDENTIFIER_LENGTH		WORD_LENGTH

#define ACB_TITLE_OFFSET				0x08

//supported values:
#define ACB_SIGNATURE 			"8BCB"
#define ACB_VERSION					0x0001

// other color spaces are not defined? who knows what size they should be.

typedef struct acb_record {
	char *nothing;
} ACB_Record;

void acb_read_string(FILE *ifile, ACB_String *string);
u16 acb_read_word(FILE *ifile);
u32 acb_read_long(FILE *ifile);

//reading headerstuff
void acb_read_signature(FILE *ifile, char *signature);
u16 acb_read_version(FILE *ifile);
u16 acb_read_identifier(FILE *ifile);
void acb_read_title(FILE *ifile, ACB_String *title);
void acb_read_prefix(FILE *ifile, ACB_String *prefix);
void acb_read_postfix(FILE *ifile, ACB_String *postfix);
void acb_read_description(FILE *ifile, ACB_String *description);
u16 acb_read_color_count(FILE *ifile);
u16 acb_read_colors_per_page(FILE *ifile);
u16 acb_read_page_selector_offset(FILE *ifile);
u16 acb_read_color_space(FILE *ifile);

//seeking header stuff
void acb_seek_to_signature(FILE *ifile);
void acb_seek_to_version(FILE *ifile);
void acb_seek_to_identifier(FILE *ifile);
void acb_seek_to_title(FILE *ifile);
void acb_seek_to_prefix(FILE *ifile);
void acb_seek_to_postfix(FILE *ifile);
void acb_seek_to_description(FILE *ifile);
void acb_seek_to_color_count(FILE *ifile);
void acb_seek_to_colors_per_page(FILE *ifile);
void acb_seek_to_page_selector_offset(FILE *ifile);
void acb_seek_to_color_space(FILE *ifile);
void acb_seek_to_first_color_record(FILE *ifile);

//color records...
void acb_read_next_color_record(FILE *ifile, ACB_Color_Record *record, int mode);

int acb_read_color_data(FILE *ifile, char *buf, int mode);

#endif