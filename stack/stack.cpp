#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 4096
typedef struct stack {
	char arr[MAX];
	int top;
}Stack;

void push(Stack *s, char data)
{
	if ( !s || s->top >= MAX )
	{
		return;
	}

	s->arr[s->top] = data;
	(s->top)++;
}

char pop(Stack *s)
{
	char val = 0;
	if ( !s || s->top <= 0 )
	{
		return NULL;
	}

	(s->top)--;
	val = s->arr[s->top];
	s->arr[s->top] = 0;

	return val;
}

bool Check(char *buffer, int size, Stack *sData, int *cnt)
{
	int i = 0;
	char buf;

	for (i = 0; i < size; i++)
	{
		buf = buffer[i];
		switch (buf)
		{
			case '(':
			case '[':
			case '{':
				{
					if (!sData)
					{
						return false;
					}

					push(sData, buf);
					break;
				}
			case ')':
			case ']':
			case '}':
				{
					char popData = pop(sData);
					if ( !popData ) 
					{
						return false;
					} 

					if ( (popData == '(' && buf == ')') || (popData == '[' && buf == ']') || (popData == '{' && buf == '}')  )
					{
						*cnt++;
						break;
					} 

					return false;
				}
		}
	}
	return true;
}

int main(void)
{
	Stack s;
	memset(&s.arr, '\0', sizeof(s.arr));
	s.top = 0;

	int size = 0;
	int posLine = 0;
	int successCnt = 0;
	bool isSuccess = true;
	char buffer[MAX] = { 0, };

	/* OS is Unix */
	FILE *fp = fopen("./test1.txt", "r");
	if ( !fp )
	{
		printf("No file\n");
		return 0;
	}

	while( !feof(fp) && isSuccess )
	{
		memset(&buffer, 0, sizeof(buffer));
		fread(buffer, sizeof(buffer) - 1, 1, fp);
		isSuccess = Check(buffer, size, &s, &successCnt);
		posLine++;
	} 
	fclose(fp);

	if ( !isSuccess )
	{
		printf("%d line fail \n", posLine);
		return 0;
	}
		
	printf("%d times correct matching \n", successCnt);

	return 0;
}
