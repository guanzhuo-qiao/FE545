//
//
//	                	BinomialTree.cpp
//	
//

#include <BinomialTreeAKI.h>
#include <Arrays.h>
#include <cmath>
#include<iostream>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

SimpleBinomialTreeAKI::SimpleBinomialTreeAKI(double Spot_,
											const Parameters& r_,
											const Parameters& d_,
											double Volatility_,
											unsigned long Steps_,
											double Time_,
											double Barrier_)
									   : Spot(Spot_), 
                                         r(r_),
                                         d(d_), 
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps),
											Barrier(Barrier_)
{
    TreeBuilt=false;
}

void SimpleBinomialTreeAKI::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot = 
                            InitialLogSpot+ r.Integral(0.0, thisTime) 
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(Time/Steps);

		for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j + 2, k++)
		{
			TheTree[i][k].resize(4);
			TheTree[i][k][0] = exp(movedLogSpot + j * sd);
		}
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleBinomialTreeAKI::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");

	for (long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j + 2, k++)
	{

		TheTree[Steps][k][1] = TheProduct.FinalPayOff(TheTree[Steps][k][0]);
		TheTree[Steps][k][2] = 0.0;
		if (TheTree[Steps][k][0]>=Barrier)
		{
			TheTree[Steps][k][3] = 1.0;
		}
		else 
		{
			TheTree[Steps][k][3] = 0.0;
		}
	}

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
        double ThisTime = index*Time/Steps;
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++)
        {
            double Spot = TheTree[index][k][0];
            double futureDiscountedValueHit = 
                            0.5*Discounts[index]*(TheTree[index+1][k][1]+TheTree[index+1][k+1][1]);
            TheTree[index][k][1] = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValueHit);
			double futureDiscountedValueNotHit =
				0.5*Discounts[index] * ((TheTree[index+1][k][1]*TheTree[index+1][k][3]+ TheTree[index + 1][k][2]*(1.0- TheTree[index + 1][k][3]))
					+ (TheTree[index + 1][k+1][1] * TheTree[index + 1][k + 1][3] + TheTree[index + 1][k + 1][2] * (1.0 - TheTree[index + 1][k + 1][3])));
			TheTree[index][k][2] = futureDiscountedValueNotHit;
			if (TheTree[index][k][0] >= Barrier)
			{
				TheTree[index][k][3] = 1.0;
			}
			else
			{
				TheTree[index][k][3] = 0.0;
			}
			/*std::cout << "\n" << TheTree[index][k][0] << " "
				<< TheTree[index][k][1] << " "
				<< TheTree[index][k][2] << " "
				<< TheTree[index][k][3] << " "
				<< "\n";*/
        }
		//std::cout << i << "\n";
    }
    return TheTree[0][0][2];
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

