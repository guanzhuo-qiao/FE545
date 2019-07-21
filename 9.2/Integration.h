//
//
//              Intergration.h
//
//

# include<cmath>

template<class T>
double Integration(double Stop_num,
                 double Low, 
                 double High,
                 T TheFunction) 
{
	double result = (High - Low)*TheFunction(Low);
	double n = 1.0;
    do
	{
	   double part = (High-Low)/n;
	   double sum = TheFunction(High) + TheFunction(Low);
	   for (unsigned long i = 1; i < n; i++)
	   {
		   sum = sum + 2.0*TheFunction(Low + i * part);
	   }
	   result = part / 2.0 * sum;
	   n = n + 1;
    }
    while 
        ( n<=Stop_num );

    return result;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

