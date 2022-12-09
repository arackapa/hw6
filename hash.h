#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime> 
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        srand(time(0)); 

        if(false == debug){
            generateRValues();
        }
    }


    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T a1, a2, a3, a4, a5, a6, result; 
        int index = (int)k.size() - 1; 
        unsigned long long w[5]; 
        int wCount = 4; 
        while (index >= 0)
        {
            if (index < 0) a6 = 0; 
            else a6 = letterDigitToNumber(k[index]); 
            index --; 

            if (index < 0) a5 = 0; 
            else a5 = letterDigitToNumber(k[index]); 
            index --; 

            if (index < 0) a4 = 0; 
            else a4 = letterDigitToNumber(k[index]); 
            index --; 

            if (index < 0) a3 = 0; 
            else a3 = letterDigitToNumber(k[index]); 
            index --; 

            if (index < 0) a2 = 0; 
            else a2 = letterDigitToNumber(k[index]); 
            index --; 

            if (index < 0) a1 = 0; 
            else a1 = letterDigitToNumber(k[index]); 
            index --; 
            w[wCount] = ((((((a1) * 36 + a2) * 36 + a3) * 36 + a4) * 36 + a5) * 36 + a6);
            wCount --; 
        }
        if (wCount != 0)
        {
            for (int i = wCount; i >= 0; i--)
            {
                w[i] = 0; 
            }
        }

        // printing out w array 
        // for (int i=0;i < 5; i++)
        // {
          // std::cout << "w[" << i << "] = " << w[i] << std::endl; 
        // }

        result = rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4]; 
        return result; 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T result; 
        int conversion = (int)letter;
        if (conversion >= 48 && conversion <= 57) 
        {
            conversion -= 22; 
        }
        else if (conversion >= 97 && conversion <= 122)
        {
            conversion -= 97; 
        }
        else if (conversion >= 65 && conversion <= 90)
        {
            conversion -= 65; 
        }
        result = conversion;
        
        return result; 
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
