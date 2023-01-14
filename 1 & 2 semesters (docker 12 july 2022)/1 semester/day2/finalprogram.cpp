#include <stdio.h>
#include <math.h>

int main()
{
	printf("Salut! I'm calculating BMI (body mass index)! Give me your mass in kilograms\n");
	float m, h, bmi;
	scanf("%f", &m);
	printf("Now give me your height in meters\n");
	scanf("%f", &h);
	bmi = m/pow(h, 2);
	printf("Your BMI is ~ %f\n", bmi);
	if(bmi >= 18.5 && bmi <= 25)
	{
		printf("Your BMI is Normal!\n");
	}
	if(bmi < 18)
		printf("You are underweight!\n");
	if(bmi > 25)
		printf("You are overweight!\n");
	return 0;
}
