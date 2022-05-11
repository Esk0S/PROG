#include "coder.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
        printf("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
    else
        if ((strcmp(argv[1], "encode") == 0) && (argc == 4))
            encode_file(argv[2], argv[3]);
        else 
            if ((strcmp(argv[1], "decode") == 0) && (argc == 4)) 
                decode_file(argv[2], argv[3]);
            else
                printf("Usage:\ncoder encode <in-file-name> <out-file-name>\ncoder decode <in-file-name> <out-file-name>\n");
    return 0;
}

int write_code_unit(FILE *out, const CodeUnits *code_units)
{
    return fwrite(&code_units->code, 1, code_units->length, out);
}

int read_next_code_unit(FILE *in, CodeUnits *code_units)
{
    uint8_t byte;
    if (!fread(&byte, 1, 1, in))
        return -1;
    if (byte < 0x80) {
        code_units->code[0] = byte;
        code_units->length = 1;
        return 0;
    }
    int k = 0;
    if (byte >= 0xc0 && byte <= 0xdf) {
        k = 2;
        code_units->code[0] = byte;
    } else
    if (byte >= 0xe0 && byte <= 0xef) {
        k = 3;
        code_units->code[0] = byte;
    } else
    if (byte >= 0xf0 && byte <= 0xf7) {
        k = 4;
        code_units->code[0] = byte;
    } else
        return -1;
    if (k > 0) {
        for (int i = 1; i < k; i++) {
            if (!fread(&byte, 1, 1, in)) {
                return -1;
            }
            if (byte >= 0x80 && byte <= 0xbf)
                code_units->code[i] = byte;
            else {
                if (read_next_code_unit(in, code_units))
                    return -1;
            }
        }
        code_units->length = k;
        return 0;
    } 
    if (read_next_code_unit(in, code_units))
        return -1;
}

int encode(uint32_t code_point, CodeUnits *code_units)
{
    if (code_point >= 0x0 && code_point <= 0x7f) {
        code_units->code[0] = (code_point & 0x7f);
        code_units->length = 1;
    }
    if (code_point >= 0x80 && code_point <= 0x7ff) {
        code_units->code[1] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[0] = (code_point & 0x1f) | 0xc0;
        code_units->length = 2;
    }
    if (code_point >= 0x800 && code_point <= 0xffff) {
        code_units->code[2] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[1] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[0] = (code_point & 0xf) | 0xce0;
        code_units->length = 3;
    }
    if (code_point >= 0x10000 && code_point <= 0x1fffff) {
        code_units->code[3] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[2] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[1] = (code_point & 0x3f) | 0x80;
        code_point >>= 6;
        code_units->code[0] = (code_point & 0x7) | 0xf0;
        code_units->length = 4;
    }
    if (code_point > 0x1fffff)
        return -1;
    return 0;
}

uint32_t decode(const CodeUnits *code_unit)
{
    uint32_t code_point;
    switch (code_unit->length)
    {
    case 1:
        code_point = code_unit->code[0];
        code_point <<= 6;
        break;
    case 2:
        code_point = code_unit->code[0] & 0x1f;
        code_point <<= 6;
        break;
    case 3:
        code_point = code_unit->code[0] & 0xf;
        code_point <<= 6;
        break;
    case 4:
        code_point = code_unit->code[0] & 0x7;
        code_point <<= 6;
        break;
    }
    int i = 0;
    while (i < code_unit->length - 1) {
        code_point += code_unit->code[i + 1] & 0x3f;
        code_point <<= 6;
        i++;
    }
    code_point >>= 6;
    return code_point;
}