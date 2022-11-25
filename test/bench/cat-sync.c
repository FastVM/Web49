#define _DEFAULT_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>

static bool simple_cat(char *const buf, size_t bufsize) {
  while (true) {
    const ssize_t nread = read(STDIN_FILENO, buf, bufsize);
    if (nread == -1) {
      return false;
    }
    if (nread == 0) {
      return true;
    }
    const ssize_t nwrite = write(STDOUT_FILENO, buf, bufsize);
    if (nwrite != nread) {
      return false;
    }
  }
}

int main(int argc, char *argv[]) {
  struct stat stat_buf;
  if (fstat(STDOUT_FILENO, &stat_buf) != 0) {
    fputs(strerror(errno), stderr);
    return EXIT_FAILURE;
  }
  const size_t outsize = MAX(128 * 1024, stat_buf.st_blksize);
  if (fstat(STDIN_FILENO, &stat_buf) != 0) {
    fputs(strerror(errno), stderr);
    return EXIT_FAILURE;
  }
  const size_t insize = MAX(128 * 1024, stat_buf.st_blksize);

  posix_fadvise(STDIN_FILENO, 0, 0, POSIX_FADV_SEQUENTIAL);
  const size_t page_size = sysconf(_SC_PAGE_SIZE);
  const size_t bufsize = MAX(insize, outsize);
  char *buf;
  if (posix_memalign((void **)&buf, page_size, bufsize) != 0) {
    fputs(strerror(errno), stderr);
    return EXIT_FAILURE;
  }

  const bool result = simple_cat(buf, bufsize);

  free(buf);

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
