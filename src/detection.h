#ifndef DETECTION_H
#define DETECTION_H
#include <vector>

class Coordinates {
    public: 
        int x1;
        int x2;
        int y1;
        int y2;

        Coordinates(int x1, int x2, int y1, int y2);
};;

class RecognizedWord {
    public: 
        Coordinates position;
        const char* word;
        float confidence;

        RecognizedWord(const char* word, float confidence, int x1, int x2, int y1, int y2);
};

class DetectedWords{
    public:
        std::vector<int> selectedWordIds;
        std::vector<RecognizedWord> recognizedWords;

    void addWord(const char* word, float confidence, int x1, int x2, int y1, int y2);
    RecognizedWord selectPrev();
    void selectNext();
    void selectWord(int id);
    bool checkCursorMatch(int x, int y, RecognizedWord recWord);

    int findMatchingWord(int x, int y);

    Coordinates getBoundingBox(int id);
};;
#endif