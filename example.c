#include <stdbool.h>
#include <stdio.h>
#include "./flag.h"

int main(int argc, char **argv) {
    bool b;
    char s[100];
    int i;
    flag_bool(&b, "x", "some boolean param");
    flag_string(s, "s", "some string param");
    flag_int(&i, "i", "some int param");
    parse(argc, argv);
    
    printf("bool: %s\n", b ? "true" : "false");
    printf("string: %s\n", s);
    printf("int: %d\n", i);
    return 0;
}
