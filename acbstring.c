#include "acbstring.h"
#include <iconv.h>

void acb_string_to_utf8(ACB_String *string, char *buf) {
	/*
	**	utf8 is a buffer that should be previously malloc'd to (string->length + 1)
	*/
	
	iconv_t cd = iconv_open("ISO-8859-1", "UTF-16");
	
	size_t outbytes = string->length;
	size_t inbytes = string->length;
	
	size_t icv = iconv(cd, &string->string, &inbytes, &buf, &outbytes);
	
	iconv_close(cd);
	
	
	/*
	bzero(utf8_buf, string->length + 1);
	UTF8 *utf8TargetStart = utf8_buf;
	
	UTF16 *utf16SourceStart, *utf16SourceEnd;
	utf16SourceStart = string->string;
	
	ConversionResult r = ConvertUTF16toUTF8((const UTF16**) &utf16SourceStart, &(string->string[string->length * 2]), &utf8TargetStart, &(utf8_buf[string->length * 2]), strictConversion);
	
	printf("result: %d\n", r);
	*/
}