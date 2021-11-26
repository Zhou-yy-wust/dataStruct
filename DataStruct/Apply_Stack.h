#pragma once
#ifndef APPLY_STACK_H
#define APPLY_STACK_H
#include"Stack.h"
typedef LinkStack Stack;

bool Parentheses_Matching(char* s, int n);

int Get_Priority(char c);

bool IS_Prior(char stack_top, char now);

void print(char* s, int n);

bool Infix2Postfix(char* expression, int n);


#endif