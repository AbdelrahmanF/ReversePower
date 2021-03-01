#include <stdio.h>

#define MAX 100000	/* Maximum number of digits in output */
//#define VERBOSE	/* Print debug information */

/* *********************************************************************
 * Private Functions
 * */
 
unsigned int IntegerReverse(unsigned int rev_in);
unsigned int LongMultiplication(unsigned int whole_num, unsigned char res[], unsigned int res_size);
void IntegerPow(unsigned int base, unsigned int exp);
/* ***************************************************************** */


/* *********************************************************************
 * @Name:	IntegerReverse
 * @Desc:	This function takes an unsigned integer and reverses 
 * 			the order of its digits. O(n) where n is the number
 * 			of digits in the input number
 * @ARG1:	rev_in: The number to be reversed
 * @Return:	The reversed digits of the input number 
 * ********************************************************************/
unsigned int IntegerReverse(unsigned int rev_in)
{
	unsigned int retVal = 0, mod_temp = 0;
	
	while(rev_in > 0)/* Keep going until the most significant digit becomes in the units */
	{ 
		mod_temp = rev_in % 10;	/* get the least significant digit */

		retVal = (retVal * 10) + mod_temp;	/* decimal shift left, and adding the new digit */
		 
		rev_in /= 10;				/* decimal right shift to eliminate the used digit  */

#ifdef VERBOSE
		printf("rev_in = %d mod_temp = %d  retVal = %d\n",rev_in, mod_temp, retVal);
#endif
	}
	
	return retVal;
}


/* *********************************************************************
 * @Name:	LongMultiplication
 * @Desc:	This function takes performs long multiplication by stroing each digit in an array element.
 *			Credit to www.geeksforgeeks.org, plus some refactoring and documentation
 * @ARG1:	whole_num: The base number as was input as a whole integer
 * @ARG2:	res[]: The result array holding the outcome of the multiplication
 * @ARG3:	res_size: The size (length) ofthe result
 * @Return:	The reversed number 
 * ********************************************************************/
unsigned int LongMultiplication(unsigned int whole_num, unsigned char res[], unsigned int res_size)
{

int carry = 0;	/*Initialize carry*/

/* Multiply each digit of the number by the whole number
 * i.e 12 x 12; first 2 x 12 = 4 (carry 2) then 1 x 12 + (carry) = 14  */
for (unsigned int i = 0; i < res_size; i++) 
{
	unsigned int prod = (res[i] * whole_num) + carry;	/* (single digit x whole) + carry (init = 0) */
	
#ifdef VERBOSE
	printf("%d * %d =%d  ", res[i], whole_num, prod, i);
#endif

	/* Store last digit of 'prod' in res[] */
	res[i] = prod % 10;

	/* Put rest in carry */
	carry = prod / 10;
#ifdef VERBOSE	
	printf("   res[%d]= %d carry=%d\n", i, res[i], carry);
#endif
}


/* After multiplication, if there is still carry, more digit(s) nedded to hold it  */
while(carry != 0)
 {
#ifdef VERBOSE
	printf("size++ %d\n", carry);
#endif

	res[res_size] = carry % 10;	/* add to result array */
	carry = carry / 10;
	res_size++;					/* increase size */
	
#ifdef VERBOSE
	printf("   res[%d]= %d \n", res_size-1, res[res_size-1]);
#endif
}

return res_size;	/* feedback the size to be used in the next multiplication round */
}

/* *********************************************************************
 * @Name:	IntegerPow
 * @Desc:	This function calculates base to the power exp and places 
 * 			each digit of the output number in a sepatae array index 
 * @ARG1:	base:The base number
 * @ARG2:	exp:The exponent number
 * @Return:	void 
 * ********************************************************************/
void IntegerPow(unsigned int base, unsigned int exp) 
{

unsigned char res[MAX];	/* 1 byte is enough to hold 1 digit and save RAM with very long numbers */
unsigned int res_size = 0;
unsigned int temp = base;
FILE * fp;

/* if the power is zero, print 1 and exit */
if(exp == 0 )
{ 
	printf("1\n");
}
else
{

	/* initializing result array to hold each digit of the base value */
	while (temp != 0) 
	{
		res[res_size++] = temp % 10;
		temp = temp / 10;
	}


	/* number of multiplications = exp - 1
	 * i.e : base^3 = (base * base) * base (exp = 3, two multiplication rounds)
	 *  */
	for (int exp_idx = 0; exp_idx < exp-1; exp_idx++)
	{
#ifdef VERBOSE
			printf("multiplication round # %d out of %d output digits =%d\n", exp_idx+1,exp-1, res_size);
#endif
			res_size = LongMultiplication(base, res, res_size);
	}
	
	fp = fopen ("power_output.txt", "w+");
	fprintf(fp,"%d to the power %d:\n", base, exp);
	
	printf("Raising %d to the power %d = ", base, exp);
	
	/* print the output digit by digit, most significant first */
	for (int out_idx = res_size - 1; out_idx >= 0; out_idx--)
	{
		printf("%d", res[out_idx]);
		fprintf(fp,"%d", res[out_idx]);
	}
}
	printf("\n\n");
	fclose(fp);
}

int main(){
	unsigned int Input = 0;
	long user_input = 0;	/* use signed type to detect negative input */
	
	printf("Please enter a positive integer bigger than 9:");
	scanf("%d",&user_input);
	
	if((user_input < 0) || (user_input < 9))	/* boundary protection */
	{
		printf("Invalid Input %d\n",user_input);
	}  
	else
	{
		Input = (unsigned int)user_input;
		
		IntegerPow(Input, IntegerReverse(Input));
	}
   
   return 0;
}
