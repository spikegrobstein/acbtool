#ifndef __ACBCOLORRECORD_H__
#define __ACBCOLORRECORD_H__

#include "acbstring.h"

typedef struct acb_color_record {
	ACB_String 	*name;
	char 				color_code[ACB_COLOR_RECORD_CODE_SIZE];
	char 				color_components[4];
}ACB_Color_Record;

#endif