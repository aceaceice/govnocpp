#include <iostream>
#include <vector>
#include "detection.h"

Coordinates::Coordinates(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), y1(x1), y2(y2) {}

RecognizedWord::RecognizedWord(const char* word, float confidence, int x1, int x2, int y1, int y2)
            : word(word), confidence(confidence), position(x1,x2,y1,y2){}

void DetectedWords::addWord(const char* word, float confidence, int x1, int x2, int y1, int y2) {
        recognizedWords.push_back(RecognizedWord(word, confidence, x1, x2, y1, y2));
    }
RecognizedWord DetectedWords::selectPrev(){
    std::cout<< recognizedWords.size() << " Fuascjsadjsajdsajdjasdjasdjsadj" << std::endl;
    std::cout<< selectedWordIds.size() << " Fuascjsadjsajdsajdjasdjasdjsadj" << std::endl;
        if(selectedWordIds.size()!=0){
            std::cout<< "And this shit is.... " << selectedWordIds[0] << std::endl;
        int prevId = selectedWordIds[0] - 1;
        std::cout<< "And this shit is.... " << prevId << std::endl;
        selectedWordIds.insert(selectedWordIds.begin(), prevId);
        return recognizedWords[prevId];
        }
    }
void DetectedWords::selectNext(){
        int nextId = selectedWordIds.back() + 1;
        selectedWordIds.push_back(nextId);
    }
void DetectedWords::selectWord(int id){
        std::cout << id << " wtf " << std::endl;
        selectedWordIds.push_back(id);
        std::cout << selectedWordIds[0] << " is it even a thing? " <<selectedWordIds.size() << std::endl;
        
    }

bool DetectedWords::checkCursorMatch(int x, int y, RecognizedWord recWord){
        Coordinates coords = recWord.position;
        return (coords.x1 < x && coords.x2 > x && coords.y1 < y && coords.y2 > y);
    }

int DetectedWords::findMatchingWord(int x, int y){
        for(int i = 0; i<recognizedWords.size(); ++i){
            if(checkCursorMatch(x,y,recognizedWords[i])){
                selectedWordIds.push_back(i);

                return i;
            }
        }
    }

Coordinates DetectedWords::getBoundingBox(int id){
        std::cout<< "Vector lenghth: " << recognizedWords.size() << "The di: "<< id << "    wuu   " << recognizedWords[(id-1)].position.y2 << std::endl;
        Coordinates coords = recognizedWords[id-1].position;
        return coords;
    }
