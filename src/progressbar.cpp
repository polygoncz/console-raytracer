#include "progressbar.h"

#include <iostream>

const ProgressBar::Characters ProgressBar::defaultCharacters = {
    '[',
    ']',
    '=',
    ' '
};

ProgressBar::ProgressBar(unsigned int displayedSteps, unsigned int total,
                         unsigned int finished, bool printPercent, bool singleLine,
                         const Characters& chars)
    : displayedSteps(displayedSteps),
      total(total),
      finished(finished),
      characters(chars),
      printPercent(printPercent),
      singleLine(singleLine)
{ }

void ProgressBar::setCompleted(unsigned int steps)
{
    if (steps > total)
        steps = total;

    finished = steps;
}

void ProgressBar::print(void) const
{
    unsigned int filledSteps = finished / (total / displayedSteps);

    //clear line
    if (singleLine)
        std::cout << '\r';

    //print bar
    std::cout << characters.leftDelimiter;
    for (unsigned int step = 0; step < displayedSteps; ++step) {
        if (step < filledSteps)
            std::cout << characters.filled;
        else
            std::cout << characters.empty;
    }
    std::cout << characters.rightDelimiter;

    //print percent
    if (printPercent) {
        std::cout << ' ';
        std::cout << finished << " %";
    }

    if (!singleLine)
        std::cout << std::endl;

    std::cout.flush();
}
