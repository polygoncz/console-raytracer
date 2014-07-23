#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

class ProgressBar
{
public:
    struct Characters {
        char leftDelimiter;
        char rightDelimiter;
        char filled;
        char empty;
    };

    const static Characters defaultCharacters;

    ProgressBar(unsigned int displayedSteps, unsigned int total = 100,
                unsigned int finished = 0, bool printPercent = true, bool singleLine = true,
                const Characters& chars = defaultCharacters);

    void setCompleted(unsigned int steps);
    void print(void) const;

private:
    const unsigned int displayedSteps;
    const unsigned int total; ///< percent
    unsigned int finished; ///< percent

    ProgressBar::Characters characters;

    bool printPercent;
    bool singleLine;
};

#endif // PROGRESSBAR_H
