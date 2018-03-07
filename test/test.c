/* log4c_layout library test program */

#include <stdio.h>
#include "velayout.h"

log4c_category_t *cat_test;
log4c_category_t *cat_test_1;

int main(void)
{
	cat_test = log4c_category_get("test");
	if (NULL == cat_test) {
		fprintf(stderr, "log4c_category_get() failed.\n");
		return -1;
	}

	cat_test_1 = log4c_category_get("test1");
	if (NULL == cat_test_1) {
		fprintf(stderr, "log4c_category_get() failed.\n");
		return -1;
	}

	VE_LOG(cat_test, LOG4C_PRIORITY_NOTICE, "debug print");
	VE_LOG(cat_test_1, LOG4C_PRIORITY_NOTICE, "normal print");

	return 0;
}
