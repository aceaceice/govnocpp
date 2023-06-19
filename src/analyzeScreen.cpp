// #ifdef __linux__ 
// #include <opencv2/opencv.hpp>
// #include <opencv2/stitching.hpp> 
// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include "detection.h"
// #include <leptonica/allheaders.h>

// #include <png.h>
// #include <tesseract/baseapi.h>
// #include <iostream>


// XEvent getMouseLocation() {
//     Display* display = XOpenDisplay(nullptr);
//     Window root = DefaultRootWindow(display);

//     XEvent event;
//     XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
//                   &event.xbutton.x_root, &event.xbutton.y_root,
//                   &event.xbutton.x, &event.xbutton.y,
//                   &event.xbutton.state);

//     XCloseDisplay(display);
//     return event;
// }



// DetectedWords analyzeScreen() {
//     // Load image using OpenCV

//     Display* display = XOpenDisplay(NULL);
//     Window root = DefaultRootWindow(display);
//     XWindowAttributes windowAttributes;
//     XGetWindowAttributes(display, root, &windowAttributes);
//     int width = windowAttributes.width;
//     int height = windowAttributes.height;
// XImage* imageX = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);

// // Create an OpenCV Mat object from the XImage data
// cv::Mat image(height, width, CV_8UC4, imageX->data);

    
//     // Convert image to grayscale
//     cv::Mat grayImage;
//     cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    
//     // Apply thresholding
//     cv::Mat thresholdedImage;
//     cv::threshold(grayImage, thresholdedImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
//     // Create Tesseract OCR object
//     tesseract::TessBaseAPI ocr;
//     ocr.Init(NULL, "eng"); // Set language ("eng" for English)
//     ocr.SetImage(thresholdedImage.data, thresholdedImage.cols, thresholdedImage.rows, 1, thresholdedImage.cols);
    
//     // Perform OCR
//     ocr.Recognize(0);
//     tesseract::ResultIterator* iterator = ocr.GetIterator();
    
//     std::string recognizedText;
//     float confidence;
//     DetectedWords recWords = DetectedWords();
//     int i = 0;
//     while (iterator->Next(tesseract::RIL_WORD)) {
//         const char* word = iterator->GetUTF8Text(tesseract::RIL_WORD);
//         float conf = iterator->Confidence(tesseract::RIL_WORD);
//         int x1, y1, x2, y2;
        
//         iterator->BoundingBox(tesseract::RIL_WORD, &x1, &y1, &x2, &y2);
//         if (word != nullptr && conf > 0.2) {
//             recWords.addWord(word, conf, x1,x2,y1,y2);
//             // std::cout<< word << " " << i << " " << y1 << " " << y2 << std::endl;

//             delete[] word;
//             ++i;
//         }
//     }
    
//     // Print recognized text and confidence
    
//     // Save the image with bounding boxes
//     // cv::imwrite("output.jpg", image);
//     // Release resources
//     ocr.Clear();
//     ocr.End();
    
//     return recWords;
// }
#ifdef __linux__

#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp> 
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "detection.h"
#include <leptonica/allheaders.h>

#include <png.h>
#include <tesseract/baseapi.h>
#include <iostream>

char* tessdata = "TESSDATA_PREFIX=/home/jasos/govnocpp/tessdata";

cv::Mat takeScreenshot() {
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
    return thresholdedImage;


}
            float scale = 1;


#elif __APPLE__

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ApplicationServices/ApplicationServices.h> 
#include <tesseract/baseapi.h>
#include <fstream>
#include "detection.h"
    char* tessdata = "TESSDATA_PREFIX=/Users/jasos/Workspace/govnocpp/tessdata";
float scale;
cv::Mat takeScreenshot() {
    CGImageRef image = CGDisplayCreateImage(CGMainDisplayID());
    cv::Mat screenshot = cv::Mat(CGImageGetHeight(image), CGImageGetWidth(image), CV_8UC4);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef contextRef = CGBitmapContextCreate(screenshot.data, screenshot.cols, screenshot.rows, 8, screenshot.step[0], colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);
    CGContextDrawImage(contextRef, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(contextRef);
    CGImageRelease(image);
    cv::cvtColor(screenshot, screenshot, cv::COLOR_RGBA2BGR);
    cv::cvtColor(screenshot, screenshot, cv::COLOR_BGR2GRAY);
            scale = 1440/(float)screenshot.cols;
    return screenshot;
}
#endif

DetectedWords analyzeScreen() {
    cv::Mat screenshot = takeScreenshot();
    const unsigned char* image = reinterpret_cast<const unsigned char*>(screenshot.data);
    std::memcpy(const_cast<unsigned char*>(image), screenshot.data, screenshot.total());
    std::streambuf* coutbuf = std::cout.rdbuf();
    putenv(tessdata);
    tesseract::TessBaseAPI api;
    api.Init(NULL, "pol", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PSM_AUTO);
    // Set the image
    api.SetImage(screenshot.data, screenshot.cols, screenshot.rows, 1, screenshot.cols);

    // api.SetImage(image, screenshot.cols, screenshot.rows, 1, screenshot.step);
    api.GetUTF8Text();
    std::cout << "api.GetUTF8Text()" << std::endl;
    DetectedWords recWords = DetectedWords();
    
    // Process the recognized text
    // Get the recognized words and their bounding boxes
    tesseract::ResultIterator* iter = api.GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    int id = 0;

    if (iter != NULL) {
        do {
            // float scale = 1440/(float)screenshot.cols;
            const char* word = iter->GetUTF8Text(level);
            float confidence = iter->Confidence(level);
            int x1, y1, x2, y2;
            iter->BoundingBox(level, &x1, &y1, &x2, &y2);
            if (confidence > 0.8){
            recWords.addWord(word, confidence, id, x1*scale,x2*scale,y1*scale,y2*scale);
            id++;
            }
            delete[] word;
        } while (iter->Next(level));
    }
    // Clean up
    std::cout.rdbuf(coutbuf);
    delete iter;
    api.End();
    return recWords;
}
