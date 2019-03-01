#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

char** Method(size_t strc, char **strings) {
	char *tempStr = NULL;
	char *errFlag = NULL;
	tempStr = (char*)calloc(1, sizeof(char));
	if (!tempStr) {
		return 0;
	}

	for (size_t i = 0; i < strc; ++i) {
		size_t j;
		size_t tStr_len = 0;
		//каждую строку данного массива перебираем в временную переменную, игнорируя лишние пробелы
		j = 0;
		while (strings[i][j] != '\0') {
			if (!(strings[i][j] == ' ' && strings[i][j + 1] == ' ')) {
				tStr_len++;
				errFlag = NULL;
				errFlag = (char*)realloc(tempStr, sizeof(char) * tStr_len);
				if (!errFlag) {
					return 0;
				}
				tempStr = errFlag;
				tempStr[tStr_len - 1] = strings[i][j];
			}
			j++;
		}

		tStr_len++;

		errFlag = NULL;
		errFlag = (char*)realloc(tempStr, sizeof(char) * tStr_len);
		if (!errFlag) {
			return 0;
		}

		tempStr = errFlag;
		//ставим в конце каждой строки терминальный ноль
		tempStr[tStr_len - 1] = '\0';

		errFlag = NULL;
		errFlag = (char*)realloc(strings[i], sizeof(char) * tStr_len);
		if (!errFlag) {
			return 0;
		}

		strings[i] = errFlag;
		memcpy(strings[i], tempStr, tStr_len);

		errFlag = NULL;
		errFlag = (char*)realloc(tempStr, sizeof(char));
		if (!errFlag) {
			return 0;
		}
		tempStr = errFlag;
	}
	free(tempStr);
	return strings;
}

int main(void)
{
	char *temp = NULL, 
		**strings = NULL;
	size_t count = 1;
	size_t strc = 1;

	strings = (char**)calloc(strc, sizeof(char*));
	if (!strings) {
		printf("[error]");
		return 0;
	}

	temp = (char*)malloc(sizeof(char) * count);
	if (!temp) {
		free(strings);
		printf("[error]");
		return 0;
	}

	while (1) {
		char c = 0;
		int isEOF = 0;
		//производим посимвольное чтение.
		switch (scanf("%c", &c)) {
		case EOF: isEOF = 1; break;
		case 1: break;
		default:
			free(strings);
			free(temp);
			printf("[error]");
			return 0;
		}

		if (isEOF) {
			temp[count - 1] = '\0';

			strings[strc - 1] = (char*)calloc(count, sizeof(char));
			if (!(strings[strc - 1])) {
				for (size_t i = 0; i < strc; ++i) {
					free(strings[i]);
				}
				free(strings);
				free(temp);
				printf("[error]");
				return 0;
			}
			memcpy(strings[strc - 1], temp, count);

			break;
		}
		//поскольку мы не можем саостоятельно заканчивать и начинать ввод. ставим терминальный ноль после каждой строки.
		if (c == '\n') {
			temp[count - 1] = '\0';
			strings[strc - 1] = (char*)calloc(count, sizeof(char));
			if (!(strings[strc - 1])) {
				for (size_t i = 0; i < strc; ++i) {
					free(strings[i]);
				}
				free(strings);
				free(temp);
				printf("[error]");
				return 0;
			}
			memcpy(strings[strc - 1], temp, count);
			strc++;
			count = 1;

			char **errFlag = NULL;
			errFlag = (char**)realloc(strings, sizeof(char*) * strc);
			if (!errFlag) {
				for (size_t i = 0; i < strc; ++i) {
					free(strings[i]);
				}
				free(strings);
				free(temp);
				printf("[error]");
				return 0;
			}
			strings = errFlag;
			strings[strc - 1] = NULL;
		}
		else {
			temp[count - 1] = c;
			count++;

			char *errFlag = NULL;
			errFlag = (char*)realloc(temp, sizeof(char) * count);
			if (!errFlag) {
				for (size_t i = 0; i < strc; ++i) {
					free(strings[i]);
				}
				free(strings);
				free(temp);
				printf("[error]");
				return 0;
			}
			temp = errFlag;
		}
	}

	char **errFlag = NULL;
	errFlag = Method(strc, strings);
	if (errFlag == 0) {
		for (size_t i = 0; i < strc; ++i) {
			free(strings[i]);
		}
		free(strings);
		free(temp);
		printf("[error]");
		return 0;
	}
	strings = errFlag;

	for (size_t i = 0; i < strc; ++i) {
		printf("%s\n", strings[i]);
	}

	free(temp);
	for (size_t i = 0; i < strc; ++i) {
		free(strings[i]);
	}
	free(strings);
	return 0;
}//возможно, конечно, излишне безопасно вышло.
