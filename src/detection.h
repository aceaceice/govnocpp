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
        Coordinates position;
        std::string word;
        float confidence;

        RecognizedWord(const char* word, float confidence, int x1, int x2, int y1, int y2);
};

class DetectedWords{
    public:
        std::vector<int> selectedWordIds;
        const char* translationText;
        std::vector<RecognizedWord> recognizedWords;
        std::vector<RecognizedWord> selectedWords;
    
    void addWord(const char* word, float confidence, int x1, int x2, int y1, int y2);
    RecognizedWord selectPrev();
    RecognizedWord selectNext();
    void selectWord(int id);
    bool checkCursorMatch(int x, int y, RecognizedWord recWord);
    std::string translateSelected();
    RecognizedWord findMatchingWord(int x, int y);

    Coordinates getBoundingBox(int id);
};
#endif