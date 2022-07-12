#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Enter one raw file!");
        return 1;
    }

    if (fopen(argv[1], "r") == NULL) {
        printf("File can not be opened!");
        return 1;
    }

    int cnt = 0;
    FILE *file = fopen(argv[1], "r");
    BYTE buffer[512];
    int flag = 0;
    FILE *jpg = NULL;
    char str[8];
    while (fread(buffer, sizeof(BYTE), 512, file)) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // find a jpg
            flag = 1;
            if (cnt == 50) {
                break;
            }
            if (cnt >= 1) {
                fclose(jpg);
            }
            sprintf(str, "%.3d.jpg", cnt++);
            jpg = fopen(str, "w");
        }

        if (flag) {

            // 是从文件最后写的吗
            fwrite(buffer, sizeof(BYTE), 512, jpg);
        }
    }
    fclose(jpg);
    fclose(file);
}
