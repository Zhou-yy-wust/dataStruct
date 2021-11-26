#include"Apply_Stack.h"

bool Parentheses_Matching(char* s, int n) {
	bool ret;
	char c;
	Stack stack;
	for (int i = 0; i != n; i++) {
		switch (s[i]) {
			//左括号入栈
		case '(':
		case'[':
		case'{':
			stack.Push(s[i]);
			break;
			//右括号则出栈顶元素
		case')':
			if (!stack.Pop(c) || c != '(')  //弹出失败或栈顶元素与右括号不匹配
				return false;
			break;
		case']':
			if (!stack.Pop(c) || c != '[')
				return false;
			break;
		case'}':
			if (!stack.Pop(c) || c != '{')
				return false;
			break;
			//非法字符
		default:std::cout << "Program error" << std::endl;
			return false;
		}
	}
	return true;
}

int Get_Priority(char c) {
	switch (c) {
	case'(':
		return 3;
	case')':
		return 0;
	case'+':
	case'-':
		return 1;
	case'*':
	case'/':
		return 2;
	}
}

bool IS_Prior(char stack_top, char now) { return Get_Priority(stack_top) - Get_Priority(now) >= 0; }
void print(char* s, int n) {
	for (int i = 0; i != n; i++)
		std::cout << s[i] << " ";
	std::cout << std::endl;
}
bool Infix2Postfix(char* expression, int n) {
	Stack Operator;
	char* postfix_exp = new char[n];
	int ptr = 0;
	for (int i = 0; i != n; i++) {
		if (isalnum(expression[i]))  //数字
			postfix_exp[ptr++] = expression[i];
		else {
			if (Operator.IsEmpty() && expression[i] != ')') //栈空，直接入栈
				Operator.Push(expression[i]);
			else if (!Operator.IsEmpty() && expression[i] != ')') {  //栈非空，比较栈顶与当前操作符
				char temp;
				Operator.GetTop(temp);
				if (!IS_Prior(temp, expression[i]) || temp == '(') //栈顶操作符优先级低
					Operator.Push(expression[i]);
				else {   //弹出栈顶所有优先级较高运算符,但除了左括号
					while (IS_Prior(temp, expression[i])) {
						Operator.Pop(temp);
						postfix_exp[ptr++] = temp;
						if (!Operator.GetTop(temp)) //栈空
							break;
					}
					Operator.Push(expression[i]);
				}
			}
			else { //当前运算符为右括号
				char temp = 'p'; //任意初值
				while (Operator.Pop(temp) && temp != '(')
					postfix_exp[ptr++] = temp;
				if (temp != '(')  //栈中无左括号
					return false;
			}
		}
	}
	while (!Operator.IsEmpty()) { //清空栈
		char temp;
		Operator.Pop(temp);
		postfix_exp[ptr++] = temp;
	}
	print(postfix_exp, ptr);
	return true;
}