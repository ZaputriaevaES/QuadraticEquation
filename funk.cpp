#include "head.h"


void Help(void)
{
    printf("���� �� ������ ������ ���������� ��������� � ������� ������, �� ������� -u, ���� ������ ������������, �� -t");
}

void InputMode (int * format)
{
    assert(format != NULL);

    printf("���� �� ������ ������ ���������� ��������� � ������� ������, �� ������� 1, ���� ������ ������������, �� 2: ");

    int a = scanf("%d", format);

    while (a != 1 || (*format != 1 && *format != 2))
    {
        InputCleaning();
        printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
        a = scanf("%d", format);
    }
}

/**
    \brief ������� ��� ������� ����������� ��������� � ������� ������
    @param [in] a {a - ���������� ���������}
    @param [in] b {b - ���������� ���������}
    @param [in] c {c - ���������� ���������}
    \return {������}
*/
void Usual(void)
{
    int input = 1, output = 1;
    InputAndOutputFormat(&input, &output);

    FILE * read = stdin;
    if (input == 2)
    {
        read = fopen("read.txt", "r");
        if (read == NULL)
        {
            printf("\n������!!! ���� read.txt �� ��� ������.\n");
            abort();
        }
    }

    OutputFormat(input, output);

    struct solutions answers = {LINEAR, ZERO, NAN, NAN};

    double a = NAN, b = NAN, c = NAN;

    while(fscanf(read, "%lg%lg%lg", &a, &b, &c) == 3)
        {
            SquareSolver(a, b, c, &answers);
            DerivationOfDecisions(a, b, c, output, &answers);
            if (input == 1)
                printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }
}

/**
    \brief ��������� ������� �����/������
    {������� ���������� � ������������, � ����� ������� ����� ����������� ���� � �����.
    ��� �� ������� ��������� ������������ ��������� ����������� ��������� ������
    � ������� ������� InputAndOutputFormat}
    @param [out] *input {��������� �� ����������, ���������� ���������� � ������� �����}
    @param [out] *output {��������� �� ����������, ���������� ���������� � ������� ������}
    \return {������}
*/
void InputAndOutputFormat(int * input, int * output)
{
    assert(input != NULL);
    assert(input != NULL);

    printf("\n������������, ��� ��������� ������ ���������� ��������� ����: a * x^2 + b * x + c = 0.\n\n"
    "���� �� ������ ������� ������ � ����������, �� ������� 1, ���� ��������� �� �����, �� 2: ");

    int w = scanf("%d", input);

    while (w != 1 || (*input != 1 && *input != 2))
    {
        if (InputCleaning() == 0)
        {
            printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
            w = scanf("%d", input);
        }
        else
            *input = 1;
    }

    printf("�������!\n"
           "���� �� ������ �������� ������ �� �����, �� ������� 1, ���� ���������� � ����, �� 2: ");

    int v = scanf("%d", output);

    while (v != 1 || (*output != 1 && *output != 2))
    {
        if (InputCleaning() == 0)
        {
            printf(" �� �������� ���������� ���������. ����� ������������, � ������� 1 ��� 2: ");
            v = scanf("%d", output);
        }
        else
            *output = 1;
    }
}

/**
    \brief �������� �������� ������
    {������� ���������, � ����� ������� ����������� �� ������� ������ �������}
    \return {������}
*/
int InputCleaning(void)
{
    int ch;
    while ((ch = getchar()) != '\n')
        {
        if (ch == EOF)
            return 1;
        putchar(ch);
        }
    return 0;
}

/**
    {������� �� ����� ��������� ������ �����/������, � ���� ����� ���������� ������������ �� ����}
    @param input {����������, ���������� ���������� � ������� �����}
    @param output {����������, ���������� ���������� � ������� ������}
    \return {������}
*/
void OutputFormat(int input, int output)
{
    assert(input  == 1 || input  == 2);
    assert(output == 1 || output == 2);

    if(input == 1)
    {
        if(output == 1) //���� � ����������, ����� �� �����
        {
            printf("\n�� �������� ������� ������ � ���������� � �������� ������ �� ������.\n\n");
            printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }
        else //���� � ����������, ����� � ����
        {
            printf("\n�� �������� ������� ������ � ���������� � �������� ������ � ���� write.txt, ������� ��������� �������������.\n\n");
            printf("������� ��� ����������� ����������� ��������� a, b, c ��� q ��� ���������� ���������:");
        }

    }
    else
    {
        printf("\n������ ���� ������� ������!\n");
        if(output == 1) //���� �� �����, ����� �� �����
        {
            printf("��������� ����� ��������� ������ �� ����� read.txt � �������� ������ �� �����.\n\n");
        }
        else //���� �� �����, ����� � ����
        {
            printf("��������� ����� ��������� ������ �� ����� read.txt � ���������� ������ � ���� write.txt,\n"
                    "������� ��������� �������������.\n");
        }
    }
}

/**
    \brief ��������� ���� ����� � ��������� �������
    {��� ������� ���������� ��� ������� ����� � �������� 0.0000001}
    @param [in] a {a - ������ ����� � ��������� �������}
    @param [in] b {b - ������ ����� � ��������� �������}
    \return {0, ���� ����� �����
            1, ���� ������ ����� ������ �������
            -1, ���� ������ ����� ������ �������}
*/
int DoubleComparison(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    const double FAULT = 0.0001;
    if (fabs(a - b) <= FAULT)
        return 0;
    else if ((a - b) > FAULT)
        return 1;
    else
        return -1;
}

/**
    \brief ����� ������� � ������ �������
    {�� �������� ��������� output ������� ����������, � ����� ������� ������ ���������� ������ �� ���������,
    ���������� � ��������� answers}
    @param [out] a {a - ���������� ���������}
    @param [out] b {b - ���������� ���������}
    @param [out] c {c - ���������� ���������}
    @param [out] output {output - ���������� ���������}
    @param [out] answers {struct solutions * answers - ��������� �� ���������, ���������� ���������� �� ���������}
    \return {������}
*/
void DerivationOfDecisions(double a, double b , double c, int outputformat, struct solutions * answers)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (outputformat == 1) // ����� �� �����
    {
        if(answers->type == LINEAR) // ��������
        {
            if(answers->amount == INF)
            {
                printf("��������� ����: 0 * x^2 + 0 * x = 0 ����� ����������� ���������� �������.\n\n");
            }
            else if(answers->amount == ZERO)
            {
                printf("��������� ����: %.3lg = 0 �� ����� �������.\n\n", c);
            }
            else if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("��������� ����: %.3lg * x = 0 ����� ������������ ������� ������ 0.\n\n", b);
            }
            else
            {
                printf("��������� ����� ���: %.3lg * x + %.3lg = 0 � �������� ��������.\n"
                       "�������� ����� ��������� �������: %.3lg.\n\n", b, c, answers->answer1);
            }
        }
        else // ����������
        {
            if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("��������� ����: %.3lg * x^2 = 0 ����� ������������ ������� ������ 0.\n\n", a);
            }
            else if(answers->amount == TWO && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("��������� ����� ���: %.3lg * x^2 + %.3lg * x = 0\n"
                    "� ��� ��������� ��������: 0, %.3lg.\n\n", a, b, answers->answer2);
            }
            else
            {
                printf("��������� ����� ���: %.3lg * x^2 + %.3lg * x + %.3lg = 0 � �������� ����������.\n", a, b, c);
                if (answers->amount == ZERO)
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� �� ����� �������.\n\n");
                }
                else if (answers->amount == ONE) //���� �������
                {
                    printf("�.�. �������� ������������� ����� 0,\n"
                           "��� ��������� ����� ���� �������, ������: %.3lg.\n\n", answers->answer1);
                }
                else
                {
                    printf("�.�. �������� ������������� ������ 0,\n"
                           "��� ��������� ����� ��� �������, ������: %.3lg, %.3lg.\n\n",
                           answers->answer1, answers->answer2);
                }
            }
        }
    }
    else // ����� � ����
    {
        FILE * write;
        write = fopen("write.txt", "a");
        if(answers->amount == INF || answers->amount == ZERO)
        {
            fprintf(write, "%d\n", answers->amount);
        }
        else if(answers->amount == ONE)
        {
             fprintf(write, "1 : %.3lg\n", answers->answer1);
        }
        else
        {
             fprintf(write, "2 : %.3lg %.3lg\n", answers->answer1, answers->answer2);
        }
    }
}
