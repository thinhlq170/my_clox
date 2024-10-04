#include <stdio.h>

#include "../inc/debug.h"
#include "../inc/value.h"

void disassembleChunk(Chunk *chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int constantInstruction(const char* name, Chunk *chunk, int offset) {
    uint8_t constant_index = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant_index);
    printValue(chunk->constants.values[constant_index]);
    printf("'\n");
    // OP_CONSTANT is a 2-byte instruction, one for the opcode and one for the operand
    // example instruction 'print 1;'
    return offset + 2;
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("    | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }
    
    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);

        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
