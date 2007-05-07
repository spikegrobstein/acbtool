#ifndef __ACBHEADER_H__
#define __ACBHEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acbstring.h"
#include "types.h"

typedef struct acb_header {
	char					signature[5];
	u16						version;
	u16						identifier;
	ACB_String		*title;
	ACB_String 		*prefix;
	ACB_String 		*postfix;
	ACB_String 		*description;
	u16						color_count;
	u16						colors_per_page;
	u16						page_selector_offset;
	u16						color_space;
}ACB_Header;

void acb_read_header(FILE *ifile, ACB_Header *header);

#endif