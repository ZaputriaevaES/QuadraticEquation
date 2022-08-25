#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <assert.h>

/// ���������, ������ ���� ���������
enum EquationType {
                   LINEAR = 1, ///< ��������� �� ��, ��� ��������� ��������
                   QUADRATIC = 2 ///< ��������� �� ��, ��� ��������� ����������
                   };

/// ���������, ������� ������� ����� ���������
enum NumberOfSolutions {
                        ZERO = 0, ///< ��������� �� ��, ��� ��������� ����� 0 �������
                        ONE = 1, ///< ��������� �� ��, ��� ��������� ����� 1 �������
                        TWO = 2, ///< ��������� �� ��, ��� ��������� ����� 2 �������
                        INF = -1 ///< ��������� �� ��, ��� ��������� ����� ���������� �������
                        };

struct solutions {enum EquationType type;
                  enum NumberOfSolutions amount;
                  double answer1;
                  double answer2;};

void InputMode (int * format);
void Usual(void);

//--------------------------����--------------------------------------------------------
void InputAndOutputFormat(int * input, int * output); // ��������� ������� �����/������
void InputCleaning(void); // ������� �����
void OutputFormat(int input, int output);

//--------------------------�������-----------------------------------------------------
void SquareSolver(double a, double b , double c, struct solutions *); // ��������� ���� ���������
static void linearEquation(double b , double c, struct solutions *); // ������� ��������� ���������
static void QuadraticEquation(double a, double b , double c, struct solutions *); // ������� ����������� ���������

//--------------------------�����-------------------------------------------------------
int DoubleComparison(double a, double b); // ��������� ����� � ��������� 0.0001
void DerivationOfDecisions(double a, double b , double c,int outputformat, struct solutions *); // ����� ������� � ������ �������

//--------------------------�����-------------------------------------------------------
void UniTest(void);
void Results(int n, double x1, double x2, struct solutions *, int i);


#endif // HEAD_H_INCLUDED
