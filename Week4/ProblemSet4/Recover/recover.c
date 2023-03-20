#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Enter only one argument\n");
        return 1;
    }

    // Open file
    char *name = argv[1];
    FILE *inputfile = fopen(name, "r");

    // Check if file exists
    if (inputfile == NULL)
    {
        printf("No such file found.\n");
        return 1;
    }

    // create a new type to store a byte of data

    // NUmber of images
    int count = 0;

    // Buffer
    typedef uint8_t BYTE;
    BYTE buffer[512];

    // File pointer to handle JPEG
    FILE *outputfile = NULL;

    // Allocate memory of filename
    char *filename = malloc(8 * sizeof(char));

    // Read 512 bytes into a buffer until the end
    while (fread(buffer, sizeof(char), 512, inputfile) == 512)
    {
        // Check start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Close previous JPG
            if (count != 0)
            {
                fclose(outputfile);
            }
            // create filename
            sprintf(filename, "%03i.jpg", count);

            // Open outputfile for writing
            outputfile = fopen(filename, "w");
            count++;
        }

        if (outputfile != NULL)
        {
            // Keep writing to the same jpeg
            fwrite(buffer, sizeof(char), 512, outputfile);
        }
    }

    // close remaining files
    fclose(inputfile);
    fclose(outputfile);
    free(filename);
    return 0;
}
