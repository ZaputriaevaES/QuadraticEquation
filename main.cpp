#include "head.h"

int main(void)
{
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
    return 0;
}
