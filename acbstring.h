#ifndef __ACBSTRING_H__
#define __ACBSTRING_H__

#include <string.h>
#include "types.h"

typedef struct acb_string {
	u32 length;
	char *string; /* utf16 string */
} ACB_String;

void acb_string_to_utf8(ACB_String *string, char *buf);

#endif