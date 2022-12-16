// KR_Disk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CarrierConstant.h"
//#include "TableConstant.h"
#include "Digit.h"
#include "Tables.h"
#include "Number.h"
#include "UserInterface.h"

int main()
{
    UserInterface ui;
    std::cout << "12 var: CARRIER = ";
    std::cout << CARRIER << "\n";
    std::cout << CARRIER.getTables();

    // TESTS
    /*
    //OTHER TEST
    srand(time(NULL));
    int wrong = 0;
    int correct = 0;
    for (int i = 0; i < 1000; i++)
    {
        
        int n1 = rand() % 99999 - rand() % 99999;
        int n2 = rand() % 99999 - rand() % 99999;

        Number num1(n1);
        Number num2(n2);
        
        std::cout << "\n------------------\n";
        std::cout << i << ") \n";
        std::cout << num1 << " (" << num1.toInt() << ")" << " + " << num2 << " (" << num2.toInt() << ")" << " = \n";
        std::cout << num1 + num2 << " (" << ((num1 + num2).toInt()) << ")" << '\n';
        
        if ((num1 + num2).toInt() == n1 + n2)
        {
            std::cout << "correct\n";
            ++correct;
        }
        else
        {
            std::cout << "WRONG!!<<<<----------------------\n";
            std::cout << "= " << Number(n1 + n2) << " (" << n1 + n2 << ")";
            ++wrong;
        }
        std::cout << "\n------------------\n";
    }
    std::cout << "\n------------------\n";
    std::cout << "WRONG: " << wrong << "\ncorrect: " << correct << "\n";
    std::cout << "\n------------------\n";
    */
   
    /* DIVISION TEST
    int iterationSum = 0;
    int Num_of_tests = 100;
    for (int i = 0; i < Num_of_tests; i++)
    {
        int n1 = rand() % 99999 - rand() % 99999;
        int n2 = rand() % 99999 - rand() % 99999;

        Number num1(n1);
        Number num2(n2);

        std::cout << "\n------------------\n";
        std::cout << i << ") \n";
        std::cout << num1 << " (" << num1.toInt() << ")" << " / " << num2 << " (" << num2.toInt() << ")" << " = \n";
        Number divRemainder;
        int iterationCount;
        Number res = num1.div(num2, divRemainder, &iterationCount);
        std::cout << "iterationCount = " << iterationCount << '\n';
        iterationSum += iterationCount;
        std::cout << res << " (" << (res.toInt()) << ") ";
        std::cout << "Remainder: " << divRemainder << " (" << (divRemainder.toInt()) << ")" << '\n';


        if (res.toInt() == n1 / n2 && divRemainder.toInt() == abs(n1 % n2))
        {
            std::cout << "correct\n";
            ++correct;
        }
        else
        {
            std::cout << "WRONG!!<<<<----------------------\n";
            std::cout << "= " << Number(n1 / n2) << " (" << n1 / n2 << ") ";
            std::cout << "Remainder: " << Number(abs(n1 % n2)) << " (" << (abs(n1 % n2)) << ")" << '\n';

            ++wrong;
        }
        std::cout << "\n------------------\n";
    }
    std::cout << "\n------------------\n";
    std::cout << "WRONG: " << wrong << "\ncorrect: " << correct << "\n";
    std::cout << "AVERAGE ITERATION count: " << iterationSum / Num_of_tests << "\n";
    std::cout << "\n------------------\n";
    */


    bool continueProgram = true;
    while (continueProgram)
    {
        Number n1;
        Number n2;

        std::string s1, s2;

        // First Number input
        std::cout << "Input 1 number: ";
        s1 = ui.inputString();
        if (!Number::validateStr(s1))
        {
            std::cout << "Number is invalid!!! Try again.\n";
            std::cout << "------------------\n";
            continue;
        }
        n1 = Number(s1);
        
        // Second Number input
        bool SecondStrIsInvalid = true;
        while (SecondStrIsInvalid)
        {
            std::cout << "Input 2 number: ";
            s2 = ui.inputString();
            if (!Number::validateStr(s2))
            {
                std::cout << "Number is invalid!!! Try again.\n";
                continue;
            }
            else
            {
                n2 = Number(s2);
                SecondStrIsInvalid = false;
            }
        }

        {//Sum
            std::cout << n1 << " (" << n1.toInt() << ")" << " + " << n2 << " (" << n2.toInt() << ")" << " = ";

            try
            {
                Number res = n1 + n2;
                std::cout << res << " (" << (res.toInt()) << ")\n";
            }
            catch (std::logic_error& e)
            {
                std::cout << e.what();
            }
        }

        {//Sub
            std::cout << n1 << " (" << n1.toInt() << ")" << " - " << n2 << " (" << n2.toInt() << ")" << " = ";
            try
            {
                Number res = n1 - n2;
                std::cout << res << " (" << (res.toInt()) << ")\n";
            }
            catch (std::logic_error& e)
            {
                std::cout << e.what();
            }
        }

        {//Mul
            std::cout << n1 << " (" << n1.toInt() << ")" << " * " << n2 << " (" << n2.toInt() << ")" << " = ";
            try
            {
                Number res = n1 * n2;
                std::cout << res << " (" << (res.toInt()) << ")\n";
            }
            catch (std::logic_error& e)
            {
                std::cout << e.what();
            }
        }

        {//Div
            std::cout << n1 << " (" << n1.toInt() << ")" << " / " << n2 << " (" << n2.toInt() << ")" << " = ";
            
            try
            {
                Number divRemainder;
                Number res = n1.div(n2, divRemainder);
                std::cout << res << " (" << (res.toInt()) << ") ";
                std::cout << "Remainder: " << divRemainder << " (" << (divRemainder.toInt()) << ")\n";
            }
            catch (std::logic_error& e)
            {
                std::cout << e.what();
            }
        }

        // End question
        bool end_flag = true;
        while (end_flag)
        {
            std::cout << "Continue (c) or Stop (s) the program: ";
            char input = ui.inputLetter();
            if (input == 'c' || input == 'C')
            {
                end_flag = false;
                std::cout << "------------------\n";
            }
            else if (input == 's' || input == 'S')
            {
                end_flag = false;
                continueProgram = false;

            }
        }
        
    }
}

