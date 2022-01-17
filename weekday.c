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
