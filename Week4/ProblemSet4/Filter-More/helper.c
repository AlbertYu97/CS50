#include "helpers.h"
#include <math.h>

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Create 2d arrays Gx and Gy
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize values
            float gxRed = 0;
            float gyRed = 0;
            float gxBlue = 0;
            float gyBlue = 0;
            float gxGreen = 0;
            float gyGreen = 0;

            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    // Check if the cell is inside the image, ignore edges
                    if (i + y > 0 && i + y < height - 1 && j + x > 0 && j + x < width - 1)
                    {
                        gxRed += copy[i + y][j + x].rgbtRed * gx[y + 1][x + 1];
                        gyRed += copy[i + y][j + x].rgbtRed * gy[y + 1][x + 1];
                        gxGreen += copy[i + y][j + x].rgbtGreen * gx[y + 1][x + 1];
                        gyGreen += copy[i + y][j + x].rgbtGreen * gy[y + 1][x + 1];
                        gxBlue += copy[i + y][j + x].rgbtBlue * gx[y + 1][x + 1];
                        gyBlue += copy[i + y][j + x].rgbtBlue * gy[y + 1][x + 1];
                    }
                }
            }
            // Caculate Gx and Gy
            int red = round(sqrt(pow(2, gxRed) + pow(2, gyRed)));
            int green = round(sqrt(pow(2, gxGreen) + pow(2, gyGreen)));
            int blue = round(sqrt(pow(2, gxBlue) + pow(2, gyBlue)));

            // Set values on Image
            image[i][j].rgbtRed = (red < 255) ? red : 255;
            image[i][j].rgbtGreen = (green < 255) ? green : 255;
            image[i][j].rgbtBlue = (blue < 255) ? blue : 255;


        }
    }
}
