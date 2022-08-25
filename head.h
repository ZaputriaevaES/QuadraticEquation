#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

/// Указывает, какого типа уравнение
enum EquationType {
                   LINEAR = 1, ///< Указывает на то, что уравнение линейное
                   QUADRATIC = 2 ///< Указывает на то, что уравнение квадратное
                   };

/// Указывает, сколько решений имеет уравнение
enum NumberOfSolutions {
                        ZERO = 0, ///< Указывает на то, что уравнение имеет 0 решений
                        ONE = 1, ///< Указывает на то, что уравнение имеет 1 решение
                        TWO = 2, ///< Указывает на то, что уравнение имеет 2 решения
                        INF = -1 ///< Указывает на то, что уравнение имеет бесконечно решений
                        };

struct solutions {enum EquationType type;
                  enum NumberOfSolutions amount;
                  double answer1;
                  double answer2;};

void InputMode (int * format);
void Usual(void);

//--------------------------ВВОД--------------------------------------------------------
void InputAndOutputFormat(int * input, int * output); // выяснение формата ввода/вывода
void InputCleaning(void); // очистка ввода
void OutputFormat(int input, int output);

//--------------------------РЕШЕНИЕ-----------------------------------------------------
void SquareSolver(double a, double b , double c, struct solutions *); // выяснение типа уравнения
static void linearEquation(double b , double c, struct solutions *); // решение линейного уравнения
static void QuadraticEquation(double a, double b , double c, struct solutions *); // решение квадратного уравнения

//--------------------------ВЫВОД-------------------------------------------------------
int DoubleComparison(double a, double b); // сравнение чисел с точностью 0.0001
void DerivationOfDecisions(double a, double b , double c,int outputformat, struct solutions *); // вывод решений в нужном формате

//--------------------------ТЕСТЫ-------------------------------------------------------
void UniTest(void);
void Results(int n, double x1, double x2, struct solutions *, int i);


#endif // HEAD_H_INCLUDED
