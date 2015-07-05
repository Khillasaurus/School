#include <stdio.h>

int main()
{

    int input;
    int digitOnes;
    int digitTens;
    bool tenDigits = false;
    int digitHundreds;
    bool hundredDigits = false;
    int digitThousands;
    bool thousandDigits = false;
    int digitTenThousands;
    bool tenThousandDigits = false;
    int digitHundredThousands;
    bool hundredThousandDigits = false;
    int digitMillions;
    bool MillionDigits = false;

    printf("Please enter an integer and I will reverse it and output it.\n");
    scanf("%d",&input);

    //digitMillions
    digitMillions = input/1000000;
    if(digitMillions>0)
    {
        MillionDigits=true;
    }


    //digitHundredThousands
    if((input-1000000)>0)
    {
        digitHundredThousands = (input-1000000)/100000;
    }
    else
    {
        digitHundredThousands = input/100000;
    }
    if(digitHundredThousands>0)
    {
        hundredThousandDigits=true;
    }


    //digitTenThousands
    if(MillionDigits==true && (input-1100000)>0)
    {
        digitTenThousands = (input-1100000)/10000;
        tenThousandDigits=true;
    }
    else if(hundredThousandDigits==true && (input-100000)>0)
    {
        digitTenThousands = (input-100000)/10000;
        tenThousandDigits=true;
    }
    else
    {
        digitTenThousands = input/10000;
    }
    if(digitTenThousands>0)
    {
        tenThousandDigits = true;
    }


    //digitThousands
    if(MillionDigits==true && (input-1110000)>0)
    {
        digitThousands = (input-1110000)/1000;
        thousandDigits=true;
    }
    else if(hundredThousandDigits==true && (input-110000)>0)
    {
        digitThousands = (input-110000)/1000;
        thousandDigits=true;
    }
    else if(tenThousandDigits==true && (input-10000)>0)
    {
        digitThousands = (input-10000)/1000;
        thousandDigits=true;
    }
    else
    {
    digitThousands = input/1000;
    }
    if(digitThousands>0)
    {
        thousandDigits = true;
    }


    //digitHundreds
    if(MillionDigits==true && (input-1111000)>0)
    {
        digitHundreds = (input-1111000)/100;
        hundredDigits=true;
    }
    else if(hundredThousandDigits==true && (input-111000)>0)
    {
        digitHundreds = (input-111000)/100;
        hundredDigits=true;
    }
    else if(tenThousandDigits==true && (input-11000)>0)
    {
        digitHundreds = (input-10000)/100;
        hundredDigits=true;
    }
    else if(thousandDigits==true && (input-1000)>0)
    {
        digitHundreds = (input-1000)/100;
        hundredDigits=true;
    }
    else
    {
        digitHundreds = input/100;
    }
    if(digitHundreds>0)
    {
        hundredDigits=true;
    }


    //digitTens
    if(MillionDigits==true && (input-1111100)>0)
    {
        digitTens = (input-1111100)/10;
        tenDigits=true;
    }
    else if(hundredThousandDigits==true && (input-111100)>0)
    {
        digitTens = (input-111100)/10;
        tenDigits=true;
    }
    else if(tenThousandDigits==true && (input-11100)>0)
    {
        digitTens = (input-11000)/10;
        tenDigits=true;
    }
    else if(thousandDigits==true && (input-1100)>0)
    {
        digitTens = (input-1100)/10;
        tenDigits=true;
    }
    else if(hundredDigits==true && (input-100)>0)
    {
        digitTens = (input-100)/10;
        tenDigits=true;
    }
    else
    {
        digitTens = input/10;
    }
    if(digitTens>0)
    {
        tenDigits=true;
    }


    //digitOnes
    if(MillionDigits==true && (input-1111110)>0)
    {
        digitOnes = input-1111110;
    }
    else if(hundredThousandDigits==true && (input-111110)>0)
    {
        digitOnes = input-111110;
    }
    else if(tenThousandDigits==true && (input-11110)>0)
    {
        digitOnes = input-11000;
    }
    else if(thousandDigits==true && (input-1110)>0)
    {
        digitOnes = input-1110;
    }
    else if(hundredDigits==true && (input-110)>0)
    {
        digitOnes = input-110;
    }
    else if(tenDigits==true && (input-10)>0)
    {
        digitOnes = input-10;
    }
    else
    {
        digitOnes = input;
    }
    if(digitTens>0)
    {
        tenDigits=true;
    }

    printf("Millions:%d\nHundredThousands:%d\nTenThousands:%d\nThousands:%d\nHundreds:%d\nTens:%d\nOnes:%d\n",digitMillions, digitHundredThousands, digitTenThousands, digitThousands, digitHundreds, digitTens, digitOnes);


    return 0;
}
