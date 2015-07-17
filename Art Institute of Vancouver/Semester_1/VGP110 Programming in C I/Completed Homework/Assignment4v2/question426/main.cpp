#include <stdio.h>

int main()
{

    int accuracy;
    int aHold;
    double pi = 0;
    double numerator = 4;
    double denominator = 1;
    int termNumber = 1;

    printf("Please enter how accurate a value of pi (where accuracy is based upon amount of terms used to calculate pi) you would like:\n");
    scanf("%f",&accuracy);

    aHold = accuracy;
    while (accuracy > 0)
    {
        if (termNumber%2 == 0)
        {
            pi = pi-(numerator/denominator);
        }
        else
        {
            pi = pi+(numerator/denominator);
        }
        denominator = denominator +2;
        accuracy--;
        termNumber++;
    }

    printf("Pi with an accuracy of %d is equal to %f.",aHold,pi);

    return 0;

}
//119 terms are required to calculate 3.14
//1686 terms are required to calculate 3.141
//10746 terms are required to calculate 3.1415
//At least 317100 terms are required to calculate 3.14159
