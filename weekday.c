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
#include <unistd.h>

void
usage(void)
{
	fputs("usage: weekday [YYYY-MM-DD...]\n", stderr);
}

/**
 * Prints a string of the format "YYYY-MM-DD: Weekday".
 */
void
dayofweek(struct tm *tm)
{
	char linebuf[64];
	strftime(linebuf, sizeof(linebuf), "%F: %A", tm);
	puts(linebuf);
}

/**
 * Converts a given "YYYY-MM-DD" date to a struct tm.
 */
void
datetotm(char *date, struct tm *tm)
{
	char *temp;
	int year, month, day;

	if ((temp = strtok(date, "-")) == NULL) {
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
		fprintf(stderr, "invalid date '%s'\n", date);
		usage();
		exit(EXIT_FAILURE);
	}

	tm->tm_year = year - 1900; /* See ctime(3) */
	tm->tm_mon  = month - 1;   /* ^^^^^^^^^^^^ */
	tm->tm_mday = day;

	if (mktime(tm) == (time_t)-1) {
		perror("mktime failed");
		exit(EXIT_FAILURE);
	}
}

int
main(int argc, char *argv[])
{
	int c;

	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage();
			return EXIT_SUCCESS;
		case '?':
			usage();
			return EXIT_FAILURE;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc == 0) {
		const time_t t = time(NULL);
		dayofweek(localtime(&t));
	} else {
		struct tm tm = {0};
		for (int i = 0; i < argc; i++) {
			datetotm(argv[i], &tm);
			dayofweek(&tm);
		}
	}

	return EXIT_SUCCESS;
}
