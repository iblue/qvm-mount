#include <stdio.h>

int main(int argc, char **argv) {
  fprintf(stderr, "WARNING: This tool should be invoked by qrexec only.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "Debugging Usage: %s <path>\n", argv[0]);
  return 1;
}