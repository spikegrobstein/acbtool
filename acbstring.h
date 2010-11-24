#ifndef __ACBSTRING_H__
#define __ACBSTRING_H__

#include <string.h>
#include "types.h"

typedef struct acb_string {
	u32 length;
	char *string; /* utf16 string */
} ACB_String;

void acb_string_to_string(ACB_String *string, char *buf);
void acb_free_string(ACB_String *s);

#endif