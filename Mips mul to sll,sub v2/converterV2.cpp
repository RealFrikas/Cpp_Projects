#include <iostream>
#include <cmath>

//count the digits in a number  !!update complete
int finddigits(int number)
{
    int digits = 0;
    while (number != 0) 
    {
        number /= 2;
        ++digits;
    }
    return digits;
}

//seperate each digit !!update complete
int seperateddigit(int number,int target)
{
    //(number mod 2 ^ target) / (target / 2) == 1 or 0
    int power = pow(2 , target);
    number = number % power;
    number /= power / 2;
    return number;
}

//input validation headache !!update complete
int getUNum()
{
    int num = 0;	
    if(!(std::cin >> num))  //not a number
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear bad input love,GPT
        std::cout << "Please input a number" << std::endl;
        return -1;
    }
    else if(num < 0)    //negative
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear bad input love,GPT
        std::cout << "Please input a positive number" << std::endl;
        return -1;
    }
	return num;
}

void dosub(bool last) //do the subtractions so we dont get $t10 cause that doesn't exist !!v2 feature
{
    if(!last)
    {
        for (int i = 3; i < 10; i++)
        {
            std::cout << "sub $t2,$t2,$t" << i << std::endl;
        }
    }
    else
    {
        for (int i = 3; i < 9; i++)
        {
            std::cout << "sub $t2,$t2,$t" << i << std::endl;
        }
        std::cout << "sub $s2,$t2,$t9" << std::endl;    
    }
}

int main()
{

    //cout give instructions
    std::cout<<"Welcome to \"MIPS mul to sll,sub\" V2.0 by Frikas!!!\n" << std::endl;
    std::cout<<"Instructions:\n1.Find your AM number in qtspim as a decimal form at the mul instruction." << std::endl;
    std::cout<<"2.Type the DECIMAL(can't tell apart from binary) number in this program." << std::endl;
    std::cout<<"3.The program expects that the AM number is in $t0,the random number in $t1 and the answer in $s2" << std::endl;
    std::cout<<"4.Change the expected registers with the ones that match the exam program.\n" << std::endl;

    //cin give input,count is for how many digits the number has !!update complete
    int binary = -1;
    while (binary == -1)
    {
        binary = getUNum();
    }

    //count the digits of the binary number !!update complete
    int count = finddigits(binary);

    //check if number is not 100000... !!update complete
    int powercount = pow(2, count - 1);
    if(binary != powercount)
    {
        std::cout<<"sll $t2,$t1," << count << std::endl;

        //make special case for number ending in 1 !!update complete
        bool single = false;
        if (binary % 2 == 1)
        {
            binary += 1;
            if (binary == powercount)
            {
                std::cout << "sub $s2,$t2,$t1" << std::endl;
                goto end;
            }
            else
            {
                std::cout << "sub $t2,$t2,$t1" << std::endl;
            }
        }

        //first part: bitshifts and temps !!update complete
        int tempno = 3;
        int makesingle = 2;
        int digit;
        for(int i = 2; i < count; i ++)
        {
            digit = seperateddigit(binary,makesingle);
            if (digit == 1)
            {
                std::cout << "sll $t" << tempno << ",$t1," << i - 1 << std::endl;
                binary += pow(2 , makesingle - 1);  
                tempno++;
                if(tempno == 10)
                {
                    if (i == count - 1)
                    {
                        dosub(true);
                    }
                    dosub(false);
                    tempno = 3;
                }
           
            }
            makesingle++;  
        } 

        //second part: subtractions and answer !!update done
        tempno -= 1;
        for (int i = 3; i < tempno; i++)
        {
            std::cout << "sub $t2,$t2,$t" << i << std::endl;
        }
        if(tempno != 2) //function has not printed the last instruction
        {
            std::cout << "sub $s2,$t2,$t" << tempno << std::endl;
        }
        
    }
    else
    {
        std::cout<<"sll $s2,$t1," << (count - 1)<< std::endl;
    }

    //any key to continue,i could make a goto to just restart the whole thing infinitely XD
    end:
    system("pause");
}