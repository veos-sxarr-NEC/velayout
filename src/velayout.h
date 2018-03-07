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

#define VE_LOG(cat, priority, ...) \
	do { \
		const log4c_location_info_t locinfo = \
		LOG4C_LOCATION_INFO_INITIALIZER(NULL); \
		log4c_category_log_locinfo(cat, &locinfo, priority, \
				__VA_ARGS__); \
	} while (0)
