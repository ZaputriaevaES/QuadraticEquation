#include "head.h"


void Help(void)
{
    printf("Если вы хотите решать квадратное уравнение в обычном режиме, то введите -u, если начать тестирование, то -t");
}

void InputMode (int * format)
{
    assert(format != NULL);

    printf("Если вы хотите решать квадратное уравнение в обычном режиме, то введите 1, если начать тестирование, то 2: ");

    int a = scanf("%d", format);

    while (a != 1 || (*format != 1 && *format != 2))
    {
        InputCleaning();
        printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
        a = scanf("%d", format);
    }
}

/**
    \brief Функция для решения квадратного уравнения в обычном режиме
    @param [in] a {a - коэффицент уравнения}
    @param [in] b {b - коэффицент уравнения}
    @param [in] c {c - коэффицент уравнения}
    \return {ничего}
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
            printf("\nОШИБКА!!! Файл read.txt не был найден.\n");
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
                printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }
}

/**
    \brief Выяснение формата ввода/вывода
    {Функция спращивает у пользователя, в каком формате будет происходить ввод и вывод.
    Так же функция позволяет пользователю исправить неправильно введенные данные
    с помощью функции InputAndOutputFormat}
    @param [out] *input {указатель на переменную, содержащую информацию о формате ввода}
    @param [out] *output {указатель на переменную, содержащую информацию о формате вывода}
    \return {ничего}
*/
void InputAndOutputFormat(int * input, int * output)
{
    assert(input != NULL);
    assert(input != NULL);

    printf("\nЗдравствуйте, эта программа решает квадратное уравнение вида: a * x^2 + b * x + c = 0.\n\n"
    "Если вы хотите вводить данные с клавиатуры, то введите 1, если считывать из файла, то 2: ");

    int w = scanf("%d", input);

    while (w != 1 || (*input != 1 && *input != 2))
    {
        if (InputCleaning() == 0)
        {
            printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
            w = scanf("%d", input);
        }
        else
            *input = 1;
    }

    printf("Отлично!\n"
           "Если вы хотите выводить данные на экран, то введите 1, если записывать в файл, то 2: ");

    int v = scanf("%d", output);

    while (v != 1 || (*output != 1 && *output != 2))
    {
        if (InputCleaning() == 0)
        {
            printf(" не является допустимым значением. Будте внимательнее, и введите 1 или 2: ");
            v = scanf("%d", output);
        }
        else
            *output = 1;
    }
}

/**
    \brief Очишение входного потока
    {Функция считывает, а затем выводит оставленные во входном потоке символы}
    \return {ничего}
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
    {Выводит на экран выбранный формат ввода/вывода, и если нужно приглашает пользователя на ввод}
    @param input {переменная, содержащая информацию о формате ввода}
    @param output {переменная, содержащая информацию о формате вывода}
    \return {ничего}
*/
void OutputFormat(int input, int output)
{
    assert(input  == 1 || input  == 2);
    assert(output == 1 || output == 2);

    if(input == 1)
    {
        if(output == 1) //ввод с клавиатуры, вывод на экран
        {
            printf("\nВы будетете вводить данные с клавиатуры и получать ответы на экране.\n\n");
            printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }
        else //ввод с клавиатуры, вывод в файл
        {
            printf("\nВы будетете вводить данные с клавиатуры и получать ответы в файл write.txt, который создастся автоматически.\n\n");
            printf("Введите три коэффицента квадратного уравнения a, b, c или q для завершения программы:");
        }

    }
    else
    {
        printf("\nНужный файл успешно найден!\n");
        if(output == 1) //ввод из файла, вывод на экран
        {
            printf("Программа будет считывать данные из файла read.txt и выводить ответы на экран.\n\n");
        }
        else //ввод из файла, вывод в файл
        {
            printf("Программа будет считывать данные из файла read.txt и записывать ответы в файл write.txt,\n"
                    "который создастся автоматически.\n");
        }
    }
}

/**
    \brief Сравнение двух чисел с плавающей запятой
    {Эта функция сравнивает два дробных числа с точность 0.0000001}
    @param [in] a {a - первое число с плавающей запятой}
    @param [in] b {b - второе число с плавающей запятой}
    \return {0, если числа равны
            1, если первое число больше второго
            -1, если второе число больше первого}
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
    \brief Вывод решений в нужном формате
    {По значению параметра output функция определяет, в каком формате должны выводиться данные об уравнении,
    хранящиеся в структуре answers}
    @param [out] a {a - коэффицент уравнения}
    @param [out] b {b - коэффицент уравнения}
    @param [out] c {c - коэффицент уравнения}
    @param [out] output {output - коэффицент уравнения}
    @param [out] answers {struct solutions * answers - указатель на структуру, содержащую информацию об уравнении}
    \return {ничего}
*/
void DerivationOfDecisions(double a, double b , double c, int outputformat, struct solutions * answers)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(answers != NULL);

    if (outputformat == 1) // вывод на экран
    {
        if(answers->type == LINEAR) // линейное
        {
            if(answers->amount == INF)
            {
                printf("Уравнение вида: 0 * x^2 + 0 * x = 0 имеет бесконечное количество решений.\n\n");
            }
            else if(answers->amount == ZERO)
            {
                printf("Уравнение вида: %.3lg = 0 не имеет решений.\n\n", c);
            }
            else if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение вида: %.3lg * x = 0 имеет единственное решение равное 0.\n\n", b);
            }
            else
            {
                printf("Уравнение умеет вид: %.3lg * x + %.3lg = 0 и является линейным.\n"
                       "Решением этого уравнения яляется: %.3lg.\n\n", b, c, answers->answer1);
            }
        }
        else // квадратное
        {
            if(answers->amount == ONE && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение вида: %.3lg * x^2 = 0 имеет единственное решение равное 0.\n\n", a);
            }
            else if(answers->amount == TWO && DoubleComparison(answers->answer1, 0) == 0)
            {
                printf("Уравнение имеет вид: %.3lg * x^2 + %.3lg * x = 0\n"
                    "и его решениями являются: 0, %.3lg.\n\n", a, b, answers->answer2);
            }
            else
            {
                printf("Уравнение умеет вид: %.3lg * x^2 + %.3lg * x + %.3lg = 0 и является квадратным.\n", a, b, c);
                if (answers->amount == ZERO)
                {
                    printf("Т.к. значение дискриминанта меньше 0,\n"
                           "это уравнение не имеет решений.\n\n");
                }
                else if (answers->amount == ONE) //одно решение
                {
                    printf("Т.к. значение дискриминанта равно 0,\n"
                           "это уравнение имеет одно решение, равное: %.3lg.\n\n", answers->answer1);
                }
                else
                {
                    printf("Т.к. значение дискриминанта больше 0,\n"
                           "это уравнение имеет два решения, равных: %.3lg, %.3lg.\n\n",
                           answers->answer1, answers->answer2);
                }
            }
        }
    }
    else // вывод в файл
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
