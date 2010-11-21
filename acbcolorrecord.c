#include "acbcolorrecord.h"

void acb_free_color_record(ACB_Color_Record *r) {
	free(r->name); // TODO: acb_free_string()
	free(r);
}