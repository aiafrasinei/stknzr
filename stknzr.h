#pragma once

#include <stdio.h>


#define STKNZR_MAX_CHARS_PER_TOKEN 80
#define STKNZR_MAX_CHARS_PER_LINE 80
#define STKNZR_MAX_TOKENS_PER_LINE 80
#define STKNZR_MAX_LINES 1024

struct STKNZR_Token {
    char data[STKNZR_MAX_CHARS_PER_TOKEN];
};

struct STKNZR_Line {
    char data[STKNZR_MAX_CHARS_PER_LINE];
    struct STKNZR_Token tokens[STKNZR_MAX_TOKENS_PER_LINE];
    int lineNr;
    int nrTokens;
};

struct STKNZR_Result {
    struct STKNZR_Line lines[STKNZR_MAX_LINES];
    int nrLines;
};

struct STKNZR_Context {
    FILE *inf;
    struct STKNZR_Result toks;
};


void STKNZR_Create(const char *fileName);

void STKNZR_Parse();

struct STKNZR_Result *STKNZR_GetData();

void STKNZR_Destroy();
