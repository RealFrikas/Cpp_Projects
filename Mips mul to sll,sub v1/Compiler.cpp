#include <iostream>
#include <cmath>

//count the digits in a number
int finddigits(int number)
{
    int digits = 0;
    while (number != 0) 
    {
        number /= 10;
        ++digits;
    }
    return digits;
}

//seperate each digit
int seperateddigit(int number,int target)
{
    target = pow(10 , target - 1);
    int r = (number / target) % 10;
    return r;
}

//input validation headache
int getUNum()
{
    int num,tempcount = 0;	
    if(!(std::cin >> num))  //not a number
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear bad input love,GPT
        std::cout << "Please input a number" << std::endl;
        return 2;
    }

    //out of bounds
    tempcount = finddigits(num);
    for (int i = 1; i <= tempcount; i++)
    {
        if(seperateddigit(num,i) > 1 || seperateddigit(num,i) < 0)
        {
            std::cout << "Only binary numbers allowed...for now ;)" << std::endl;
            return 2;
        }
    }
	return num;
}

int main()
{

    //cout give instructions
    std::cout<<"Welcome to \"MIPS mul to sll,sub\" V1.0 by Frikas!!!" << std::endl;
    std::cout<<"Please input your up to 10 digits binary number and the program will spit out the answer \nwith the multiplicand number being $t1"<<std::endl;

    //cin give input,count is for how many digits the number has
    int binary = 2;
    while (binary == 2)
    {
        binary = getUNum();
    }

    //count the digits of the binary number
    int count = finddigits(binary);

    //check if number is not 100000...
    int powercount = pow(10, count - 1);
    if(binary % powercount != 0)
    {
        std::cout<<"sll $t2,$t1," << count << std::endl;

        //make special case for number ending in 1
        bool single = false;
        if (binary%10 == 1)
        {
            single = true;
            binary += 9;
        }

        //first part: bitshifts and temps
        int tempno = 3;
        int makesingle = 2;
        int digit;
        for(int i = 2; i < count; i ++)
        {
            digit = seperateddigit(binary,makesingle);
            if (digit == 1)
            {
                std::cout << "sll $t" << tempno << ",$t1," << i - 1 << std::endl;
                tempno++;
                binary += 9 * pow(10 , makesingle - 1);             
            }
            else if (digit > 1)
            {
                binary += 8 * pow(10 , makesingle - 1);        
            }
            makesingle++;  
        }

        //second part: subtractions and answer
        tempno -= 1;
        if (single)
        {
            if (tempno == 2)
            {
                std::cout << "sub $s2,$t2,$t1" << std::endl;
                goto end;
            }
            else
            {
                std::cout << "sub $t2,$t2,$t1" << std::endl;
            }
        }
        for (int i = 3; i < tempno; i++)
        {
            std::cout << "sub $t2,$t2,$t" << i << std::endl;
        }
        std::cout << "sub $s2,$t2,$t" << tempno << std::endl;
    }
    else
    {
        std::cout<<"sll $s2,$t1," << (count - 1)<< std::endl;
    }

    //any key to continue,i could make a goto to just restart the whole thing infinitely XD
    end:
    system("pause");
}