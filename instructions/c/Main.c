#define _CRT_SECURE_NO_WARNINGS 0
#include <stdio.h>
#include "preinte.h"

int main() {
	int a = 2023;
	print_d(&a, "a");
	float f = 3.14f;
	print_f(&f, "f");
	double d = 0.59;
	set_digits_lf(3);
	print_lf(&d, "d");
	long l = 0xffffff;
	print_ld(&l, "l");
	char c = 'k';
	print_c(&c, "k");
	char s[] = "ok5678";
	print_s(s, "s");
	int ints[] = { 5,6,7,8,9,10,12 };
	print_ad(ints, 7, "ints");
	double fs[] = { 5.68,6.98,7.23,8.46,9.55,10.27,12.366,569,254.2,56.4,256.4,125.2,154.2,99.2 };
	print_alf(fs, 14, "doubles");
	int ds[] = { 5,7,56,23,48,92,15,72,3,-8,-3,2,-9,-884,2,6 };
	set_len_d(5);
	print_ad(ds, 16, "nums");
	pause();
	char strs[3][64] = { 0 };
	sprintf(strs[0], " - i love you.");
	sprintf(strs[1], " - 6.");
	sprintf(strs[2], " - my life becomes meaningless.");
	print_as(strs, 3, 64, "strs");
	int test[2][12] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
	print_ad2(test, 4, 6, "test");
	long double dls[2][6] = { 5.68,6.98,7.23,8.46,9.55,10.27,12.366,569,254.2,56.4,256.4,125.2 };
	print_aLf2(dls, 2, 6, "Testing");
	pause();
}
