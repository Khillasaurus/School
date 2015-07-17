#include <stdio.h>

int main()
{

    int typeOfWorker;

    double mTotalWage = 0;

    double hHourlyWage = 0;
    double hHoursWorked = 0;
    double hNormalPay = 0;
    double hOvertimePay = 0;
    double hTotalWage = 0;

    double cGrossSales = 0;
    double cTotalWage = 0;

    int pPiecesCompleted = 0;
    double pPayPerPiece = 0;
    double pTotalWage = 0;


    printf("To edit wages, enter 1 for manager, 2 for hourly workers, 3 for commission workers, 4 for pieceworkers and 0 to quit.\n");
    typeOfWorker = getchar();

    while(typeOfWorker != 0)
    {
        switch(typeOfWorker)
        {
            case '1':
                printf("Enter the weekly wage for a manager without the $ sign:\n");
                scanf("%lf",&mTotalWage);
                printf("This manager is getting paid %.2f per week.\n\n",mTotalWage);
                break;

            case '2':
                printf("Enter the hourly wage for an hourly worker without the $ sign:\n");
                scanf("%lf",&hHourlyWage);
                printf("Enter the amount of hours the hourly worker worked:\n");
                scanf("%lf",&hHoursWorked);

                hNormalPay = hHourlyWage*hHoursWorked;
                if(hHoursWorked>40)
                {
                    hOvertimePay=(hHoursWorked-40)*(hHourlyWage*0.5);
                }
                hTotalWage = hNormalPay+hOvertimePay;
                printf("This hourly worker is getting paid: %.2f\n\n",hTotalWage);
                break;

            case '3':
                printf("Enter the gross of the commission workers sales without the $ sign:\n");
                scanf("%lf",&cGrossSales);

                cTotalWage = 250 + (cGrossSales*0.057);
                printf("This commission worker is getting paid: %.2f\n\n",cTotalWage);
                break;

            case '4':
                printf("Enter the amount of pieces the commission workers completed:\n");
                scanf("%d",&pPiecesCompleted);
                printf("Enter how much the commission worker gets paid per piece they completed:\n");
                scanf("%lf",&pPayPerPiece);
                pTotalWage = pPiecesCompleted*pPayPerPiece;
                printf("This piecework worker is getting paid: %.2f\n\n",pTotalWage);
                break;

            case '\n':  //ignore new lines in input
            case '\t':  //ignore tabs in input
            case ' ':   //ignore spaces in input
                break;

        }
        printf("To edit wages, enter 1 for manager, 2 for hourly workers, 3 for commission workers, 4 for pieceworkers and 0 to view results.\n");
        typeOfWorker = getchar();
    }


    return 0;

}
