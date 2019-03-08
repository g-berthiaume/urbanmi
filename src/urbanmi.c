/* ---------------------------------------------------------------------------
 * urbanmi.c 
 * A simple brainfuck[1] language interpreter.
 * 
 * USAGE:
 *  $ ./urbanmi ./myprogram.bf
 * 
 * LANGUAGE OPERATORS HELPER:
 *   >   increases memory pointer, or moves the pointer to the right 1 block.
 *   <   decreases memory pointer, or moves the pointer to the left 1 block.
 *   +   increases value stored at the block pointed to by the memory pointer
 *   -   decreases value stored at the block pointed to by the memory pointer
 *   [   like c while(cur_block_value != 0) loop.
 *   ]   if block currently pointed to's value is not zero, jump back to [
 *   ,   like c getchar(). input 1 character.
 *   .   like c putchar(). print 1 character to the console
 * 
 * 
 * [1] https://en.wikipedia.org/wiki/Brainfuck
 * 
 * ---------------------------------------------------------------------------
 * G.Berthiaume 
 * 2019
 * ---------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Brainfuck language specific definition */
#define PROGRAM_MEMORY_MAX_SIZE 30000

/* Program status */
typedef enum
{
    UMI_OK = 0,
    UMI_INVALID_ARG,
    UMI_INVALID_FILE_OPEN,
    UMI_INVALID_FILE_READ,
    UMI_MEMORY_ALLOC_ERR,
    // UMI_OUT_OF_PROGRAM_MEMORY,
    // UMI_PROGRAM_ERROR_MEM_OVERFLOW,
    // UMI_PROGRAM_ERROR_MEM_UNDERFLOW,

} umi_status;

/* Program memory */
struct program_memory
{
    char *program;      ///< Pointers to program string extracted from input file.
    size_t programSize; ///< The program string size (number of char).
};

/* Function prototypes */
umi_status load_program(const char *fileName, struct program_memory *programMemory);
size_t get_file_size(FILE *fp);

/* Program */
int main(int argc, char const *argv[])
{
    umi_status status;
    if (argc < 2)
    {
        fprintf(stderr, "Invalid usage.\nPlease use the command:­`%s yourfilename.bf`.\n", argv[0]);
        return UMI_INVALID_ARG;
    }

    struct program_memory programMemory = {0};
    status = load_program(argv[1], &programMemory);
    if (status != UMI_OK)
    {
        return status;
    }

    char appMemory[PROGRAM_MEMORY_MAX_SIZE] = {0};
    char *pAppMemory = appMemory;

    char *cursor = programMemory.program;
    while (*cursor)
    {
        char operator= *cursor;
        switch (operator)
        {
        case '>':
            pAppMemory++;
            break;
        case '<':
            pAppMemory--;
            break;
        case '+':
            (*pAppMemory)++;
            break;
        case '-':
            (*pAppMemory)--;
            break;
        case '.':
            putchar(*pAppMemory);
            break;
        case ',':
            *pAppMemory = getchar();
            break;
        case '[':
            if (*pAppMemory == 0)
            {
                /// Dont enter the loop -> go to the matching bracket
                uint16_t level = 1;
                while (level != 0)
                {
                    ++cursor; ///< Next operator
                    if (*cursor == '[')
                    {
                        level++;
                    }
                    if (*cursor == ']')
                    {
                        level--;
                    }
                }
            }
            break;
        case ']':
            if (*pAppMemory != 0)
            {
                /// loop is not finished -> go to the matching bracket
                uint16_t level = 1;
                while (level != 0)
                {
                    cursor--; ///< Previous operator
                    if (*cursor == '[')
                    {
                        level--;
                    }
                    if (*cursor == ']')
                    {
                        level++;
                    }
                }
            }
            break;
        default:
            break; ///< All other characters are ignored.
        }
        cursor++; //TODO: Better than this
    }
    return UMI_OK;
}

umi_status load_program(const char *fileName, struct program_memory *programMemory)
{
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open `%s` file.\n", fileName);
        return UMI_INVALID_FILE_OPEN;
    }

    programMemory->programSize = get_file_size(fp);

    programMemory->program = (char *)malloc(programMemory->programSize + 1);
    if (programMemory->program == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return UMI_MEMORY_ALLOC_ERR;
    }

    size_t readSize = fread(programMemory->program, sizeof(char), programMemory->programSize, fp);
    if (readSize != programMemory->programSize)
    {
        free(programMemory->program);
        fclose(fp);
        fprintf(stderr, "Error while reading file.\n");
        return UMI_INVALID_FILE_READ;
    }
    fclose(fp);
    return UMI_OK;
}

size_t get_file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);
    return size;
}