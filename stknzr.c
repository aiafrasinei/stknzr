#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "stknzr.h"


struct STKNZR_Context ctx;

/* copy tokens */
void copyToken(char *src, int tokenNr, int len) {
    strncpy(ctx.toks.lines[ctx.toks.nrLines].tokens[tokenNr].data, src, len);
    printf("%s\n", ctx.toks.lines[ctx.toks.nrLines].tokens[tokenNr].data);
    ctx.toks.lines[ctx.toks.nrLines].nrTokens++;
}

/* handle double quotes and whitespace separators */
void handleSeparators(char **ch, int *stringStarted) {
    if(*ch[0] == '"') {
        *stringStarted = 1;
    }

    if (*stringStarted == 0) {
        *ch = strchr(*ch, ' ');
        if (*ch != NULL) {
            *ch = *ch + 1;
        }
    } else {
        *ch = *ch + 1;
        *ch = strchr(*ch, '"');
        if (*ch != NULL) {
            if (*stringStarted) {
                *stringStarted = 0;
                *ch = *ch + 2;
            }
        }
    }
}

/* copy tokens to structure */
void handleTokens(char *line, char *ch, int *index, int prevIndex, int tokenNr, int stringStarted) {
    char *src = line + prevIndex;

    if (ch != NULL) {
        *index = (int)(ch - line);
        int len = *index - (prevIndex + 1);
        if (len > 0) {
            if (stringStarted) {
                len = len + 2;
            }
            copyToken(src, tokenNr, len);
        }
    } else {
        int len = strlen(line + *index);
        copyToken(src, tokenNr, len);
    }
}

/* tokenize line */
void handleLine(char *line) {
    if (line[0] == '\n') {
        return; // Skip empty lines
    }

    int tokenNr = 0;
    int stringStarted = 0;
    int index = 0;
    char *ch = line;

    while (ch != NULL) {
        handleSeparators(&ch, &stringStarted);
        handleTokens(line, ch, &index, index, tokenNr, stringStarted);

        tokenNr++;
    }

    ctx.toks.nrLines++;
}

/* create context */
void STKNZR_Create(const char *fileName) {
    ctx.toks.nrLines = 0;
    memset(ctx.toks.lines, 0, sizeof(ctx.toks.lines));

        
    ctx.inf = fopen(fileName, "r");
    if (ctx.inf == NULL) {
        fprintf(stderr, "%s\n", "Error opening input file\n");
        exit(EXIT_FAILURE);
    }
}

void STKNZR_Parse() {
    while((fgets(ctx.toks.lines[ctx.toks.nrLines].data, STKNZR_MAX_CHARS_PER_LINE, ctx.inf))!= NULL) {
        handleLine(ctx.toks.lines[ctx.toks.nrLines].data);
    }
}

struct STKNZR_Result *STKNZR_GetData() {
    return &ctx.toks;
}

/* destroy context */
void STKNZR_Destroy() {
    ctx.toks.nrLines = 0;
    memset(ctx.toks.lines, 0, sizeof(ctx.toks.lines));
    fclose(ctx.inf);
}
