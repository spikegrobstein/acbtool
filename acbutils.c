#include "acbutils.h"
#include "ConvertUTF.h"

void acb_read_string(FILE *ifile, ACB_String *string) {
	//first, let's get the length...
	string->length = acb_read_long(ifile);
		
	if (string->length == 0) return; //error

	// allocate size of string + 1 * sizeof(UTF16)
	string->string = (char*)malloc(string->length * sizeof(UTF16) + 1);
		
	if (fread(string->string, sizeof(UTF16), string->length, ifile) != string->length) {
		printf("error: acb_read_string- reading string\n");
		return;
	}
}

u16 acb_read_word(FILE *ifile) {
	if (!ifile || ifile == NULL) return 0;
	
	u16 *s = (u16*)malloc(sizeof(u16));
	
	if (fread(s, 1, sizeof(u16), ifile) != sizeof(u16)) {
		free(s);
		printf("error reading word....\n");
		return 0;
	}
	
	u16 val = *s;
	free(s);
	return ntohs(val);
}

u32 acb_read_long(FILE *ifile) {
	if (!ifile || ifile == NULL) return 0;
		
	u32 *l = (u32*)malloc(sizeof(u32));
	if (fread(l, 1, sizeof(u32), ifile) != sizeof(u32)) {
		free(l);
		printf("error: acb_read_long\n");
		return 0;
	}
	
	u32 val = *l;
	free(l);
		
	return ntohl(val);
}

//headerstuff
void acb_read_signature(FILE *ifile, char *signature) {
	/*
	**	sets signature to the file's signature (should be "8BCB")
	**	signature must be of size (ACB_SIGNATURE_LENGTH + 1)
	*/
	
	acb_seek_to_signature(ifile);
	if (fread(signature, 1, ACB_SIGNATURE_LENGTH, ifile) != ACB_SIGNATURE_LENGTH) {
		perror("acb_read_signature");
		exit(1);
	}
}

u16 acb_read_version(FILE *ifile) {
	acb_seek_to_version(ifile);
	return acb_read_word(ifile);
}

u16 acb_read_identifier(FILE *ifile) {
	acb_seek_to_identifier(ifile);
	return acb_read_word(ifile);
}

void acb_read_title(FILE *ifile, ACB_String *title) {
	acb_seek_to_title(ifile);
	acb_read_string(ifile, title);
}

void acb_read_prefix(FILE *ifile, ACB_String *prefix) {
	acb_seek_to_prefix(ifile);
	acb_read_string(ifile, prefix);
}

void acb_read_postfix(FILE *ifile, ACB_String *postfix) {
	acb_seek_to_postfix(ifile);
	acb_read_string(ifile, postfix);
}

void acb_read_description(FILE *ifile, ACB_String *description) {
	acb_seek_to_description(ifile);
	acb_read_string(ifile, description);
}

u16 acb_read_color_count(FILE *ifile) {
	acb_seek_to_color_count(ifile);
	return acb_read_word(ifile);
}

u16 acb_read_colors_per_page(FILE *ifile) {
	acb_seek_to_colors_per_page(ifile);
	return acb_read_word(ifile);
}

u16 acb_read_page_selector_offset(FILE *ifile) {
	acb_seek_to_page_selector_offset(ifile);
	return acb_read_word(ifile);
}

u16 acb_read_color_space(FILE *ifile) {
	acb_seek_to_color_space(ifile);
	return acb_read_word(ifile);
}

//offset stuff
void acb_seek_to_signature(FILE *ifile) {
	fseek(ifile, ACB_SIGNATURE_OFFSET, SEEK_SET);
}

void acb_seek_to_version(FILE *ifile) {
	fseek(ifile, ACB_VERSION_OFFSET, SEEK_SET);
}

void acb_seek_to_identifier(FILE *ifile) {
	fseek(ifile, ACB_IDENTIFIER_OFFSET, SEEK_SET);
}

void acb_seek_to_title(FILE *ifile) {
	fseek(ifile, ACB_TITLE_OFFSET, SEEK_SET);
}

void acb_seek_to_prefix(FILE *ifile) {
	acb_seek_to_title(ifile);
	fseek(ifile, acb_read_long(ifile) * 2, SEEK_CUR); 	//skip over the title
}

void acb_seek_to_postfix(FILE *ifile) {
	acb_seek_to_prefix(ifile);
	fseek(ifile, acb_read_long(ifile) * 2, SEEK_CUR); 	//skip over the prefix
}

void acb_seek_to_description(FILE *ifile) {
	acb_seek_to_postfix(ifile);
	fseek(ifile, acb_read_long(ifile) * 2, SEEK_CUR); 	//skip over the postfix
}

void acb_seek_to_color_count(FILE *ifile) {
	acb_seek_to_description(ifile);
	fseek(ifile, acb_read_long(ifile) * 2, SEEK_CUR); 	//skip over the description
}

void acb_seek_to_colors_per_page(FILE *ifile) {
	acb_seek_to_color_count(ifile);
	fseek(ifile, 2, SEEK_CUR);							//skip over the color_count
}

void acb_seek_to_page_selector_offset(FILE *ifile) {
	acb_seek_to_colors_per_page(ifile);
	fseek(ifile, 2, SEEK_CUR);							//skip over the colors_per_page
}

void acb_seek_to_color_space(FILE *ifile) {
	acb_seek_to_page_selector_offset(ifile);
	fseek(ifile, 2, SEEK_CUR);							//skip over the page_selector_offset
}

void acb_seek_to_first_color_record(FILE *ifile) {
	acb_seek_to_color_space(ifile);
	fseek(ifile, 2, SEEK_CUR);							//skip over the color_space
}

void acb_read_next_color_record(FILE *ifile, ACB_Color_Record *record, int mode) {
	/*
	**	assumes that record has been allocated and configured... (name is configured, too)
	**	also assumes that ifile's current position is aligned to a record
	*/
	
	acb_read_string(ifile, record->name);
	
	if (fread(record->color_code, 1, 6, ifile) != 6) {
		printf("error next_color_record\n");
		exit(1);
	}
	
//	switch (mode) {
//		case ACB_C
//	}
}
