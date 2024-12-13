#include "helpers.h"
#include <math.h>

int calculate_average_color(int Red, int Green, int Blue);
int check_max_RGB(int RGB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average_color;

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average grayscale
            average_color = calculate_average_color(image[i][j].rgbtRed, image[i][j].rgbtGreen,
                                                    image[i][j].rgbtBlue);

            // Update pixle's value to grayscale
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap a pixel for it's reflection
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    float sR, sG, sB, count;

    // Make a copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sR = sG = sB = count = 0;

            // Go to each 3x3 position
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // If the position goes off the edge (rows), skip the iteration
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }
                    // If the position goes off the edge (colums), skip the iteration
                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    // Else, calculate the 'blur box'
                    sR += copy[i + x][j + y].rgbtRed;
                    sG += copy[i + x][j + y].rgbtGreen;
                    sB += copy[i + x][j + y].rgbtBlue;
                    count++;
                }
            }
            // Update the pixel value
            image[i][j].rgbtRed = (int) round(sR / count);
            image[i][j].rgbtGreen = (int) round(sG / count);
            image[i][j].rgbtBlue = (int) round(sB / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Declare Gx and Gy arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    double sRx, sGx, sBx, sRy, sGy, sBy;

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sRx = sGx = sBx = sRy = sGy = sBy = 0;

            // Go to each 3x3 position
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // If the position goes off the edge (rows), skip the iteration
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }
                    // if the position goes off the edge (colums), skip the iteration
                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    // Else, calculate the Solbel Operator
                    sRx += Gx[x + 1][y + 1] * copy[i + x][j + y].rgbtRed;
                    sGx += Gx[x + 1][y + 1] * copy[i + x][j + y].rgbtGreen;
                    sBx += Gx[x + 1][y + 1] * copy[i + x][j + y].rgbtBlue;
                    sRy += Gy[x + 1][y + 1] * copy[i + x][j + y].rgbtRed;
                    sGy += Gy[x + 1][y + 1] * copy[i + x][j + y].rgbtGreen;
                    sBy += Gy[x + 1][y + 1] * copy[i + x][j + y].rgbtBlue;
                }
            }
            // Update the pixel value
            image[i][j].rgbtRed = check_max_RGB(round(sqrt((pow(sRx, 2) + pow(sRy, 2)))));
            image[i][j].rgbtGreen = check_max_RGB(round(sqrt((pow(sGx, 2) + pow(sGy, 2)))));
            image[i][j].rgbtBlue = check_max_RGB(round(sqrt((pow(sBx, 2) + pow(sBy, 2)))));
        }
    }
    return;
}

int calculate_average_color(int Red, int Green, int Blue)
{
    // Calculate and return the average value between Red, Green and Blue color (a.k.a Grescale)
    return round((Red + Green + Blue) / 3.0);
}

int check_max_RGB(int RGB)
{
    // Check if the RGB value is in the correct rank (0 - 255)
    if (RGB > 255)
    {
        return 255;
    }
    else
    {
        return RGB;
    }
}
