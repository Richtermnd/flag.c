#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FLAGS 25
#define MAX_LEN_NAME 100

enum FLAG_TYPE {
    FLAG_BOOL,
    FLAG_STRING,
    FLAG_INT
};


typedef struct {
    enum FLAG_TYPE type;
    void *dst;
    char *name;
    char *usage;
} flag;

int c_flags = 0; // flags counter
// I don't use *flag cuz it stores only a type and other pointers
flag flags[MAX_FLAGS];  // TODO: Use hasmap or binary tree or something else with faster than O(n) search.
char *desc;

void _flag(enum FLAG_TYPE t, void *dst, char *name, char *usage) {
    if (c_flags >= MAX_FLAGS) {
        fprintf(stderr, "too many flags\n");
        exit(1);
    }
    flag f = {t, dst, name, usage};
    flags[c_flags++] = f;
}

flag *find(char *name) {
    for (int i = 0; i < c_flags; ++i) {
        if (strcmp(flags[i].name, name) == 0)
            return &flags[i];
    }
    return NULL;
}

void flag_bool(bool *dst, char *name, char *usage) {
    _flag(FLAG_BOOL, dst, name, usage);
}

void flag_string(char *dst, char *name, char *usage) {
    _flag(FLAG_STRING, dst, name, usage);
}

void flag_int(int *dst, char *name, char *usage) {
    _flag(FLAG_INT, dst, name, usage);
}


char *trim_dash(char *s) {
    while (*s == '-')
        s++;
    return s;
}

void print_help() {
    printf("%s\n", desc);
    for (int i = 0; i < c_flags; ++i) {
        printf("\t%-20s - %s\n", flags[i].name, flags[i].usage);
    }
}

void parse(int argc, char **argv) {
    while (--argc) { // prefix decr to skip filename
        char *arg = *++argv;
        if (arg[0] != '-') {
            continue;
        }
        arg = trim_dash(arg);
        if (strcmp(arg, "h") == 0 || strcmp(arg, "help") == 0) {
            print_help();
            exit(0);
        }
        flag *f = find(arg);
        if (f == NULL) {
            fprintf(stderr, "unknown option: %s\n", arg);
            exit(1);
        }

        switch (f->type) {
            case FLAG_BOOL: {
                bool *temp = (bool *)f->dst;
                *temp = true;
                break;
            }
            case FLAG_INT: {
                int *temp = (int *)f->dst;
                *temp = atoi(*++argv);
                argc--;
                break;
            }
            case FLAG_STRING: {
                char *temp = (char *)f->dst;
                temp = strcpy(temp, *++argv);
                argc--;
                break;
            }
        }
    }
}

