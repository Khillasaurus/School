#include <iostream>

using namespace std;

int main()
{
    cout << "Questions:" << endl;
    cout << "Question 4.29a)\t!(x < 5) && !(y >= 7)" << endl;
    cout << "Question 4.29b)\t!(a == b) || !(g != 5)" << endl;
    cout << "Question 4.29c)\t!( (x <= 8) && (y > 4) )" << endl;
    cout << "Question 4.29d)\t!( (i > 4) || (j <= 6) )" << endl << endl;

    cout << "Answers:" << endl;
    cout << "Answer to 4.29a) !(x < 5 || y >= 7)" << endl;
    cout << "Answer to 4.29b) !(a == b && g != 5)" << endl;
    cout << "Answer to 4.29c) !(x <= 8) || !(y > 4)" << endl;
    cout << "Answer to 4.29d) !(i > 4) && !(j <= 6)" << endl;


    return 0;
}
