// 如果 READLINE_H 被使用過了，就會直接跳到 #endif，
// 結束這個 readline
#ifndef READLINE_H
#define READLINE_H

// read_line: Skips leading white-space characters, then
//            reads the remainder of the input line and 
//            stores it in str. Truncates the line if its
//            length exceeds n. Returns the number of
//            characters stored.
int read_line(char str[], int n);

#endif
