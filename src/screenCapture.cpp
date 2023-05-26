#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <png.h>
#include <iostream>
#include "screenCapture.h"

void saveXImageAsPNG(XImage* ximage, const std::string& filename) {
    int width = ximage->width;
    int height = ximage->height;
    int depth = ximage->depth;
    int bytes_per_line = ximage->bytes_per_line;
    unsigned char* image_data = reinterpret_cast<unsigned char*>(ximage->data);

    FILE* fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(fp);
        std::cerr << "Failed to create PNG write struct" << std::endl;
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        fclose(fp);
        png_destroy_write_struct(&png, NULL);
        std::cerr << "Failed to create PNG info struct" << std::endl;
        return;
    }

    png_init_io(png, fp);
    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png, info);

    png_bytep row = new png_byte[bytes_per_line];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            row[x * 3] = image_data[y * bytes_per_line + x * depth / 8 + 2];     // Red
            row[x * 3 + 1] = image_data[y * bytes_per_line + x * depth / 8 + 1]; // Green
            row[x * 3 + 2] = image_data[y * bytes_per_line + x * depth / 8];     // Blue
        }
        png_write_row(png, row);
    }

    delete[] row;

    png_write_end(png, info);
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    std::cout << "XImage saved as PNG: " << filename << std::endl;
}


void savePixToFile(Pix* pix, const std::string& filename) {
    if (!pix) {
        std::cerr << "Invalid Pix* image." << std::endl;
        return;
    }

    if (filename.empty()) {
        std::cerr << "Invalid filename." << std::endl;
        return;
    }

    // Save the Pix* image to file
    if (pixWrite(filename.c_str(), pix, IFF_PNG) != 0) {
        std::cerr << "Failed to save the image to file: " << filename << std::endl;
        return;
    }

    std::cout << "Image saved to file: " << filename << std::endl;
}

Pix* ximageToPix(XImage* ximage) {
    int width = ximage->width;
    int height = ximage->height;
    int depth = ximage->bits_per_pixel;
    int bytes_per_line = ximage->bytes_per_line;

    // Create a new Pix* structure
    Pix* pix = pixCreate(width, height, depth);

    // Copy the pixel data from ximage to pix
    unsigned char* src_data = reinterpret_cast<unsigned char*>(ximage->data);

    l_uint32* dest_data = reinterpret_cast<l_uint32*>(pixGetData(pix));

    for (int y = 0; y < height; ++y) {
        unsigned char* src_line = src_data + y * bytes_per_line;
        l_uint32* dest_line = dest_data + y * pixGetWpl(pix);
        // std::cout<<dest_line << (y * pixGetWpl(pix))<<std::endl;
        // Copy each pixel from src_line to dest_line
        for (int x = 0; x < width; ++x) {
            dest_line[x] = static_cast<l_uint32>(src_line[x]);
        }
    }
    return pix;
}

Pix* takeScreenshot() {
    Display* display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);
    int width = windowAttributes.width;
    int height = windowAttributes.height;
    XImage* image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
    std::cout<<"Size: "<<sizeof(image->data)<<std::endl;
    saveXImageAsPNG(image, "dupa.png");
    const char *filename = "dupa.png";
    Pix* buffer = pixRead(filename);
    std::cout<<"Size: "<<sizeof(pixGetData(buffer))<<std::endl;
    return buffer;
}