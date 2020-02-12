#include <iostream>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Image {
    std::vector<unsigned char> data;
    int height;
    int width;
    int channels;

    void set(int y, int x, int channel, unsigned char value) {
        data[y*width*channels + x*channels + channel] = value;
    }

    unsigned char get(int y, int x, int channel) {
        return data[y*width*channels + x*channels + channel];
    }

    Image(int height, int width, int channels) : data(height*width*channels), height(height), width(width), channels(channels) {}
};

void nearestNeighbor(Image &image, Image &newImage) {
    int height = image.height;
    int width = image.width;
    int newHeight = newImage.height;
    int newWidth = newImage.width;
    double xr = (double)width / newWidth;
    double yr = (double)height / newHeight;

    int x,y;
    for (int i = 0; i < newHeight; i ++) {
        y = i * yr;
        for (int j = 0; j < newWidth; j++) {
            x = j * xr;
            for (int k = 0; k < image.channels; k++) {
                newImage.set(i, j, k, image.get(y, x, k));
            }
        }
    }
}

void resize(Image &image, int newWidth, int newHeight)
{
    //if new dimensions are identical, do nothing
    if (image.height == newHeight && image.width == newWidth) return;

    Image newImage(newHeight, newWidth, image.channels);
    nearestNeighbor(image, newImage);

    image = newImage;
}

void drawAscii(Image &image, int invert) {
    std::string ascii = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    if (invert) ascii = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    
    int height, width, channels;
    height = image.height;
    width = image.width;
    channels = image.channels;

    int sum;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < channels; k++) {
                sum += image.get(i,j,k);
            }
            std::cout << ascii[0 + ((sum) * 69 / (255 * channels))];
            sum = 0;
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    //argv [filename, width (optional), invert (optional)]
    if (argc == 1) {
        std::cout << "Too few arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (argc > 4) {
        std::cout << "Too many arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    //defaults
    int newWidth = 100;
    int invert = 0;
    if(argc > 2) { newWidth = atoi(argv[2]); }
    if(argc > 3) { invert = atoi(argv[3]); }

    int width,height,channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);

    if (data == NULL) {
        std::cout << "Could not load image" << std::endl;
        exit(EXIT_FAILURE);
    }

    //load data into image struct
    Image image = Image(height, width, channels);
    for (int i = 0; i < height*width*channels; i++) {
        image.data[i] = data[i];
    }
    
    int newHeight = (height * newWidth / (width * 2));

    resize(image, newWidth, newHeight);
    drawAscii(image, invert);
    
    exit(EXIT_SUCCESS);
}