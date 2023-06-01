#ifndef _SqueezeText
#define _SqueezeText

#include <string>
#include <algorithm>

#include "raylib.h"

namespace TextUtility{
    inline const std::string fitTextByWidth(const std::string& text, float fontSize ,float maxWidth){
        float width = MeasureText(text.c_str(), fontSize);
        if(width <= maxWidth){
            return text;
        }


        std::string newText;
        float ratio = maxWidth / width;
        int step = static_cast<int>(ratio * (text.size() -1));
    
        int currentIndex = 0;
        int lastIndex = text.size() - 1;
        while (currentIndex != lastIndex){
            int actualStep = currentIndex + step  < static_cast<int>(text.size()) ? step : lastIndex - currentIndex;
            std::string sub = text.substr(currentIndex, actualStep);
            if(sub.substr(0,1) == " "){
                sub.erase(sub.begin(), sub.begin() + 1);
            }

            //check if word gets split, if so backtrack
            int nextIndex = (currentIndex + actualStep + 1);
            if(nextIndex < static_cast<int>(text.size()) && text.substr(currentIndex, nextIndex) != " "){
                int indexOfLastWhiteSpace = sub.find_last_of(" ");
                int backtrackSteps = (sub.size() -1) - indexOfLastWhiteSpace;
                sub = sub.substr(0, indexOfLastWhiteSpace);
                actualStep -= backtrackSteps;
            }

            currentIndex += actualStep;
            newText += sub;
            newText += (currentIndex+1) < static_cast<int>(text.size()) ? "\n" : "";
        }

        newText += text.substr(lastIndex, 1); //ugly hack but I'm tired of this shit.

        return newText;
    }
}

#endif