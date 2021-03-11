#include <stdio.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "WARNING: This tool should be invoked by qrexec only.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Debugging Usage: %s <source-path>\n", argv[0]);
    fprintf(stderr, "Serves the file system at <source-path> via stdin/stdout" "pipes");
    return 1;
  }
}