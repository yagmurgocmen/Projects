#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

typedef struct {
	char product[20];
	double price;
	int quantity;
}product_t;

int readFromFile(FILE* inp, product_t* p,int size)
{
	int i;
	for (i = 0; i < size; i++)
		fscanf(inp, " %[^0-9] %lf %d", (p + i)->product, &(p + i)->price, &(p + i)->quantity);
	return i;
}

void display(product_t* p, int size)
{
	int i;
	printf("PRODUCT        UNIT PRICE  QUANTITY\n");
	for (i = 0; i < size; i++)
	{
		printf("%d. %-15s %5.2f", i+1, (p + i)->product, (p + i)->price);

		if ((p + i)->quantity == 0)
			printf("    OUT" );
		else
		printf(" %10d", (p+i)->quantity);
		
		printf("\n");
		

	}
}

int main(void)
{
	FILE* inp = fopen("products.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		int pro,size;
		double money;
		int num = 0;
		product_t *p;
		
		fscanf(inp, "%d", &size);
		p = (product_t*)malloc(sizeof(product_t) * size);
		readFromFile(inp,p, size);

		do
		{
			display(p, size);

			printf("\n\nEnter a product to purchase (to stop -1) :");
			scanf("%d", &pro);

			if (pro != -1)
			{
				if ((p + pro - 1)->quantity == 0)
					printf("\nTHERE IS NO MORE %s\n", (p + pro - 1)->product);
				else
				{
					printf("\nInsert the money: ");
					scanf("%lf", &money);

					if (money >= (p + pro - 1)->price)
					{
						printf("\n%.2f TL return back\n\n", money - (p + pro - 1)->price);
						p[pro - 1].quantity--;
					}
				}
				num++;
			}
		

		} while (pro != -1);

		printf("\n****************\n");
		printf("Today %d products sold", num);

		

	}
}