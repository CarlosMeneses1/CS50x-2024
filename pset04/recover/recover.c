#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int SIZE_BLOCK = 512;

int main(int argc, char *argv[])
{
    // Make sure that command line has only 1 element
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *memory_card = fopen(argv[1], "r");
    if (memory_card == NULL)
    {
        printf("Failed to open the file\n");
        return 1;
    }

    uint8_t buffer[SIZE_BLOCK];
    int count = 0;
    char filename[8];
    bool first_jpg = true;
    FILE *img = NULL;

    // While there's still data left to read from memory card
    while (fread(buffer, SIZE_BLOCK, 1, memory_card))
    {
        // If it's the beginning of a JPEGs file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's the first JPEG
            if (first_jpg == true)
            {
                // Update bool variable
                first_jpg = false;
            }
            // Else, close previous JPEG file
            else
            {
                fclose(img);
            }

            // Create and open a new JPEG file
            sprintf(filename, "%03i.jpg", count);
            count++;
            img = fopen(filename, "w");
            fwrite(buffer, SIZE_BLOCK, 1, img);
        }
        // Else, keep writing data into JPEG file
        else if (first_jpg == false)
        {
            fwrite(buffer, SIZE_BLOCK, 1, img);
        }
    }
    fclose(img);
    fclose(memory_card);
}
