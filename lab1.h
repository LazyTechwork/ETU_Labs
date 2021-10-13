#ifndef ETU_LAB1_H
#define ETU_LAB1_H

#include <iostream>
#include <vector>
#include <cmath>

int lab1();

/*
 * Получение факториала с меморизацией значений (см. вектор factorials)
 */
unsigned long long fact(unsigned long long x);

/*
 * Возведение числа в степень
 */
double pow(double x, int n);

/*
 * Получение e^x
 */
double e_x(double x);

/*
 * Получение квадратного корня
 */
double sqrt(double x);

/*
 * Вычисление синуса
 */
double sin(double x);

/*
 * Вычисление косинуса
 */
double cos(double x);

/*
 * Вычисление арктангенса
 */
double atg(double x);

#endif
