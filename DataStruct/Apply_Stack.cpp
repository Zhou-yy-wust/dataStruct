#include"Apply_Stack.h"

bool Parentheses_Matching(char* s, int n) {
	bool ret;
	char c;
	Stack stack;
	for (int i = 0; i != n; i++) {
		switch (s[i]) {
			//��������ջ
		case '(':
		case'[':
		case'{':
			stack.Push(s[i]);
			break;
			//���������ջ��Ԫ��
		case')':
			if (!stack.Pop(c) || c != '(')  //����ʧ�ܻ�ջ��Ԫ���������Ų�ƥ��
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
			//�Ƿ��ַ�
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
		if (isalnum(expression[i]))  //����
			postfix_exp[ptr++] = expression[i];
		else {
			if (Operator.IsEmpty() && expression[i] != ')') //ջ�գ�ֱ����ջ
				Operator.Push(expression[i]);
			else if (!Operator.IsEmpty() && expression[i] != ')') {  //ջ�ǿգ��Ƚ�ջ���뵱ǰ������
				char temp;
				Operator.GetTop(temp);
				if (!IS_Prior(temp, expression[i]) || temp == '(') //ջ�����������ȼ���
					Operator.Push(expression[i]);
				else {   //����ջ���������ȼ��ϸ������,������������
					while (IS_Prior(temp, expression[i])) {
						Operator.Pop(temp);
						postfix_exp[ptr++] = temp;
						if (!Operator.GetTop(temp)) //ջ��
							break;
					}
					Operator.Push(expression[i]);
				}
			}
			else { //��ǰ�����Ϊ������
				char temp = 'p'; //�����ֵ
				while (Operator.Pop(temp) && temp != '(')
					postfix_exp[ptr++] = temp;
				if (temp != '(')  //ջ����������
					return false;
			}
		}
	}
	while (!Operator.IsEmpty()) { //���ջ
		char temp;
		Operator.Pop(temp);
		postfix_exp[ptr++] = temp;
	}
	print(postfix_exp, ptr);
	return true;
}