#include "kies_index.h"

int lees_int(const std::string& prompt);

int kies_index(int max_index, const std::string& prompt)
{
    int index = lees_int(prompt);

    if (index < 0 || index >= max_index)
    {
        return -1;
    }
    return index;
}