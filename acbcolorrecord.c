#include "acbcolorrecord.h"

void acb_free_color_record(ACB_Color_Record *r) {
	acb_free_string(r->name);
	free(r);
}