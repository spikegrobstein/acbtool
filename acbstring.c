#include "acbstring.h"
#include <iconv.h>

void acb_string_to_utf8(ACB_String *string, char *buf) {
	/*
	**	utf8 is a buffer that should be previously malloc'd to (string->length + 1)
	*/
	
	iconv_t cd = iconv_open("ISO-8859-1", "UTF-16");
	
	size_t outbytes = string->length;
	size_t inbytes = string->length * 2;
	
	size_t icv = iconv(cd, &string->string, &inbytes, &buf, &outbytes);
	
	iconv_close(cd);
}