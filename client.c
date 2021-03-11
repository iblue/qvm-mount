#include <stdio.h>

int main(int argc, char **argv) {
  fprintf(stderr, "WARNING: This tool should be invoked by qrexec only.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "Debugging Usage: %s <target-path>\n", argv[0]);
  fprintf(stderr, "Mounts the file system received via stdin/stdout pipes to <target-path>");
  return 1;
}