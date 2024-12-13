#include "helpers.h"
#include <math.h>

int calculate_average_color(int Red, int Green, int Blue);
int check_max_RGB(int RGB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average_color;

    // Iterate through  each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average grayscale
            average_color = calculate_average_color(image[i][j].rgbtRed,
                                                    image[i][j].rgbtGreen,
                                                    image[i][j].rgbtBlue);

            // Update pixel's values to grayscale
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia_red, sepia_green, sepia_blue;

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the 'sepia value'
            sepia_red = round(.393 * image[i][j].rgbtRed +
                              .769 * image[i][j].rgbtGreen +
                              .189 * image[i][j].rgbtBlue);
            sepia_green = round(.349 * image[i][j].rgbtRed +
                                .686 * image[i][j].rgbtGreen +
                                .168 * image[i][j].rgbtBlue);
            sepia_blue = round(.272 * image[i][j].rgbtRed +
                               .534 * image[i][j].rgbtGreen +
                               .131 * image[i][j].rgbtBlue);

            // Check if 'sepia value' is in the correct rack
            image[i][j].rgbtRed = check_max_RGB(sepia_red);
            image[i][j].rgbtGreen = check_max_RGB(sepia_green);
            image[i][j].rgbtBlue = check_max_RGB(sepia_blue);
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
        for (int j = 0; j < (width / 2); j++)
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
    double sR, sG, sB, count;

    // Copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate through each pixel and check its position
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Variables initialization
            sR = sG = sB = count = 0;

            // Pixel top left corner
            if (i == 0 && j == 0)
            {
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Pixel top rigth corner
            else if (i == 0 && j == width - 1)
            {
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = -1; y <= 0; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Pixel bottom left corner
            else if (i == height - 1 && j == 0)
            {
                for (int x = -1; x <= 0; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Pixel bottom rigth corner
            else if (i == height - 1 && j == width - 1)
            {
                for (int x = -1; x <= 0; x++)
                {
                    for (int y = -1; y <= 0; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Top pixels
            else if (i == 0)
            {
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Left pixels
            else if (j == 0)
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Bottom pixels
            else if (i == height - 1)
            {
                for (int x = -1; x <= 0; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Right pixels
            else if (j == width - 1)
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 0; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Others pixels
            else
            {
                for (int x = -1; x <= 1; x++)
                {
                    for (int y = -1; y <= 1; y++)
                    {
                        sR += copy[i + x][j + y].rgbtRed;
                        sG += copy[i + x][j + y].rgbtGreen;
                        sB += copy[i + x][j + y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Update pixels
            image[i][j].rgbtRed = (int) round(sR / count);
            image[i][j].rgbtGreen = (int) round(sG / count);
            image[i][j].rgbtBlue = (int) round(sB / count);
        }
    }
    return;
}

int calculate_average_color(int Red, int Green, int Blue)
{
    // Calculate and return the average between the Red, Green and Blue color (a.k.a Greyscale)
    return round((Red + Green + Blue) / 3.0);
}

int check_max_RGB(int RGB)
{
    // Check if the RBG value is in the correct rank (0 - 255)
    if (RGB > 255)
    {
        return 255;
    }
    else
    {
        return RGB;
    }
}
