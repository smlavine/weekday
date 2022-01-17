/**
 * weekday - Print the day of the week
 * Copyright (C) 2021 Sebastian LaVine <mail@smlavine.com>
 *
 * weekday is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * weekday is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with weekday. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void
usage(void)
{
	fputs("usage: weekday [YYYY-MM-DD]...\n", stderr);
}

int
main(int argc, char *argv[])
{
	/* No arguments provided */
	if (argc < 2) {
		usage();
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++) {
		struct tm tm;
		char *temp;
		int year, month, day;
		char linebuf[64];

		if ((temp = strtok(argv[i], "-")) == NULL) {
			goto error;
		} else {
			year = atoi(temp);
		}

		if ((temp = strtok(NULL, "-")) == NULL) {
			goto error;
		} else {
			month = atoi(temp);
		}

		if ((temp = strtok(NULL, "-")) == NULL) {
			goto error;
		} else {
			day = atoi(temp);
		}

		if (year == 0 || month == 0 || day == 0) {
error:
			fprintf(stderr, "invalid date '%s'\n", argv[i]);
			usage();
			return EXIT_FAILURE;
		}

		tm.tm_year = year - 1900; /* See ctime(3) */
		tm.tm_mon  = month - 1;   /* ^^^^^^^^^^^^ */
		tm.tm_mday = day;

		if (mktime(&tm) == (time_t)-1) {
			perror("mktime failed");
			return EXIT_FAILURE;
		}

		strftime(linebuf, sizeof(linebuf), "%F: %A", &tm);
		puts(linebuf);
	}

	return EXIT_SUCCESS;
}
