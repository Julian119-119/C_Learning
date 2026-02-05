#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[], int n) {
    int ch, i = 0;

    // 在讀取之前先清除掉多餘的空白鍵, 換行 , tab 等
    // 也順便讀取字
    while (isspace(ch = getchar())) ;

    while (ch != '\n' && ch != EOF) {
        if (i < n)
          str[i++] = ch;
        // 讀取下一個 character
        ch = getchar();
    } 
    str[i] = '\0';
    return i;
}