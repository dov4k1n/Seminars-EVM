#include <stdio.h>
#include <math.h>

int main()
{
	printf("Salut! I'm calculating BMI (body mass index)! Give me your mass in kilograms\n");
	float m, h, bmi;
	int ret = scanf("%f", &m);
	if(ret != 1)
	{
		printf("error!\n");
		return -1;
	}

	if(m <= 0 || m > 500)
	{
		printf("incorrect input!\n");
		return 0;
	}

	printf("Now give me your height in meters\n");
	ret = scanf("%f", &h);
	if(ret != 1)
	{
		printf("error!\n");
		return -1;
	}

	if(h <= 0 || h > 3)
	{
		printf("incorrect input!\n");
		return 0;
	}

	bmi = m/pow(h, 2);
	printf("Your BMI is ~ %f\n", bmi);

	if(bmi >= 18.5 && bmi < 25)
		printf("Your BMI is Normal!\n");
	if(bmi >= 17 && bmi < 18.5)
		printf("You are underweight! (Mild thinness)\n");
	if(bmi >= 16 && bmi < 17)
		printf("You are underweight! (Moderate thinness)\n");
	if (bmi < 16)
		printf("You are underweight! (Severe thinness)\n");
	if (bmi >= 25 && bmi < 30)
		printf("You are overweight! (Pre-obese)\n");
	if (bmi >= 30 && bmi < 35)
		printf("You have obesity! (Class I)\n");
	if (bmi >= 35 && bmi < 40)
		printf("You have obesity! (Class II)\n");
	if (bmi >= 40)
		printf("You have obesity! (Class III)\n");
	return 0;
}
