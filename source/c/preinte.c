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

#define _CRT_SECURE_NO_WARNINGS
#include "preinte.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define TRUE  1
#define FALSE 0
#define _MACRO_STR(_MACRO_) #_MACRO_
#define _MIN(_X_, _Y_) ((_X_) < (_Y_) ? (_X_) : (_Y_))
#define _MAX(_X_, _Y_) ((_X_) > (_Y_) ? (_X_) : (_Y_))
#define _POSITIVE_CEIL(_NUM_A_, _NUM_B_) ((_NUM_A_) / (_NUM_B_) + (((_NUM_A_) % (_NUM_B_) > 0) ? 1 : 0))
#define _SET_SIZE(_VARIBLE_, _CAN_BE_ZERO_) (size_t _Len) { if (_CAN_BE_ZERO_ || _Len > 0) { _VARIBLE_ = _Len; } }
#define _PRINT_VALUE(_TYPE_, _STDIO_CODE_, _DIGITS_, _FORMAT_STR_) (_TYPE_* _Ptr, const char* _Name) { \
	printf("@%p " _MACRO_STR(_TYPE_) " %s = " _FORMAT_STR_, _Ptr, _Name); \
	char result[32] = { 0 }; \
	value_format(result, _STDIO_CODE_, 0, _DIGITS_); \
	printf(result, *_Ptr); \
	printf(_FORMAT_STR_ "\n"); \
}
#define _ARRAY_SPLITER(_LEFT_, _ID_SPLITER_, _MIDDLE_, _RIGHT_) (size_t _Count, size_t _Width, int _Is_Arr2) { \
	printf((_Count > 1 && !_Is_Arr2) ? (_LEFT_ "───────" _ID_SPLITER_) : (_LEFT_ "───" _ID_SPLITER_)); \
	for (size_t count = 0; count < _Count; count++) { \
		for (size_t len = 0; len < _Width; len++) { \
			printf("─"); \
		} \
		printf(count < _Count - 1 ? _MIDDLE_ : _RIGHT_); \
	} \
	putchar('\n'); \
}
#define _PRINT_ARRAY(_TYPE_, _STDIO_CODE_, _LENGTH_, _WIDTH_, _DIGITS_) (_TYPE_* _Ptr, size_t _Len, const char* _Name) { \
	printf("@%p "_MACRO_STR(_TYPE_) " %s[%zd]:\n", _Ptr, _Name, _Len); \
	upper_spliter(_MIN(_Len, _LENGTH_), _WIDTH_, FALSE); \
	size_t rows = _POSITIVE_CEIL(_Len, _LENGTH_); \
	for (size_t row = 0; row < rows; row++) { \
		print_id(row * _LENGTH_, _MIN(_Len - 1, (row + 1) * _LENGTH_ - 1), (_LENGTH_ == 1) ? 3 : 7); \
		for (size_t ptr = 0; ptr < _LENGTH_; ptr++) { \
			if (row * _LENGTH_ + ptr < _Len) { \
				char result[32] = { 0 }; \
				value_format(result, _STDIO_CODE_, _WIDTH_, _DIGITS_); \
				printf(result, _Ptr[row * _LENGTH_ + ptr]); \
				printf("│"); \
			} \
			else if (rows > 1) { \
				put_chars(' ', _WIDTH_); \
				printf("│"); \
			} \
		} \
		putchar('\n'); \
		row < rows - 1 ? median_spliter(_LENGTH_, _WIDTH_, FALSE) : lower_spliter(_MIN(_Len, _LENGTH_), _WIDTH_, FALSE);\
	} \
}
#define _PRINT_ARRAY2(_TYPE_, _STDIO_CODE_, _LENGTH_, _WIDTH_, _DIGITS_) (_TYPE_** _Ptr, size_t _Row, size_t _Col, const char* _Name) { \
	printf("@%p " _MACRO_STR(_TYPE_) " %s[%zd][%zd]:\n", _Ptr, _Name, _Row, _Col); \
	for (size_t charts_c = 0; charts_c < _POSITIVE_CEIL(_Col, _LENGTH_); charts_c++) { \
		size_t end_c = _MIN((charts_c + 1) * _LENGTH_, _Col); \
		size_t len   = _MIN(_Col - charts_c * _LENGTH_, _LENGTH_); \
		for (size_t charts_r = 0; charts_r < _POSITIVE_CEIL(_Row, _Max_rows); charts_r++) { \
			upper_spliter2(len, _WIDTH_, TRUE); \
			printf("│ \\ │"); \
			for (size_t col = charts_c * _LENGTH_; col < end_c; col++) { \
				print_center_id(col, _WIDTH_, TRUE); \
				printf("│"); \
			} \
			printf("\n├───╆"); \
			for (size_t col = charts_c * _LENGTH_; col < end_c; col++) { \
				for (size_t width = 0; width < _WIDTH_; width++) { \
					printf("━"); \
				} \
				printf(col < end_c - 1 ? "┿" : "┥\n"); \
			} \
			size_t end_r = _MIN((charts_r + 1) * _Max_rows, _Row); \
			for (size_t row = charts_r * _Max_rows; row < end_r; row++) { \
				printf("│"); \
				print_center_id(row, 3, TRUE); \
				printf("┃"); \
				for (size_t col = charts_c * _LENGTH_; col < end_c; col++) { \
					char result[32] = { 0 }; \
					value_format(result, _STDIO_CODE_, _WIDTH_, _DIGITS_); \
					printf(result, *((_TYPE_*)_Ptr + row * _Col + col)); \
					printf("│"); \
				} \
				putchar('\n'); \
				row < end_r - 1 ? median_spliter(len, _WIDTH_, TRUE) : lower_spliter(len, _WIDTH_, TRUE); \
			} \
		} \
	} \
}

size_t _Width_s  = 80;
size_t _Max_rows = -1;
size_t _Len_d    = 10, _Width_d    = 7;
size_t _Len_u    = 10, _Width_u    = 7;
size_t _Len_hd   = 10, _Width_hd   = 6;
size_t _Len_f    = 10, _Width_f    = 9,  _Digits_f  = 2;
size_t _Len_ld   = 10, _Width_ld   = 10;
size_t _Len_lf   = 10, _Width_lf   = 9,  _Digits_lf = 2;
size_t _Len_lld  = 10, _Width_lld  = 10;
size_t _Len_Lf   = 10, _Width_Lf   = 10, _Digits_Lf = 2;

void print_s(char* _Str, const char* _Name);
void print_id(size_t _Start, size_t _End, size_t _Width);
void put_chars(char _Char, size_t _Count);
void print_center_id(size_t _Id, size_t _Width, int _Is_Left);
void value_format(char* _Result, char* _Code, size_t _Length, size_t _Digits);

void print_d   _PRINT_VALUE(int, "d", 0, )
void print_u   _PRINT_VALUE(unsigned, "u", 0, )
void print_hd  _PRINT_VALUE(short, "hd", 0, )
void print_c   _PRINT_VALUE(char, "c", 0, "'")
void print_f   _PRINT_VALUE(float, "f", _Digits_f, )
void print_ld  _PRINT_VALUE(long, "ld", 0, )
void print_lf  _PRINT_VALUE(double, "lf", _Digits_lf, )
void print_Lf  _PRINT_VALUE(long double, "Lf", _Digits_Lf, )
void print_lld _PRINT_VALUE(long long, "lld", 0, )

void upper_spliter  _ARRAY_SPLITER("┌", "┰", "┬", "┐")
void upper_spliter2 _ARRAY_SPLITER("┌", "┬", "┬", "┐")
void lower_spliter  _ARRAY_SPLITER("└", "┸", "┴", "┘")
void median_spliter _ARRAY_SPLITER("├", "╂", "┼", "┤")

void print_ad   _PRINT_ARRAY(int, "d", _Len_d, _Width_d, 0)
void print_au   _PRINT_ARRAY(unsigned, "u", _Len_u, _Width_u, 0)
void print_ahd  _PRINT_ARRAY(short, "hd", _Len_hd, _Width_hd, 0)
void print_af   _PRINT_ARRAY(float, "f", _Len_f, _Width_f, _Digits_f)
void print_ald  _PRINT_ARRAY(long, "ld", _Len_ld, _Width_ld, 0)
void print_alf  _PRINT_ARRAY(double, "lf", _Len_lf, _Width_lf, _Digits_lf)
void print_aLf  _PRINT_ARRAY(long double, "Lf", _Len_Lf, _Width_Lf, _Digits_Lf)
void print_alld _PRINT_ARRAY(long long, "lld", _Len_lld, _Width_lld, 0)

void print_ad2   _PRINT_ARRAY2(int, "d", _Len_d, _Width_d, 0)
void print_au2   _PRINT_ARRAY2(unsigned, "u", _Len_u, _Width_u, 0)
void print_ahd2  _PRINT_ARRAY2(short, "hd", _Len_hd, _Width_hd, 0)
void print_af2   _PRINT_ARRAY2(float, "f", _Len_f, _Width_f, _Digits_f)
void print_ald2  _PRINT_ARRAY2(long, "ld", _Len_ld, _Width_ld, 0)
void print_alf2  _PRINT_ARRAY2(double, "lf", _Len_lf, _Width_lf, _Digits_lf)
void print_aLf2  _PRINT_ARRAY2(long double, "Lf", _Len_Lf, _Width_Lf, _Digits_Lf)
void print_alld2 _PRINT_ARRAY2(long long, "lld", _Len_lld, _Width_lld, 0)

void set_len_d     _SET_SIZE(_Len_d, FALSE)
void set_len_u     _SET_SIZE(_Len_u, FALSE)
void set_len_hd    _SET_SIZE(_Len_hd, FALSE)
void set_len_f     _SET_SIZE(_Len_f, FALSE)
void set_len_ld    _SET_SIZE(_Len_ld, FALSE)
void set_len_lf    _SET_SIZE(_Len_lf, FALSE)
void set_len_Lf    _SET_SIZE(_Len_Lf, FALSE)
void set_len_lld   _SET_SIZE(_Len_lld, FALSE)
void set_width_d   _SET_SIZE(_Width_d, FALSE)
void set_width_u   _SET_SIZE(_Width_u, FALSE)
void set_width_ud  _SET_SIZE(_Width_hd, FALSE)
void set_width_f   _SET_SIZE(_Width_f, FALSE)
void set_width_ld  _SET_SIZE(_Width_ld, FALSE)
void set_width_lf  _SET_SIZE(_Width_lf, FALSE)
void set_width_Lf  _SET_SIZE(_Width_Lf, FALSE)
void set_width_lld _SET_SIZE(_Width_lld, FALSE)
void set_digits_f  _SET_SIZE(_Digits_f, TRUE)
void set_digits_lf _SET_SIZE(_Digits_lf, TRUE)
void set_digits_Lf _SET_SIZE(_Digits_Lf, TRUE)
void set_max_rows  _SET_SIZE(_Max_rows, FALSE)

void print_s(char* _Str, const char* _Name) {
	printf("@%p char* %s = \"%s\"\n", _Str, _Name, _Str);
}

void pause() {
	time_t now;
	now = time(NULL);
	struct tm* plocaltime = localtime(&now);
	printf("[%d/%02d/%02d %d:%02d:%02d] Program is paused. Please press 'Enter' to continue.", plocaltime->tm_year + 1900,
		plocaltime->tm_mon + 1,	plocaltime->tm_mday, plocaltime->tm_hour, plocaltime->tm_min, plocaltime->tm_sec);
	while (getchar() != '\n');
}

void print_center_id(size_t _Id, size_t _Width, int _Is_Left) {
	size_t disposed = _Id / 10;
	size_t digits   = 1;
	while (disposed) {
		digits++;
		disposed /= 10;
	}
	if (_Width < digits) {
		return;
	}
	size_t left = (_Width - digits) / 2;
	if (!(_Width % 2 && digits % 2 || !(_Width % 2) && !(digits % 2))) {
		left += _Is_Left ? 0 : 1;
	}
	put_chars(' ', left);
	printf("%zd", _Id);
	put_chars(' ', _Width - digits - left);
}

void print_id(size_t _Start, size_t _End, size_t _Width) {
	if (_Start < _End) {
		printf("│");
		print_center_id(_Start, 3, FALSE);
		putchar('-');
		print_center_id(_End, 3, TRUE);
		printf("┃");
	}
	else {
		printf("│");
		print_center_id(_Start, _Width, FALSE);
		printf("┃");
	}
}

void put_chars(char _Char, size_t _Count) {
	for (size_t count = 0; count < _Count; count++) {
		putchar(_Char);
	}
}

void value_format(char* _Result, char* _Code, size_t _Length, size_t _Digits) {
	_Result[0] = '%';
	if (_Length > 0) {
		if (_Digits < _Length && (_Code == "f" || _Code == "lf" || _Code == "Lf")) {
			sprintf(_Result + 1, "%zd.%zd%s", _Length, _Digits, _Code);
		}
		else if (_Code == "s") {
			sprintf(_Result + 1, "-%zd%s", _Length, _Code);
		}
		else {
			sprintf(_Result + 1, "%zd%s", _Length, _Code);
		}
	}
	else {
		if (_Code == "f" || _Code == "lf" || _Code == "Lf") {
			sprintf(_Result + 1, ".%zd%s", _Digits, _Code);
		}
		else {
			sprintf(_Result + 1, "%s", _Code);
		}
	}
}

void print_as(char** _Ptr, size_t _Len_Arr, size_t _Len_Str, const char* _Name) {
	printf("@%p char %s[%zd][%zd]:\n", _Ptr, _Name, _Len_Arr, _Len_Str);
	upper_spliter(1, _Width_s, TRUE);
	for (size_t row = 0; row < _Len_Arr; row++) {
		print_id(row, row, 3);
		char result[32] = { 0 };
		value_format(result, "s", _Width_s, 0);
		printf(result, (char*)_Ptr + row * _Len_Str);
		printf("│\n");
		if (row < _Len_Arr - 1) {
			median_spliter(1, _Width_s, TRUE);
		}
	}
	lower_spliter(1, _Width_s, TRUE);
}

#ifdef __cplusplus
}
#endif // __cplusplus