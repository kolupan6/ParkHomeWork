//#include "stdafx.h"
#include <string>
#include <iostream>
const int k = 256;
using namespace std;
void bucketSort(string * strings, int n, int * c, int symb){
	for (int i = 0; i < k; i++)
		c[i] = 0;
	for (int i = 0; i < n; i++)//раскидываем по корзинам 
		c[strings[i][symb]]++;

	int sum = 0;
	for (int i = 0; i < k; i++) {//приоритет строк по кол-ву символов
		int tmp = c[i];
		c[i] = sum;
		sum += tmp;
	}

	string * b = new string[n];
	for (int i = 0; i < n; i++) {
		b[c[strings[i][symb]]++] = strings[i];
	}
	for (int i = 0; i < n; i++)
		strings[i] = b[i];

	delete[] b;
}

void MSDSort(string * strings, int n, int symb) {
	if (n <= 1)
		return;

	int * c = new int[k + 1];
	c[k] = n - 1;//чтоб не выйти за конец массива

	bucketSort(strings, n, c, symb);

	for (int i = 1; i < k; i++)
		MSDSort(strings + c[i], c[i + 1] - c[i], symb + 1);// вызываем для следующей "корзины" символа

	delete[] c;
}
int main() {
	int n = 0;
	string * strings = new string[100001];

	while (!cin.eof()) {
		getline(cin, strings[n++]);
			if (strings[n - 1].empty()) {
				n--;
				break;
			}
	}

	MSDSort(strings, n, 0);

	for (int i = 0; i < n-1; i++)
		cout << strings[i] << '\n';
		cout << strings[n-1];

	delete[] strings;
	return 0;
}
