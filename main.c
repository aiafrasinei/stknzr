#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "stknzr.h"


void logError(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

/* argument checks */
void argCheck(int argc) {
    if(argc != 2) {
        logError("Usage: stknzr [input file]\n");
    }
}

int main(int argc, char *argv[])
{
    argCheck(argc);
    
    STKNZR_Create(argv[1]);

    STKNZR_Parse();

    /*struct STKNZR_Result *result = STKNZR_GetData();
    for (int i = 0; i < result->nrLines; i++) {
        printf("Line %d: %s", result->lines[i].lineNr, result->lines[i].data);
        for (int j = 0; j < result->lines[i].nrTokens; j++) {
            printf("Token %d: %s\n", j, result->lines[i].tokens[j].data);
        }
    }*/

    STKNZR_Destroy();

    return 0;
}