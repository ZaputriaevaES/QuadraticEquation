#include "head.h"

/**
    \brief ��������� ���� ���������
    {�� �������� ����������� a ������� ����������, �������� ��� �������� ��� ����������}
    @param [in] a {a - ���������� ���������}
    @param [in] b {b - ���������� ���������}
    @param [in] c {c - ���������� ���������}
    @param [out] answers {struct solutions * answers - ��������� �� ���������, ���������� ���������� �� ���������}
    \return {������}
*/
void SquareSolver(double a, double b , double c, struct solutions * answers)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (DoubleComparison(a, 0) == 0)
    {
        answers->type = LINEAR; // �������� ��������
        linearEquation(b, c, answers);
    }

    else // a != 0
    {
        answers->type = QUADRATIC; // �������� ����������
        QuadraticEquation(a, b, c, answers);
    }
}

/**
    \brief ������� ��������� ���������
    {������� ������ ��������� ���� �������� ��������� � ���������� ���������� ������ � ��������� answers}
    @param [in] b {b - ���������� ���������}
    @param [in] c {c - ���������� ���������}
    @param [out] answers {struct solutions * answers - ��������� �� ���������, ���������� ���������� �� ���������}
    \return {������}
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
            answers->amount = INF; // ����������� ���������� �������
        }
        else // c != 0
        {
            answers->amount = ZERO; // �� ����� ������
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
    \brief ������� ����������� ���������
    {������� ������ ��������� ���� ���������� ��������� � ���������� ���������� ������ � ��������� answers}
    @param [in] a {a - ���������� ���������}
    @param [in] b {b - ���������� ���������}
    @param [in] c {c - ���������� ���������}
    @param [out] answers {struct solutions * answers - ��������� �� ���������, ���������� ���������� �� ���������}
    \return {������}
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
        double D = b * b - 4 * a * c; //�������� �������������
        if (DoubleComparison(D, 0) == -1) //������� ���
        {
            answers->amount = ZERO;
        }
        else if (DoubleComparison(D, 0) == 0) //���� �������
        {
            answers->amount = ONE;
            answers->answer1 = ((-1) * b) / (2 * a);
        }
        else //��� �������
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
