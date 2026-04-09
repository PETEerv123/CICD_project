#include "unity.h"
#include <stdio.h>

void print_banner(const char *text);

void app_main(void) {
  /*UNITY_BEGIN();

   UNITY_END();
   */
}
void print_banner(const char *text) { printf("\n### %s ###\n\n", text); }
