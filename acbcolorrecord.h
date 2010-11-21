#ifndef __ACBCOLORRECORD_H__
#define __ACBCOLORRECORD_H__

#include "acbstring.h"

// color record stuff
#define ACB_COLOR_RECORD_CODE_SIZE	6 /* number of bytes in the color_code field */

//colorspace constants:
#define ACB_CS_RGB				0
#define	ACB_CS_CMYK				2
#define	ACB_CS_LAB				7

//colorspace constants (unimplemented by adobe? unsupported?):
#define ACB_CS_HSB				1
#define	ACB_CS_PANTONE		3
#define ACB_CS_FOCALTONE	4
#define ACB_CS_TRUMATCH		5
#define ACB_CS_TOYO				8
#define ACB_CS_GRAYSCALE	8
#define ACB_CS_HKS				10

// colorspace datasize in bytes
#define ACB_CS_RGB_SIZE		3
#define ACB_CS_CMYK_SIZE	4
#define ACB_CS_LAB_SIZE		3

typedef struct acb_color_record {
	ACB_String 	*name;
	char 				color_code[ACB_COLOR_RECORD_CODE_SIZE];
	char 				color_components[4];
}ACB_Color_Record;

void acb_free_color_record(ACB_Color_Record *r);

#endif