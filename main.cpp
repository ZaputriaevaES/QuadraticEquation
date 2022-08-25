#include "head.h"

int main(int argc, const char* argv[])
{
    int ModeSelected = 0;

    for (int i = 1; i < argc; i++)
    {
        if(strncmp("-u", argv[i], 3) == 0)
        {
            Usual();
            ModeSelected = 1;
        }
        else if(strncmp("-t", argv[i], 3) == 0)
        {
            UniTest();
            ModeSelected = 1;
        }
    }
    if (ModeSelected == 0)
        Help();

/*
    int format = 1;

    InputMode(&format);

    if (format == 1)
    {
        Usual();
    }

    else
    {
        UniTest();
    }
*/
    return 0;
}
