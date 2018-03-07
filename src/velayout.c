/*
 * VE log4c layout library
 *
 * Copyright (C) 2017-2018 NEC Corporation
 * This file is part of the VE log4c layout library.
 *
 * The VE log4c layout library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either version
 * 2.1 of the License, or (at your option) any later version.
 *
 * The VE log4c layout library is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the VE log4c layout library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <log4c.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define DATE_STR_SIZE 35

static int ve_timestr(char *str, int size, int debug) {
	int ret;
	char buf[DATE_STR_SIZE];
	struct timespec ts;
	struct tm *tmp, res;

	ret = clock_gettime(CLOCK_REALTIME, &ts);
	if (ret)
		return -3;

	tmp = localtime_r(&ts.tv_sec, &res);
	if (tmp == NULL)
		return -1;

	ret = strftime(buf, DATE_STR_SIZE, "%FT%T%z", &res);
	if (ret == 0)
		return -2;

	if (debug)
		ret = snprintf(str, size, "%s.%09ld", buf, ts.tv_nsec);
	else
		ret = snprintf(str, size, "%s", buf);
	if (ret < 0)
		return -4;

	return 0;
}

const char *ve_layout(const log4c_layout_t *a_layout,
		const log4c_logging_event_t *a_event) {
	int n;
	char str[DATE_STR_SIZE];

	n = ve_timestr(str, DATE_STR_SIZE, 0);
	if (n)
		str[0] = '\0';

	n = snprintf(a_event->evt_buffer.buf_data,
			a_event->evt_buffer.buf_size,
			"%s %s %s %d %s\n",
			str,
			a_event->evt_category,
			log4c_priority_to_string(a_event->evt_priority),
			getpid(),
			a_event->evt_msg);

	return a_event->evt_buffer.buf_data;
}

const char *ve_layout_debug(const log4c_layout_t *a_layout,
		const log4c_logging_event_t *a_event) {
	int n;
	char str[DATE_STR_SIZE];

	n = ve_timestr(str, DATE_STR_SIZE, 1);
	if (n)
		str[0] = '\0';

	n = snprintf(a_event->evt_buffer.buf_data,
			a_event->evt_buffer.buf_size,
			"%s %s %s %d %d %s:%d %s\n",
			str,
			a_event->evt_category,
			log4c_priority_to_string(a_event->evt_priority),
			getpid(),
			(int)syscall(SYS_gettid),
			a_event->evt_loc->loc_file,
			a_event->evt_loc->loc_line,
			a_event->evt_msg);

	return a_event->evt_buffer.buf_data;
}

const log4c_layout_type_t ve_layout_t = {
	"ve_layout",
	ve_layout,
};

const log4c_layout_type_t ve_layout_debug_t = {
	"ve_layout_debug",
	ve_layout_debug,
};

__attribute__ ((constructor))
static void constructor(void)
{
	log4c_layout_type_set(&ve_layout_t);
	log4c_layout_type_set(&ve_layout_debug_t);
	log4c_init();
}

__attribute__ ((destructor))
static void destructor(void)
{
	log4c_fini();
}
