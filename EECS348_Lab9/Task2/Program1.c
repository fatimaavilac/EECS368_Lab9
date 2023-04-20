/*
 * Program1.c
 *
 *  Created on: Feb 10, 2023
 *      Author: Fatima Avila
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void minSale(float sales[], float *min, int *minMonth)
{
	/* Find minimum value from given array. */

	for(int i = 0; i < 12; ++i)
	{
		if(sales[i] < *min)
		{
			*min = sales[i];
			*minMonth = i;
		}
	}
}

void maxSale(float sales[], float *max, int *maxMonth)
{
	/* Find maximum value from given array. */

	for(int i = 0; i < 12; ++i)
	{
		if(sales[i] > *max)
		{
			*max = sales[i];
			*maxMonth =  i;
		}
	}
}

void avgSale(float sales[], float *avg)
{
	/* Find average of all values from given array. */

	for(int i = 0; i < 12; ++i)
	{
		*avg+=sales[i];
	}
	*avg = *avg / 12;

}

float findSix(int i, float sales[])
{
	/* Return average of the given index and the next 6 values from given array. */

	float avg = 0;

	for(int j = 0; j < 6; ++j)
	{
		avg+=sales[i+j];
	}

	avg = avg / 6;
	return avg;
}

int main(void)
{
	float sales[12]; // array of sale values from input file
	char *months[12] = {"January", "February", "March", "April", "May", "June",
					  "July", "August", "September", "October", "November", "December"};
	FILE *fptr; // file pointer
	char fname[100] = ""; // filename variable

	printf("\nEnter filename: "); // prompt user for filename
	scanf("%s", fname); // initialize filename

	// check for valid user file
	if ((fptr = fopen(fname, "r")) == NULL)
	{
		printf("<Error> File could not be opened.\n");
		exit(1); // if file fails, exit program
	}

	printf("\nReading from file...\n");

	int i = 0;
	// reads file
	while(!feof(fptr))
	{
		// input each value into sales array
		fscanf(fptr, "%f", &sales[i]);
		i++;
	}

	// Monthly Sales Report
	printf("\nMonthly Sales Report for 2023:\n");
	printf("\nMonth\t\tSales\n\n");

	// print all values of sales array
	for(int i = 0; i < 12; ++i)
	{
		if(i == 1 || i == 8 || i == 10 || i == 11)
		{
			printf("%s\t$%.2f\n", months[i], sales[i]);
		}
		else
			printf("%s\t\t$%.2f\n", months[i], sales[i]);
	}

	// Sales Summary
	printf("\nSales Summary:\n");

	int minMonth = 0; // month with minimum sale var
	float min = sales[0]; // mimimum sale var
	int maxMonth = 0; // month with minimum sale var
	float max = sales[0]; // maximum sale var
	float avg = 0; // average sale var

	minSale(sales, &min, &minMonth); // call minSale() function
	maxSale(sales, &max, &maxMonth); // call maxSale() function
	avgSale(sales, &avg); // call avgSale() function

	printf("\nMinimum sales:\t$%.2f  (%s)\n", min, months[minMonth]); // print min sale
	printf("Maximum sales:\t$%.2f  (%s)\n", max, months[maxMonth]); // print max sale
	printf("Average sales:\t$%.2f\n", avg); // print avg sale

	// Six-Month Moving Average
	printf("\nSix-Month Moving Average Report:\n\n");

	float sixAvg[7]; // six-month moving avg array

	for(int i = 0; i < 7; ++i)
	{
		/* call findSix() with increasing index for each month
			and receive each return into sixAvg array 			*/
		sixAvg[i] = findSix(i, sales);
	}

	// print six-month avg report
	for(int i = 0; i < 7; ++i)
	{
		if(i == 1)
			printf("%s\t-  %s\t\t$%.2f\n", months[i], months[i+5], sixAvg[i]);
		else if(i == 0)
			printf("%s\t\t-  %s\t\t$%.2f\n", months[i], months[i+5], sixAvg[i]);
		else
			printf("%s\t\t-  %s\t$%.2f\n", months[i], months[i+5], sixAvg[i]);
	}

	// Sales Report Highest-to-Lowest
	printf("\nSales Report (Highest to Lowest):\n\n");

	float ordered[12]; // ordered sales array
	float a; // temp var

	// duplicate sales[]
	for(int i = 0; i < 12; ++i)
	{
		ordered[i] = sales[i];
	}

	// nested loop to reorder orray into descending order
	for(int i = 0; i < 12; ++i)
	{
		for(int j = i + 1; j < 12; ++j)
		{
			if(ordered[i] < ordered[j])
			{
				a = ordered[i];
				ordered[i] = ordered[j];
				ordered[j] = a;
			}
		}
	}

	printf("Month\t\tSales\n\n");

	// print sales report in descending order
	for(int i = 0; i < 12; ++i)
	{
		for(int j = 0; j < 12; ++j)
		{
			if(ordered[i] == sales[j])
			{
				if(j == 11 || j == 10 || j == 8 || j == 1)
					printf("%s\t$%.2f\n", months[j], ordered[i]);
				else
					printf("%s\t\t$%.2f\n", months[j], ordered[i]);
			}
		}
	}

	printf("\n");

	fclose(fptr);

	return 0;
}
