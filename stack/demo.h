//
// Created by 张群 on 2018/8/4.
//

#include <iostream>
#include "ArrayStack.h"

using namespace std;

const char left_1 = '[';
const char left_2 = '(';
const char left_3 = '{';
const char right_1 = ']';
const char right_2 = ')';
const char right_3 = '}';

const char ADD = '+';
const char DEL = '-';
const char MUL = '*';
const char DIV = '/';
const char DOT = '.';
const char SPACE = ' ';

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

float pow(int num, int power) {
    float result = 1;
    while (power-- > 0) {
        result = result / 10;
    }
    return result * num;
}

bool checkBrackets(string brackets) {
    char* data = brackets.data();
    int length = static_cast<int>(brackets.length());

    Stack<char>* stack = new ArrayStack<char>();
    for (int i = 0; i < length; ++i) {
        char cur = data[i];
        if (!stack->empty()) {
            char top = stack->top();
            if (top == left_1 && cur == right_1) {
                stack->pop();
            } else if (top == left_2 && cur == right_2) {
                stack->pop();
            } else if (top == left_3 && cur == right_3) {
                stack->pop();
            } else {
                stack->push(cur);
            }
        } else {
            stack->push(cur);
        }
    }

    return stack->empty();
}

float calculate(string formula) {
    char* data = formula.data();
    int length = static_cast<int>(formula.length());

    Stack<float>* stack = new ArrayStack<float>();
    for (int i = 0; i < length; ++i) {
        char c = data[i];
        if (isNum(c)) {
            float num = c - '0';
            bool isUp = true;
            int power = 0;
            while(true) {
                if (isNum((c = data[i + 1]))) {
                    if (isUp) {
                        num = num * 10 + c - '0';
                    } else {
                        num = num + pow(c - '0', power++);
                    }
                    i++;
                } else if (data[i+1] == DOT) {
                    isUp = false;
                    power = 1;
                    i++;
                }else if (data[i+1] == SPACE){
                    i++;
                    break;
                } else {
                    break;
                }
            }
            stack->push(num);
        } else {
            if (stack->length() > 1) {
                float se = stack->pop();
                float fi = stack->pop();
                switch (c) {
                    case ADD:
                        stack->push(fi + se);
                        break;
                    case DEL:
                        stack->push(fi - se);
                        break;
                    case MUL:
                        stack->push(fi * se);
                        break;
                    case DIV:
                        stack->push(fi / se);
                        break;
                    default:
                        return NULL;
                }
            }
        }
    }
    return stack->pop();
}

