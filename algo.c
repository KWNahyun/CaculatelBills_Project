#include <stdio.h>

int main(void)
{
    int a = 10000;
    int b = 2000;
    int c = 0;
    
    int mean = (a + b + c) / 3;
    a = mean - a;
    b = mean - b;
    c = mean - c;

    int atob = 0;
    int btoa = 0;
    int btoc = 0;
    int ctob = 0;
    int atoc = 0;
    int ctoa = 0;
    
    if (a > 0)
	{
		if (b < 0)
		{
			while (b != 0)
			{
				a--;
				b++;
				atob++;
			}
		}
		if (c < 0)
		{
			while (c != 0)
			{
				a--;
				c++;
				atoc++;
			}
		}
	}   
	
	if (b > 0)
	{
		if (a < 0)
		{
			while (a != 0)
			{
				b--;
				a++;
				btoa++;
			}
		}
		if (c < 0)
		{
			while (c != 0)
			{
				b--;
				c++;
				btoc++;
			}
		}
	}
	
	if (c > 0)
	{
		if (a < 0)
		{
			while (a != 0)
			{
				c--;
				a++;
				ctoa++;
			}
		}
		if (b < 0)
		{
			while (b != 0)
			{
				c--;
				b++;
				ctob++;
			}
		}
	}

    printf("a->b: %d원\n", atob);
    printf("b->a: %d원\n", btoa);
    printf("b->c: %d원\n", btoc);
    printf("c->b: %d원\n", ctob);
    printf("a->c: %d원\n", atoc);
    printf("c->a: %d원\n", ctoa);

    return 0;
}

