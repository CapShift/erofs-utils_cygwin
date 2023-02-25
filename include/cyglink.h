#ifndef __CYGLINK_H
#define __CYGLINK_H

#ifdef __CYGWIN__
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <fileapi.h> // win32api 

int cyglink(char* src, const char* dest) {
	int fp;
	const char* header = "!<symlink>\xff\xfe";
	fp = open(dest, O_CREAT | O_RDWR | O_TRUNC | O_BINARY);
	if (!fp) {
		fprintf(stderr, "Faild create cygwin symlink %s", src);
        return fp;
	}
    write(fp, header, 12);
	for(unsigned long i=0;i<strlen(src);i++) {
		write(fp, &src[i], 1); write(fp, "\0", 1);
	}
    write(fp, 0, 1); write(fp, 0, 1);
	close(fp);
    chmod(dest, 0777);
    SetFileAttributesA(dest, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_SYSTEM);
    return 0;
}
#endif // __CYGWIN__
#endif // __CYGLINK_H
