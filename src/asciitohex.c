#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    FILE *fp = fopen(argv[1], "rb");
    char hex_chars[256];

    hex_chars[0x30] = 0;
    hex_chars[0x31] = 1;
    hex_chars[0x32] = 2;
    hex_chars[0x33] = 3;
    hex_chars[0x34] = 4;
    hex_chars[0x35] = 5;
    hex_chars[0x36] = 6;
    hex_chars[0x37] = 7;
    hex_chars[0x38] = 8;
    hex_chars[0x39] = 9;
    hex_chars['a'] = 0xa;
    hex_chars['b'] = 0xb;
    hex_chars['c'] = 0xc;
    hex_chars['d'] = 0xd;
    hex_chars['e'] = 0xe;
    hex_chars['f'] = 0xf;
    hex_chars['A'] = 0xa;
    hex_chars['B'] = 0xb;
    hex_chars['C'] = 0xc;
    hex_chars['D'] = 0xd;
    hex_chars['E'] = 0xe;
    hex_chars['F'] = 0xf;

    int i = 0, j = 0;
    FILE *f1 = fopen("DEBUG.dat", "wb");
    if (fp != NULL) {
        char str[512] = { 0 };
        while (!feof(fp)) {
            fgets(str, 512, fp);
            if (str[0] == '#') { fwrite(str, 1, strlen(str), f1); continue; }
            unsigned char bin[32] = { 0 };
            for (i = 0; i < strlen(str); i++) {
                if (str[i] == ' ') continue;
                bin[j] = 0;
                bin[j] = (bin[j] << 4) | hex_chars[str[i]];
                bin[j] = (bin[j] << 4) | hex_chars[str[++i]];
                printf("%02x ", bin[j]);
                j++;
            }
            fwrite(bin, 1, j - 1, f1);
            j = 0;
        }
        fclose(f1);
        fclose(fp);
    }
}
