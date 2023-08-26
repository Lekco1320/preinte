#pragma once
/****************************************************************************
* Author:   Lukaß Zhang
* Since:    2023/05/31
* Modifyed: 2023/08/26
* Version:  1.0.0.87
* Email:    sunny_clouds@outlook.com
*
* This version is just for C, and lacks many functions. It's crude to use, so
* I don't recommend you to apply it into your project. Please use the C++
* version with C++ compiler (>=C++14) if possible.
*
* This version can be compiled by MSVC, GCC or Clang.
*
* Copyright 2023 Lekco. All Rights Reserved.
****************************************************************************/

#ifndef _PREINTE_H_
#define _PREINTE_H_
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <time.h>

void print_d(int* _Ptr, const char* _Name);
void print_u(unsigned* _Ptr, const char* _Name);
void print_hd(short* _Ptr, const char* _Name);
void print_c(char* _Ptr, const char* _Name);
void print_s(char* _Str, const char* _Name);
void print_f(float* _Ptr, const char* _Name);
void print_lf(double* _Ptr, const char* _Name);
void print_ld(long* _Ptr, const char* _Name);
void print_lld(long long* _Ptr, const char* _Name);
void print_Lf(long double* _Ptr, const char* _Name);

void print_ad(int* _Ptr, size_t _Len, const char* _Name);
void print_au(unsigned* _Ptr, size_t _Len, const char* _Name);
void print_ahd(short* _Ptr, size_t _Len, const char* _Name);
void print_af(float* _Ptr, size_t _Len, const char* _Name);
void print_alf(double* _Ptr, size_t _Len, const char* _Name);
void print_ald(long* _Ptr, size_t _Len, const char* _Name);
void print_alld(long long* _Ptr, size_t _Len, const char* _Name);
void print_aLf(long double* _Ptr, size_t _Len, const char* _Name);
void print_as(char** _Ptr, size_t _Arr_Len, size_t _Str_Len, const char* _Name);

void print_ad2(int** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_au2(unsigned** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_ahd2(short** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_af2(float** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_ald2(long** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_alf2(double** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_aLf2(long double** _Ptr, size_t _Row, size_t _Col, const char* _Name);
void print_alld2(long long** _Ptr, size_t _Row, size_t _Col, const char* _Name);

void set_len_d(size_t _Len);
void set_len_u(size_t _Len);
void set_len_hd(size_t _Len);
void set_len_f(size_t _Len);
void set_len_ld(size_t _Len);
void set_len_lf(size_t _Len);
void set_len_Lf(size_t _Len);
void set_len_lld(size_t _Len);
void set_width_d(size_t _Len);
void set_width_u(size_t _Len);
void set_width_hd(size_t _Len);
void set_width_f(size_t _Len);
void set_width_ld(size_t _Len);
void set_width_lf(size_t _Len);
void set_width_Lf(size_t _Len);
void set_width_lld(size_t _Len);
void set_digits_f(size_t _Len);
void set_digits_lf(size_t _Len);
void set_digits_Lf(size_t _Len);
void set_max_rows(size_t _Len);

void pause();

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _PREINTE_
