// caulculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define CODE_PLUS 1
#define CODE_MINS 2
#define CODE_MULTI 3
#define CODE_DIVID 4
#define CODE_LEFT 8
#define CODE_RIGHT 9
#define CODE_EQUA 10
#define CODE_POWER 11
#define CODE_FACTORIA 12
#define CODE_SPACE 13
#define CODE_ROOT 14
#define MAX_FORMULA 100
#define DIGIT 1
#define OPERA 0

#define OPT_PLUS		'+'
#define OPT_MINS		'-'
#define OPT_MULTI		'*'
#define OPT_DIVID		'/'
#define OPT_LIFT		'('
#define OPT_RIGHT		')'
#define OPT_EQUA		'='
#define OPT_POWER		'^'
#define OPT_DOT			'.'
#define OPT_FACTORIA	'!'
#define OPT_SPACE		' '
#define OPT_ROOT		''

#define LEFT_PLUS 25
#define LEFT_MINS 25
#define LEFT_MULTI 35
#define LEFT_DIVID 35
#define LEFT_LIFTRACK 15
#define LEFT_RIGHTRACK 5
#define LEFT_POWER 45
#define LEFT_FACTORIA 55

#define RIGHT_PLUS 20
#define RIGHT_MINS 20
#define RIGHT_MULTI 30
#define RIGHT_DIVID 30
#define RIGHT_LIFTRACK 150
#define RIGHT_RIGHTRACK 15
#define RIGHT_POWER 40
#define RIGHT_FACTORIA 40
#define RIGHT_EQUA 1

#define LEGAL 20000
#define ILLEGAL 40000

struct QuickWay {
	char corOperator;
	int  code;
	int right;
	int left;
};

const struct QuickWay qickway[] = {
	{ OPT_PLUS	,CODE_PLUS	, RIGHT_PLUS		,LEFT_PLUS },
	{ OPT_MINS	,CODE_MINS	, RIGHT_MINS		,LEFT_MINS },
	{ OPT_MULTI	,CODE_MULTI	, RIGHT_MULTI		,LEFT_MULTI },
	{ OPT_DIVID	,CODE_DIVID	, RIGHT_DIVID		,LEFT_DIVID },
	{ OPT_LIFT	,CODE_LEFT	, RIGHT_LIFTRACK	,LEFT_LIFTRACK },
	{ OPT_RIGHT	,CODE_RIGHT	, RIGHT_RIGHTRACK	,LEFT_RIGHTRACK },
	{ OPT_EQUA	,CODE_EQUA	, RIGHT_EQUA		,    -1 },
	{ OPT_POWER	,CODE_POWER	,RIGHT_POWER		,RIGHT_POWER },
	{OPT_FACTORIA,CODE_FACTORIA,LEFT_FACTORIA,RIGHT_FACTORIA},
	{OPT_SPACE	,CODE_SPACE	, -1				,-1}
};

struct Oprline {
	int realthing;
	int realopera;
	int leftpriority;
};

struct Calcu {
	int di_op;
	double code;
	int rightprty;
};

int determine(int comein) {
	const int O = sizeof(qickway) / sizeof(struct QuickWay);
	int o;
	for (o = 0; o < O; o++)
	{
		if (qickway[o].left == comein)
		{
			return qickway[o].right;
		}
	}
}

int Convert_operator(char item) {
	const int N = sizeof(qickway) / sizeof(struct QuickWay);
	int n;
	for (n = 0; n < N; n++)
	{
		if (item == qickway[n].corOperator)
		{
			return qickway[n].code;
		}
	}
	return -1;
}
char OppoConvert_operator(int item)
{
	const int N = sizeof(qickway) / sizeof(struct QuickWay);
	int n;
	for (n = 0; n < N; n++)
	{
		if (item == qickway[n].code)
		{
			return qickway[n].corOperator;
		}
	}
	return -1;
}

int rightPriority(int code)
{
	int Try = sizeof(qickway) / sizeof(struct QuickWay);
	int ty;
	for (ty = 0; ty < Try; ty++)
	{
		if (code == qickway[ty].code)
		{
			return qickway[ty].right;
		}
	}
	return -1;
}

int leftPriority(int code)
{
	int Try = sizeof(qickway) / sizeof(struct QuickWay);
	int ty;
	for (ty = 0; ty < Try; ty++)
	{
		if (code == qickway[ty].code)
		{
			return qickway[ty].left;
		}
	}
	return -1;
}

double calculation(double numbera, char Operator, double numberb)
{
	double result;
	int e;
	double power = numbera;
	switch (Operator)
	{
	case CODE_PLUS:
		return numbera + numberb;
		break;
	case CODE_MINS:
		return numbera - numberb;
		break;
	case CODE_MULTI:
		return numbera * numberb;
		break;
	case CODE_DIVID:
		return numbera / numberb;
		break;
	case CODE_POWER:
	{
		return pow(numbera, numberb);
		break;
	}
	case CODE_FACTORIA:
	{
		int length;
		double number=1;
		if (numbera == 0)
		{
			return 0;
			break;
		}
		for (length= 1; length < numbera; length++)
		{
			number = number*(length+1);
		}
		return number;
		break;
	}
	default:
		break;
	}
}

void Cleanoperstack(struct Oprline* target, int whichone)
{
	target[whichone].leftpriority = -1;
	target[whichone].realopera = -1;
	target[whichone].realthing = -1;
	whichone--;
}

int popOP(struct Oprline* income)
{
	int output;
	int d = 0;
	if (income[d].realthing != -1)
	{
		while (income[d].realthing != -1)
		{
			d++;
		}
		d--;
	}
	output = income[d].realthing;
	Cleanoperstack(income, d);
	return output;
}

int Testimput(char income)
{
	if (income >= '0' && income <= '9')
	{
		return LEGAL;
	}
	switch (income)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':
	case'^':
	case'.':
	case'=':
	case '!':
	case ' ':
		return LEGAL;
	default:
		return ILLEGAL;
		break;
	}
}

void PushOP(int imput, struct Oprline* target)
{
	int e = 0;
	while (target[e].realthing != -1)
	{
		e++;
	}
	target[e].realthing = imput;
}

int GettopOP(struct Oprline* stack)
{
	int n = 0;
	if (stack[n].realthing != -1)
	{
		while (stack[n].realthing != -1)
		{
			n++;
		}
		n--;
	}
	else
	{
		return -1;
	}
	return stack[n].realthing;
}

double GetopDIG(double* stack)
{
	double output;
	int n = 0;
	if (stack[n] != 0)
	{
		while (stack[n] != 0)
		{
			n++;
		}
		n--;
	}
	else
	{
		return -1;
	}
	output = stack[n];
	stack[n] = 0;
	return output;
}
double PopDIG(double* stack)
{
	double output;
	int n = 0;
	if (stack[n] != -1)
	{
		while (stack[n] != -1)
		{
			n++;
		}
		n--;
	}
	else
	{
		return -1;
	}
	output = stack[n];
	stack[n] = -1;
	return output;
}

void PushDIG(double input, double* stack)
{
	int n = 0;	while (stack[n] != -1)
	{
		n++;
	}
	stack[n] = input;
}

void cleannumber(int* target, int whichone)
{
	target[whichone] = -1;
}

int main()
{
LABLE_START:
	int leftracks = 0, righracks=0;
	int cnt,loop=0;
	int stp = 0;
	double popreciver;
	double holder;
	int sni = 0, tpi = 0, lni = 0, nubcount = 0, operacount = 0;
	char imput[MAX_FORMULA];
	char temp[MAX_FORMULA];
	double numberstack[MAX_FORMULA];
	struct Oprline operatestack[MAX_FORMULA];
	struct Calcu lines[MAX_FORMULA];
	memset(temp, 0, sizeof(temp));
	for (cnt = 0; cnt < MAX_FORMULA; cnt++)
	{
		numberstack[cnt] = -1;
	}
	memset(operatestack, -1, sizeof(operatestack));
	if (loop == 0)
	{
		printf("please enter equal sign\n");
		printf("calculator will egnore anything after equal sign\nequasion :  ");
	}
	fgets(imput,MAX_FORMULA,stdin);
	if (imput[sni] >= '0' && imput[sni] <= '9'|| imput[sni] == OPT_LIFT)
	{
		
	}
	else
	{
		printf("HAVE TO START WITH NUMBER OR LEFT RACKET");
		_getch();
		return 0;
	}
	while (sni !=MAX_FORMULA)
	{
		if (imput[sni] != OPT_EQUA)
		{
			if (sni < MAX_FORMULA)
			{
				sni++;
			}
			else
			{
				printf("NEEDS EQUAL SIGN");
				_getch();
				return 0;
			}
		}
		else
		{
			sni = MAX_FORMULA;
		}
	}
	sni = 0;
	while (imput[sni] !=OPT_EQUA)
	{
		if (imput[sni] == OPT_LIFT)
		{
			leftracks++;
			sni++;
		}
		else if(imput[sni] == OPT_RIGHT)
		{
			righracks++;
			sni++;
		}
		else
		{
			sni++;
		}
	}
	if (leftracks != righracks)
	{
		printf("NEEDS SAME AMOUNT OF LEFTRACKET AND RIGHTRACKES");
		_getch();
		return 0;
	}
	sni = 0;
	while (imput[sni] !='\n')
	{
		if (Testimput( imput[sni] ) ==LEGAL)
		{
			sni++;
		}
		else
		{
			printf("UNRECOGNIZABLE EXPRESSION");
			_getch();
			return 0;
		}
	}
	sni = 0;
	while (imput[stp] != 0)
	{
		stp++;
	}
	while (imput[sni] != '\n')
	{	
		if (imput[sni] == ' ')
		{
			sni++;
		}
		else
		{
			if (imput[sni] >= '0'&& imput[sni] <= '9' || imput[sni] == '.')
			{
				temp[tpi] = imput[sni];
				sni++;
				tpi++;
			}
			else
			{
				if (temp[0] != 0)
				{
					tpi = 0;
					while (temp[tpi] != 0)
					{
						if (temp[tpi] == OPT_DOT)
						{
							if (imput[sni] == OPT_FACTORIA)
							{
								printf("HAVE TO USE INTIGER FOR FACTORIAL");
								_getch();
								return 0;
							}
							if (tpi != 0 && temp[tpi + 1] != 0)
							{

							}
							else
							{
								printf("THERE HAS TO BE THINGS INFORNT OR BEHIND A DOT");
								_getch();
								return 0;
							}
							while (temp[tpi] != 0)
							{
								if (temp[tpi + 1] != OPT_DOT)
								{
									tpi++;
								}
								else
								{
									printf("THERE CAN'T BE MULTIPLE DOTS");
									_getch();
									return 0;
								}
							}
							holder = atof(temp);
							memset(temp, 0, sizeof(temp));
							tpi = 0;
							lines[lni].code = holder;
							lines[lni].di_op = DIGIT;
							lines[lni].rightprty = rightPriority(lines[lni].code);
							lni++;
						}
						else
						{
							tpi++;
						}
					}
					if (temp[0] != 0)
					{
						holder = atof(temp);
						memset(temp, 0, sizeof(temp));
						tpi = 0;
						lines[lni].code = holder;
						lines[lni].di_op = DIGIT;
						lines[lni].rightprty = rightPriority(lines[lni].code);
						lni++;
					}
				}
				lines[lni].code = Convert_operator(imput[sni]);
				sni++;
				lines[lni].rightprty = rightPriority(lines[lni].code);
				lines[lni].di_op = OPERA;
				lni++;
			}
		}
		
	}
	lni = 0;
	while (lines[lni].code !=CODE_EQUA)
	{
		if (lines[lni].code == CODE_SPACE)
		{
			lni++;
		}
		if (lines[lni].di_op==DIGIT)
		{
			if (lines[lni].di_op == DIGIT  && lines[lni + 1].code != CODE_LEFT)
			{
				lni++;
			}
			else
			{
				printf("CAN'T PUT NUMBER INFORNT OF LEFTRACKET");
				_getch();
				return 0;
			}
		}
		else if(lines[lni].code !=CODE_RIGHT && lines[lni+1].di_op == DIGIT)
		{
			lni++;
		}					
		else if(lines[lni].code ==CODE_RIGHT && lines[lni+1].code != CODE_LEFT && lines[lni+1].di_op !=DIGIT)
		{
			lni++;
		}
		else if(lines[lni].code == CODE_LEFT && lines[lni+1].di_op == DIGIT )
		{
			lni++;
		}
		else if (lines[lni].code == CODE_FACTORIA && lines[lni+1].di_op != DIGIT && lines[lni].code !=CODE_LEFT)
		{
			lni++; 
		}
		else if (lines[lni].code !=CODE_LEFT && lines[lni+1].di_op == DIGIT)
		{
			lni++;
		}
		else if (lines[lni].code != CODE_LEFT && lines[lni + 1].code == CODE_LEFT )
		{
			lni++;
		}
		else
		{
			printf("EXPRESSION LOGIC ERROR");
			_getch();
			return 0;
		}
	}
	lni = 0;
	while (lines[lni-1].code != CODE_EQUA)
	{
		if (lines[lni].di_op == DIGIT)
		{
			printf("%f", lines[lni].code);
			lni++;
		}
		else
		{
			printf("%c", OppoConvert_operator(lines[lni].code));
			lni++;
		}
	}
	printf("\n");
	lni = 0;
	while (GettopOP(operatestack) != CODE_EQUA)
	{
		if (lines[lni].di_op == OPERA)
		{
			if (GettopOP(operatestack) != -1)
			{
			LABLE_CAUC:
				
				if (leftPriority(GettopOP(operatestack)) < lines[lni].rightprty)
				{
					PushOP(lines[lni].code, operatestack);
					lni++;
				}
				else if (leftPriority(GettopOP(operatestack)) > lines[lni].rightprty)
				{
					if (GettopOP(operatestack) == CODE_FACTORIA)
					{
						PushDIG(calculation(PopDIG(numberstack), popOP(operatestack), 0), numberstack);
					}
					else
					{
						PushDIG(calculation(PopDIG(numberstack), popOP(operatestack), PopDIG(numberstack)), numberstack);
						goto LABLE_CAUC;
					}
				}
				else
				{
					popOP(operatestack);
					lni++;
				}
			}
			else
			{
				PushOP(lines[lni].code, operatestack);
				lni++;
			}
		}
		else
		{
			PushDIG(lines[lni].code, numberstack);
			lni++;
		}
	}
	printf("%.15lf \npress c to continue\n", PopDIG(numberstack));
	if (_getch() == 'c')
	{
		goto LABLE_START;
	}
	else
	{
		return 0;
	}
}
