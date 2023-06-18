#ifndef DETECTION_H
#define DETECTION_H
#include <vector>
#include <string>

class Coordinates {
    public: 
        int x1;
        int x2;
        int y1;
        int y2;

        Coordinates(int x1, int x2, int y1, int y2);
};

class RecognizedWord {
    public: 
        std::string word;
        float confidence;
        int id;
        Coordinates position;

        RecognizedWord(const char* word, float confidence, int id, int x1, int x2, int y1, int y2);
};

class DetectedWords{
    public:
        std::string translationText;
        std::string detectionError;
        std::string selectedText;
        std::vector<RecognizedWord> recognizedWords;
        std::vector<RecognizedWord> selectedWords;
        bool shouldExit;
    
    void addWord(const char* word, float confidence, int id, int x1, int x2, int y1, int y2);
    void selectPrev();
    void selectNext();
    void updateSelectedText(const std::string& text);
    bool checkCursorMatch(int x, int y, RecognizedWord recWord);
    void translateSelected();
    void findMatchingWord(int x, int y);
    void clearSelected();
};
#endif