#include "head.h"

void UniTest(void)
{
    FILE * test = fopen("test.txt", "r");
    if (test == NULL)
        {
            printf("\nОШИБКА!!! Файл test.txt не был найден.\n");
            abort();
        }
    else
        printf("файл test.txt успешно найден\n");

    struct solutions answers = {LINEAR, ZERO, 0, 0};
    double a = NAN, b = NAN, c = NAN;
    int n = 0;
    double x1 = 0, x2 = 0;
    int i = 1;

    while(fscanf(test, "%lg%lg%lg", &a, &b, &c) == 3)
        {
            SquareSolver(a, b, c, &answers);
            fscanf(test, "%d%lg%lg", &n, &x1, &x2);
            Results(n, x1, x2, &answers, i);
            i++;
        }
}

void Results(int n, double x1, double x2, struct solutions * answers, int i)
{
    assert(isfinite(x1));
    assert(isfinite(x2));
    assert(answers != NULL);

    if ((answers->amount == -1 && n == -1)
     || (answers->amount == 0  && n == 0))
        printf("%d test is ok\n", i);

    else if(answers->amount == 1 && n == 1 && DoubleComparison(x1, answers->answer1) == 0)
        printf("%d test is ok\n", i);

    else if(answers->amount == 2 && n == 2 && DoubleComparison(x1, answers->answer1) == 0
            && DoubleComparison(x2, answers->answer2) == 0)
        printf("%d test is ok\n", i);

    else
        printf("%d test: Failed : n = %d, x1 = %lg, x2 = %lg. Expected : n = %d, x1 = %lg, x2 = %lg.\n",
               i, answers->amount, answers->answer1, answers->answer2, n, x1, x2);

}
