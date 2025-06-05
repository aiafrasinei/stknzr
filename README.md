# stknzr

Simple tokenizer for text files in C. It reads a file line by line, splits each line into tokens (words or quoted strings), and stores the results in a structured format.

- **STKNZR_Create**: Opens the input file and initializes the tokenizer context.
- **STKNZR_Parse**: Reads each line from the file, tokenizes it, and stores tokens in a result structure.
- **STKNZR_GetData**: Returns a pointer to the structure holding all parsed lines and tokens.
- **STKNZR_Destroy**: Cleans up by closing the file and resetting the context.

The code uses fixed-size arrays for lines and tokens.
