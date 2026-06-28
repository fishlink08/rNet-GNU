#ifndef DATA_TEMPLATE
#define DATA_TEMPLATE

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    intType,
    floatType,
    stringType,
    boolType
} DataType;

typedef union content {
    int32_t i;
    float f;
    char s[5000];
    bool b;
} content;

typedef struct {
    DataType type;
    content data;
} Data;

#endif