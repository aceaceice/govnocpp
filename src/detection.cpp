#include <iostream>
#include <vector>
#include "detection.h"
#include <string>
#include "translator.h"



Coordinates::Coordinates(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}

RecognizedWord::RecognizedWord(const char* word, float confidence, int id, int x1, int x2, int y1, int y2)
            : word(word), confidence(confidence), id(id), position(x1,x2,y1,y2){

            }

void DetectedWords::addWord(const char* word, float confidence, int id, int x1, int x2, int y1, int y2) {
        // std::cout << word << std::endl;
        recognizedWords.push_back(RecognizedWord(word, confidence, id, x1, x2, y1, y2));
    } 
void DetectedWords::selectPrev(){
        if(selectedWords.size() > 0){
        int prevId = selectedWords[0].id - 1;
        selectedWords.insert(selectedWords.begin(), recognizedWords[prevId]);
        selectedText.insert(0, recognizedWords[prevId].word + " ");
        }
    }
void DetectedWords::selectNext(){
        if (selectedWords.size() > 0){
        int nextId = selectedWords.back().id + 1;
        selectedWords.push_back(recognizedWords[nextId]);
        selectedText += recognizedWords[nextId].word + " ";
        }
    }
void DetectedWords::translateSelected(){
    // std::string sentence;
    // for (std::vector<int>::size_type i=0; i<selectedWords.size(); ++i){
    //     sentence += selectedWords[i].word + " ";
    // }
    translationText = translate(selectedText);
}
bool DetectedWords::checkCursorMatch(int x, int y, RecognizedWord recWord){
        Coordinates coords = recWord.position;
        return (coords.x1 < x && coords.x2 > x && coords.y1 < y && coords.y2 > y);
    }

void DetectedWords::findMatchingWord(int x, int y){
        detectionError = "";
        for(std::vector<int>::size_type i = 0; i<recognizedWords.size(); ++i){
            if(checkCursorMatch(x,y,recognizedWords[i])){
                selectedWords.push_back(recognizedWords[i]);
                std::cout<<selectedWords[0].word << std::endl;
                selectedText += recognizedWords[i].word + " ";
                return;
            }
        }
          detectionError = "Could not find matching word";
          throw std::runtime_error("No matching word was found");
    }
void DetectedWords::clearSelected(){
        selectedWords.clear();
        selectedText = "";
    }
void DetectedWords::updateSelectedText(const std::string& text){
        selectedText = text;
    }