#include "analyzeScreen.h"
#include "screenCapture.h"
#include <X11/Xlib.h>
#include <tesseract/baseapi.h>
#include <X11/Xutil.h>
#include "detection.h"
#include <leptonica/allheaders.h>
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

    Pix* pix = takeScreenshot();
    XEvent event = getMouseLocation();
    std::cout << "Mouse coordinates: x = " << event.xbutton.x
              << ", y = " << event.xbutton.y << std::endl;

    l_uint32 pixel;
    int x = 1;  // X-coordinate of the pixel
    int y = 1;  // Y-coordinate of the pixel

    if (pix!=NULL) {
    // The pix image is valid
    
        std::cout<<"yes" <<std::endl;
    // You can proceed with pixel access and other operations
    // ...
} else {
    // The pix image is invalid
    // Handle the error case or return
        std::cout<<"nooooooo" <<std::endl;
    // ...
}
    
    if (pixGetPixel(pix, x, y, &pixel)) {
        // The pixel value is stored in 'pixel'
        // You can perform operations or access its components
        // For example, you can get the red, green, blue components using the following masks:
        int red = GET_DATA_BYTE(&pixel, COLOR_RED);
        int green = GET_DATA_BYTE(&pixel, COLOR_GREEN);
        int blue = GET_DATA_BYTE(&pixel, COLOR_BLUE);
        std::cout << red << "   " << green << "    " << blue << "  pixold"<<std::endl;
        // Do something with the pixel values
        // ...
    } else {
        std::cout<<"fuccckkk" <<std::endl;
        // Failed to get the pixel value
        // Handle the error case
    }



    Pix* pixGray = pixConvertRGBToGray(pix, 0.21, 0.72, 0.07);
    savePixToFile(pix, "output.png");
    // cv::cvtColor(screenshot, screenshot, cv::COLOR_BGR2GRAY);
    // const unsigned char* image = reinterpret_cast<const unsigned char*>(screenshot.data);
    // std::memcpy(const_cast<unsigned char*>(image), screenshot.data, screenshot.total());
    // std::ofstream outfile("output.txt");
    // std::streambuf* coutbuf = std::cout.rdbuf();
    tesseract::TessBaseAPI api;

    api.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    api.SetPageSegMode(tesseract::PSM_AUTO);

    // // Set the image
    api.SetImage(pix);
    char* recognizedText = api.GetUTF8Text();
    
    // // Process the recognized text
    // std::cout << "Recognized text: " << recognizedText << std::endl;
    // // cv::Mat imageMat(screenshot.rows, screenshot.cols, CV_8UC1, const_cast<unsigned char*>(image));
    // // cv::imshow("Gowno", imageMat);
    // // Get the recognized words and their bounding boxes
    tesseract::ResultIterator* iter = api.GetIterator();
    std::cout << "Shoigu! Gerasimov!" << (iter==NULL) << std::endl;
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    std::cout << "Shoigu! Gerasimov!" << (iter==NULL) << std::endl;
    // // CGEventRef event = CGEventCreate(NULL);
    // // CGPoint cursorPos = CGEventGetLocation(event);
    // // CFRelease(event);
    DetectedWords recWords = DetectedWords();
    int a = 0;

    if (iter != NULL) {
        do {

            const char* word = iter->GetUTF8Text(level);
            float confidence = iter->Confidence(level);
            if (confidence > 0.3) {
            // std::cout << &recWords << std::endl;
            int x1, y1, x2, y2;
            iter->BoundingBox(level, &x1, &y1, &x2, &y2);
            recWords.addWord(word, confidence, x1,x2,y1,y2);
            a++;
            // if (x1 < event.xbutton.x && x2 > event.xbutton.x && y1 < event.xbutton.y && y2 > event.xbutton.y){
            //     std::cout << "Found shit: 123" << std::endl;
            //     recWords.selectWord(a); 
            //     Coordinates cords = recWords.getBoundingBox(a);
            //     std::cout << "Bounding x:   " << cords.x1 << std::endl;
            // }
            // std::cout << "Length: " << recWords.recognizedWords.size() << std::endl; 
            // std::cout << "Word: " << recWords.recognizedWords[a].word << std::endl; 
            // std::cout << x1 << " " << y1 << " " << x2 << " " << word << std::endl;    
    // Print the coordinates
            // std::cout << "Shoigu! Gerasimov!" << x1 << std::endl;
            // Draw a rectangle around the recognized word
            // std::cout << "Recognized word: " << word << " (confidence: " << confidence << ")" << std::endl;
            }
            
            delete[] word;
        } while (iter->Next(level));
    }
    // cv::imshow("res", screenshot);
    // Clean up
    delete iter;
    api.End();
    // cv::waitKey(0);
    return recWords;
}