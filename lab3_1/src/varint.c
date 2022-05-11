#include "includes.h"

int main()
{
    
    FILE *uncompressed, *compressed, *uncompressed1, *comp;
    comp = fopen("comp.bin", "wb");
    uncompressed = fopen("uncompressed.dat", "wb");
    uncompressed1 = fopen("uncompressed1.dat", "wb");
    remove("compressed.dat");
    compressed = fopen("compressed.dat", "ab+");
    srand(time(NULL));
    uint32_t a[1000000];
    for (int i = 0; i < 1000000; i++) {
        a[i] = generate_number();
    }

    fwrite(a, sizeof(uint32_t), 1000000, uncompressed);
    
    for (int i = 0; i < 1000000; i++) {
        uint8_t buf[4];
        size_t length = encode_varint(a[i], buf);
        fwrite(buf, sizeof(uint8_t), length, compressed);
    }
    uint8_t buf[4];
    size_t length = encode_varint(0xcab3e, buf);
    fwrite(buf, sizeof(uint8_t), length, comp);

    fseek(compressed, 0, SEEK_END);
    long int CompressedLength = ftell(compressed);
    fseek(compressed, 0, SEEK_SET);
    
    uint8_t *p = malloc(CompressedLength);
    if (fread(p, sizeof(uint8_t), CompressedLength, compressed) < 1) {
        printf("Error\n");
        return 0;
    }
    const uint8_t *temp = p;

    uint32_t *t = malloc(sizeof(uint32_t) * 1000000);
    
    for (int i = 0; i < 1000000; i++) {
        t[i] = decode_varint(&temp);
    }
    
    fwrite(t, sizeof(uint32_t), 1000000, uncompressed1);

    int k = 0;
    for(int i = 0; i < 1000000; i++) {
        if (t[i] != a[i])
            k += 1;
    }
    if (k == 0)
        printf("Декодирование успешно\n");
    else   
        printf("Декодирование не успешно\n");

    fclose(compressed);
    fclose(uncompressed1);
    fclose(uncompressed);

    return 0;
}