#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
    CodeUnits code_units;
    FILE *in, *out;
    in = fopen(in_file_name, "r");
    out = fopen(out_file_name, "wb");
    uint32_t hex;
    int j, k = 0;
    for (j = 0; !feof(in); j++) {
        fscanf(in, "%" SCNx32, &hex);
        if (encode(hex, &code_units) == 0) {
            write_code_unit(out, &code_units);
            k++;
        }
    }
    fclose(in);
    fclose(out);
    return j == k ? 0 : -1;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
    CodeUnits code_units1;
    FILE *in, *out;
    in = fopen(in_file_name, "rb");
    remove(out_file_name);
    out = fopen(out_file_name, "a");

    while (!feof(in)){
        if ((read_next_code_unit(in, &code_units1) == 0) && (code_units1.length != 0)) {
            uint32_t dec = decode(&code_units1);
            fprintf(out, "%" PRIx32 "\n", dec);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}