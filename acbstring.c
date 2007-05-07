#include "acbstring.h"

void acb_string_to_utf8(ACB_String *string, UTF8 *utf8_buf) {
	/*
	**	utf8 is a buffer that should be previously malloc'd to (string->length + 1)
	*/
	
	bzero(utf8_buf, string->length + 1);
	UTF8 *utf8TargetStart = utf8_buf;
	
	UTF16 *utf16SourceStart, *utf16SourceEnd;
	utf16SourceStart = string->string;
	
	ConversionResult r = ConvertUTF16toUTF8((const UTF16**) &utf16SourceStart, &(string->string[string->length]), &utf8TargetStart, &(utf8_buf[string->length]), strictConversion);
}