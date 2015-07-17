#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    return 0;
}


//        C How to Program, Fifth Edition by Deitel Textbook Questions
//        ************************************************************
//
//        Chapter 2.7 - 2.12
//        ------------------
//        Question 2.7:   Identify and correct the errors in each of the following statements.
//                        (Note: There may be more than one error per statement.)
//                        a) scanf( "d", value );
//                        b) pri ntf( "The product of %d and %d is %d"\n, x, y );
//                        c) firstNumber + secondNumber = sumOfNumbers
//                        d) if ( number => largest )
//                        l argest == number;
//                        e) */ Program to determine the largest of three integers /*
//                        f) Scanf( "%d", anInteger );
//                        g) pri ntf( "Remainder of %d divided by %d i s\n", x, y, x % y );
//                        h) if ( x = y ) ;
//                        printf( %d is equal to %d\n", x, y );
//                        i) pri nt( "The sum i s %d\n," x + y );
//                        j) Pri ntf( "The value you entered is: %d\n, &value );
//
//            Answers:    a) scanf( "%d", &value );
//                        b) printf( "The product of %d and %d is %d\n", x, y );
//                        c) firstNumber + secondNumber = sumOfNumbers;
//                        d) if ( number >= largest )
//                            {
//                            largest == number;
//                            }
//                        e) /* Program to determine the largest of three integers */
//                        f) Scanf( "%d", &anInteger );
//                        g) printf( "Remainder of %d divided by %d is %d\n", x, y, x % y );
//                        h) if ( x = y )
//                            {
//                            printf( "%d is equal to %d\n", x, y );
//                            }
//                        i) printf( "The sum is %d\n," x + y );
//                        j) printf( "The value you entered is: %d\n", &value );
//        Question 2.8:   Fill in the blanks in each of the following:
//
//                        a) ___ are used to document a program and improve its readability.
//                        b) The function used to display information on the screen is ___.
//                        c) A C statement that makes a decision is ___.
//                        d) Calculations are normally performed by ___ statements.
//                        e) The ___ function inputs values from the keyboard.
//
//            Answers:    a) comments
//                        b) printf()
//                        c) if statements
//                        d) assignment statements
//                        e) scanf()
//
//        Question 2.9:   Write a single C statement or line that accomplishes each of the following:
//                        a) Print the message “Enter two numbers.”
//                        b) Assign the product of variables b and c to variable a.
//                        c) State that a program performs a sample payroll calculation (i.e., use text that helps to
//                        document a program).
//                        d) Input three integer values from the keyboard and place these values in integer variables
//                        a, b and c.
//
//            Answers:    a) printf("Enter two numbers.");
//                        b) a = b*c;
//                        c) //Calculate Sample Payroll
//                        d) scanf( "%d %d %d", &a, &b, &c,);
//
//        Question 2.10   State which of the following are true and which are false. If false, explain your answer.
//                        a) C operators are evaluated from left to right.
//                        b) The following are all valid variable names: _under_bar_, m928134, t5, j7, her_sales,
//                        his_account_total , a, b, c, z, z2.
//                        c) The statement printf("a = 5;") ; is a typical example ofan assignment statement.
//                        d) A valid arithmetic expression containing no parentheses is evaluated f
//                        e) The following are all invalid variable names: 3g, 87, 67h2, h22, 2h.
//
//            Answers:    a) true. Although some are evaluated right to left as well.
//                        b) true.
//                        c) false. The statement would print out a = 5; rather than assigning the value 5 to the variable a.
//                        d) false. All boolean calculations evaulate to either 1 or 0.
//                          Secondly more information is required (such as where the parentheses are placed) as to whether it would change the outcome of the calculation.
//                          Also simply adding parenthesis to the outside of an arithmetic expression does not change the outcome of the expression.
//                        e) false. h22 is a valid variable name. All other variable names are still invalid though.
//
//        Question 2.11   Fill in the blanks in each of the following:
//                        a) What arithmetic operations are on the same level of precedence as multiplication? ____.
//                        b) When parentheses are nested, which set ofparentheses is evaluated first in an arithmetic expression? ___.
//                        c) A location in the computer's memory that may contain different values at various times
//                           throughout the execution of a program is called a ___.
//
//            Answers:    a) Division
//                        b) The outermost parenthesis are evaluated first.
//                        c) variable
//
//        Question 2.12   What, if anything, prints when each of the following statements is performed?
//                        If nothing prints, then answer “Nothing.” Assume x = 2 and y = 3.
//                        a) printf( "%d", x ) ;
//                        b) printf( "%d", x + x );
//                        c) printf( "x=" );
//                        d) printf( "x=%d", x );
//                        e) printf( "%d = %d", x + y, y + x );
//                        f) z = x + y;
//                        g) scanf( "%d%d", &x, &y );
//                        h) /* printf( "x + y = %d", x + y ); */
//                        i) printf( "\n" );
//
//            Answers:    a)2
//                        b)4
//                        c)x=
//                        d)5 = 5
//                        e)Nothing
//                        f)Nothing
//                        h)Nothing
//                        i)a new line is created
//
//
//




    /*

        Computer Structure and Logic Textbook Questions
        ***********************************************

        Chapter 2 Review Questions:
        ---------------------------
        Question 1:  How many combinations are there in a 4-bit binary number?
            Answer:      C. 16
        Question 2:  24-bit color is the same as which of the following amounts of colors?
            Answer:      D. 16,777,216
        Question 3:  What is the binary equivalent of the decimal number 6?
            Answer:      B. 110
        Question 4:  What is the binary equivalent of the decimal number 255?
            Answer:      C. 11111111
        Question 5:  What is the decimal value of 212?
            Answer:      D. 4096
        Question 6:  A gigabyte is equal to how many bytes in binary measurement?
            Answer:      A. 2^30
        Question 7:  In the hexadecimal numbering system, what is D equal to?
            Answer:      C.   D is equal to 13.
        Question 8:  Which of the following operators is represented with the | (pipe) sign?
            Answer:      B.   OR
        Question 9:  Using the binary numbering system, if A equals 1 and B equals 1, what is the solution to the following equation: A AND B.
            Answer:      B.   1
        Question 10: You want to search for records containing “music lessons” and “computer music.” Which of the following expressions would work best?
            Answer:      A.   music AND (lessons OR computer)
        Question 11: What does the following measurement mean? 266MBps
            Answer:      C.   266 megabytes per second
        Question 12: Which of the following would be faster at an identical clock speed?
            Answer:      A.   Parallel data transfer
        Question 13: What is 1GHz equal to?
            Answer:      C. 1,000,000,000 Hertz
        Question 14: Which numbering system has 16 values?
            Answer:      D. Hexadecimal
        Question 15: What is the decimal equivalent of the binary number 11110000?
            Answer:      B. 240

        Chapter 3 Review Questions:
        ---------------------------
        Question 1:  Which of the following can be used with the SCSI-based technology? (Choose two.)
        Answer:      A. High-performance and high-capacity hard drives AND B. Image scanners
        Question 2:  What are two ways that USB version 2.0 ports can be added to a computer? (Choose two.)
        Answer:      A. Implement a USB hub AND C. Add a USB 2.0 expansion card
        Question 3:  A serial port can hook up devices such as external modems and label printers.
                     What is this port usually called?
        Answer:      B. COM port
        Question 4:  Which of the following devices can be used for a printer port, scanner, or removable media?
        Answer:      B. Parallel port
        Question 5:  Which device is known as IEEE 1394?
        Answer:      C. FireWire
        Question 6:  Some desktop systems and many of the older laptop and portable systems include a port to connect a mouse or keyboard.
                     What is this port called?
        Answer:      D. PS/2
        Question 7:  What is the standard size of the audio mini-jack used by sound cards?
        Answer:      B. 1/8 inch
        Question 8:  There are currently three standards for USB ports. What are they? (Choose three.)
        Answer:      A. USB 1.1 AND D. USB 2.0 AND B. USB 3.0
        Question 9:  If you run out of USB ports and need more, which of the following devices are available? (Choose all that apply.)
        Answer:      A. Motherboard connectors AND B. USB hubs AND C. Add-on cards
        Question 10: Which device still remains the primary method used to enter data and send commands to the computer?
        Answer:      D. Keyboard
        Question 11: Which of the following is used to transfer data into a computer by pressing on screen icons?
        Answer:      A. Touch screen monitors
        Question 12: Which of the following are considered multimedia devices? (Choose all that apply.)
        Answer:      D. All of these options are correct. (A. Webcam AND B. Sound card AND C. Microphone)
        Question 13: You are in the process of installing a new keyboard to a new PC.
                     Which of the following is the most common type of connector to use?
        Answer:      C. USB connector
        Question 14: What is the major difference between a laser printer and an LED printer? (Choose all that apply.)
        Answer:      A. LED printers use an LED array to perform the transfer of images. AND
                     D. Laser printers use a laser to transfer the image to the drum.
        Question 15: Most inkjet, laser, and thermal printers use this interface to connect a printer to a computer. (Choose two.)
        Answer:      B. USB AND C. Parallel
        Question 16: What are three major types of display devices that are in use in today’s industry? (Choose all that apply.)
        Answer:      A. CRT monitors AND B. LCD monitors AND C. Data projectors
        Question 17: Identify three types of video connectors.
        Answer:      A. VGA type AND B. DMI type AND C. HDMI type

    */
