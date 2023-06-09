#include <iostream>
#include <vector>
#include "detection.h"
#include <string>
#include "translator.h"



Coordinates::Coordinates(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}

RecognizedWord::RecognizedWord(const char* word, float confidence, int x1, int x2, int y1, int y2)
            : word(word), confidence(confidence), position(x1,x2,y1,y2){

            }

void DetectedWords::addWord(const char* word, float confidence, int x1, int x2, int y1, int y2) {
        // std::cout << word << std::endl;
        recognizedWords.push_back(RecognizedWord(word, confidence, x1, x2, y1, y2));
    }
RecognizedWord DetectedWords::selectPrev(){
    std::cout<< recognizedWords.size() << " Fuascjsadjsajdsajdjasdjasdjsadj" << std::endl;
    std::cout<< selectedWordIds.size() << " Fuascjsadjsajdsajdjasdjasdjsadj" << std::endl;
        if(selectedWordIds.size()!=0){
            std::cout<< "And this shit is.... " << selectedWordIds[0] << std::endl;
        int prevId = selectedWordIds[0] - 1;
        std::cout<< "And this shit is.... " << prevId << std::endl;
        std::cout<< recognizedWords[prevId].position.x1 << " " << recognizedWords[prevId].position.x2 << " " << recognizedWords[prevId].position.y1 << " " << recognizedWords[prevId].position.y2 << " " << std::endl;
        selectedWordIds.insert(selectedWordIds.begin(), prevId);
        return recognizedWords[prevId];
        }
    }
RecognizedWord DetectedWords::selectNext(){
        if (selectedWordIds.size() > 0){
        int nextId = selectedWordIds.back() + 1;
        selectedWordIds.push_back(nextId);
        return recognizedWords[nextId];
        }
    }
void DetectedWords::selectWord(int id){
        std::cout << id << " wtf " << std::endl;
        selectedWordIds.push_back(id);
        std::cout<< recognizedWords[id].position.x1 << "sdasd as  asd as" << std::endl;
        std::cout << selectedWordIds[0] << " is it even a thing? " <<selectedWordIds.size() << std::endl;
        
    }
std::string DetectedWords::translateSelected(){
    std::string sentence;
    for (std::vector<int>::size_type i=0; i<selectedWordIds.size(); ++i){
        int id = selectedWordIds[i];
        sentence += recognizedWords[id].word + " ";
        
    }
    std::cout<<sentence <<std::endl;
    std::string translation = translate(sentence);
    std::cout << translation << std::endl;
    return translation;
}
bool DetectedWords::checkCursorMatch(int x, int y, RecognizedWord recWord){
        Coordinates coords = recWord.position;
        return (coords.x1 < x && coords.x2 > x && coords.y1 < y && coords.y2 > y);
    }

RecognizedWord DetectedWords::findMatchingWord(int x, int y){
        for(std::vector<int>::size_type i = 0; i<recognizedWords.size(); ++i){
            if(checkCursorMatch(x,y,recognizedWords[i])){
                std::cout<< "The shit is: " << selectedWordIds.size() << std::endl;
                selectedWordIds.push_back(i);
                std::cout<< "The shit is: " << selectedWords.size() << std::endl;
                // std::vector<RecognizedWord> selectedWords;
                // selectedBoundingBoxes.push_back(recognizedWords[i].position);
                RecognizedWord das = recognizedWords[i];
                selectedWords.push_back(das);
                std::cout<<selectedWords[0].word << std::endl;
                std::cout<< "The word is: " << recognizedWords[i].position.x1 << std::endl;
                return recognizedWords[i];
            }
        }
    }

Coordinates DetectedWords::getBoundingBox(int id){
        std::cout<< "Vector lenghth: " << recognizedWords.size() << "The di: "<< id << "    wuu   " << recognizedWords[(id-1)].position.y2 << std::endl;
        Coordinates coords = recognizedWords[id-1].position;
        return coords;
    }
