#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp> 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "detection.h"
#include <leptonica/allheaders.h>

#include <png.h>
#include <tesseract/baseapi.h>
#include <iostream>


XEvent getMouseLocation() {
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);

    XEvent event;
    XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);

    XCloseDisplay(display);
    return event;
}



DetectedWords analyzeScreen() {
    // Load image using OpenCV

    Display* display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(display, root, &windowAttributes);
    int width = windowAttributes.width;
    int height = windowAttributes.height;
XImage* imageX = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

// Create an OpenCV Mat object from the XImage data
cv::Mat image(height, width, CV_8UC4, imageX->data);

    
    // Convert image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    
    // Apply thresholding
    cv::Mat thresholdedImage;
    cv::threshold(grayImage, thresholdedImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    // Create Tesseract OCR object
    tesseract::TessBaseAPI ocr;
    ocr.Init(NULL, "eng"); // Set language ("eng" for English)
    ocr.SetImage(thresholdedImage.data, thresholdedImage.cols, thresholdedImage.rows, 1, thresholdedImage.cols);
    
    // Perform OCR
    ocr.Recognize(0);
    tesseract::ResultIterator* iterator = ocr.GetIterator();
    
    std::string recognizedText;
    float confidence;
    DetectedWords recWords = DetectedWords();
    int i = 0;
    while (iterator->Next(tesseract::RIL_WORD)) {
        const char* word = iterator->GetUTF8Text(tesseract::RIL_WORD);
        float conf = iterator->Confidence(tesseract::RIL_WORD);
        int x1, y1, x2, y2;
        
        iterator->BoundingBox(tesseract::RIL_WORD, &x1, &y1, &x2, &y2);
        if (word != nullptr && conf > 0.2) {
            recWords.addWord(word, conf, x1,x2,y1,y2);
            // std::cout<< word << " " << i << " " << y1 << " " << y2 << std::endl;

            delete[] word;
            ++i;
        }
    }
    
    // Print recognized text and confidence
    
    // Save the image with bounding boxes
    // cv::imwrite("output.jpg", image);
    // Release resources
    ocr.Clear();
    ocr.End();
    
    return recWords;
}