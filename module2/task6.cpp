/*
Напишите функцию поиска первого вхождения шаблона в текст. В качестве первого параметра функция принимает текст
(C-style строка), в которой нужно искать шаблон. В качестве второго параметра строку-шаблон (C-style строка), которую
нужно найти. Функция возвращает позицию первого вхождения строки-шаблона, если он присутствует в строке (помните, что
в C++ принято считать с 0), и -1, если шаблона в тексте нет.

Учтите, что пустой шаблон (строка длины 0) можно найти в любом месте текста.

Требования к реализации: при выполнении данного задания вы можете определять любые вспомогательные функции, если они
вам нужны. Вводить или выводить что-либо не нужно. Реализовывать функцию main не нужно.
*/

#include <stdio.h>

int strstr(const char *text, const char *pattern) {
    if (*pattern == 0) {
        return 0;
    }

    bool suppose = false;
    int pos = -1, cur_pat_inx = 0, i = 0;

    for (; text[i] != '\0'; i++) {
        if (suppose && pattern[cur_pat_inx] == '\0') {
            return pos;
        } else if (text[i] == pattern[cur_pat_inx]) {
            suppose = true;
            cur_pat_inx++;
            if (pos < 0) {
                pos = i;
            }
        } else if(suppose && text[i] != pattern[cur_pat_inx]) {
            suppose = false;
            cur_pat_inx = 0;
            pos = -1;
            i--;
        }
    }

    if (suppose && pattern[cur_pat_inx] == '\0') {
        return pos;
    }

    return -1;
}

int main() {
    char s[] = "Hey hhello, What do you think about c++?";
    char p1[] = "c++";
    char p2[] = "What";
    char p3[] = "he";
    char p4[] = "your";
    char p5[] = "you";
    char p6[] = "?";
    char p7[] = "o";
    char p8[] = "";
    char p9[] = "c++!";
    char p10[] = "hello";
    char p11[] = "c++?!";
    printf("String : %s\n", s);
    printf("Pattern 1: %s | Pos: %d\n", p1, strstr(s, p1));
    printf("Pattern 2: %s | Pos: %d\n", p2, strstr(s, p2));
    printf("Pattern 3: %s | Pos: %d\n", p3, strstr(s, p3));
    printf("Pattern 4: %s | Pos: %d\n", p4, strstr(s, p4));
    printf("Pattern 5: %s | Pos: %d\n", p5, strstr(s, p5));
    printf("Pattern 6: %s | Pos: %d\n", p6, strstr(s, p6));
    printf("Pattern 7: %s | Pos: %d\n", p7, strstr(s, p7));
    printf("Pattern 8: %s | Pos: %d\n", p8, strstr(s, p8));
    printf("Pattern 9: %s | Pos: %d\n", p9, strstr(s, p9));
    printf("Pattern 10: %s | Pos: %d\n", p10, strstr(s, p10));
    printf("Pattern 11: %s | Pos: %d\n", p11, strstr(s, p11));
}