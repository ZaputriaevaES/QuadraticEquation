#include "head.h"

/**
    \brief Выяснение типа уравнения
    {По значению коэффицента a функция определяет, является оно линейным или квадратным}
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void SquareSolver(double a, double b , double c, struct solutions * answers)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (DoubleComparison(a, 0) == 0)
    {
        answers->type = LINEAR; // является линейным
        linearEquation(b, c, answers);
    }

    else // a != 0
    {
        answers->type = QUADRATIC; // является квадратным
        QuadraticEquation(a, b, c, answers);
    }
}

/**
    \brief Решение линейного уравнения
    {Функция решает различные типы линейных уравнений и записывает полученные данные в структуру answers}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void linearEquation(double b , double c, struct solutions * answers)
{
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (DoubleComparison(b, 0) == 0)
    {
        if (DoubleComparison(c, 0) == 0)
        {
            answers->amount = INF; // бесконечное количество решений
        }
        else // c != 0
        {
            answers->amount = ZERO; // не имеет смысла
        }
    }
    else // b != 0
    {
        if (DoubleComparison(c, 0) == 0)
        {
            answers->amount = ONE;
            answers->answer1 = 0;
        }
        else // c != 0
        {
            answers->amount = ONE;
            answers->answer1 = (-1 * c) / b;
        }
    }
}

/**
    \brief Решение квадратного уравнения
    {Функция решает различные типы квадратных уравнений и записывает полученные данные в структуру answers}
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void QuadraticEquation(double a, double b , double c, struct solutions * answers)
{
    assert(DoubleComparison(a, 0) != 0);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (DoubleComparison(c, 0) == 0)
    {
        if (DoubleComparison(b, 0) == 0)
        {
            answers->amount = ONE;
            answers->answer1= 0;
        }
        else // b != 0
        {
            answers->amount = TWO;
            answers->answer1 = 0;
            answers->answer2 = (-1 * b) / a;
        }
    }
    else // c != 0
    {
        double D = b * b - 4 * a * c; //значение дискриминанта
        if (DoubleComparison(D, 0) == -1) //решений нет
        {
            answers->amount = ZERO;
        }
        else if (DoubleComparison(D, 0) == 0) //одно решение
        {
            answers->amount = ONE;
            answers->answer1 = ((-1) * b) / (2 * a);
        }
        else //два решения
        {
            double d = sqrt(D);
            answers->amount = TWO;
            double x1 = ((-1) * b + d) / (2 * a);
            double x2 = ((-1) * b - d) / (2 * a);

            assert(DoubleComparison(x1, x2) != 0);

            answers->answer1 = min(x1, x2);
            //(x1 < x2) ? x1 : x2;
            answers->answer2 = max(x1, x2);
            //(x1 > x2) ? x1 : x2;
        }
    }
}
