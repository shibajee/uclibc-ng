#include <string.h>
#include <features.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

char *mktemp(template)
char *template;
{
	int i;
	int num __attribute__ ((unused));	/* UNINITIALIZED */
	int n2;
	int l = strlen(template);
	struct stat stbuf;

	if (l < 6) {
		__set_errno(EINVAL);
		return 0;
	}

	for (i = l - 6; i < l; i++)
		if (template[i] != 'X') {
			__set_errno(EINVAL);
			return 0;
		}

  again:
	n2 = num;
	for (i = l - 1; i >= l - 6; i--) {
		template[i] = '0' + n2 % 10;
		n2 /= 10;
	}

	if (stat(template, &stbuf) == 0) {
		num++;
		goto again;
	}

	return template;
}
