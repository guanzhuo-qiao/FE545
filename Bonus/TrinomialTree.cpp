//
//
//	                	TrinomialTree.cpp
//	
//

#include <TrinomialTree.h>
#include <Arrays.h>
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

SimpleTrinomialTree::SimpleTrinomialTree(double Spot_,
									   const Parameters& r_,
									   const Parameters& d_,
									   double Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
									   : Spot(Spot_), 
                                         r(r_),
                                         d(d_), 
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps)
{
    TreeBuilt=false;
}

void SimpleTrinomialTree::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(2*i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot = 
                            InitialLogSpot+ r.Integral(0.0, thisTime) 
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(2*Time/Steps);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+1,k++)
              TheTree[i][k].first = exp(movedLogSpot+ j*sd);
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleTrinomialTree::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");

    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+1,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

	double delta_t = Time / Steps;
	double part1 = exp(Volatility*sqrt(delta_t / 2));

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
        double ThisTime = index*Time/Steps;
		double NextTime = (index+1) * Time / Steps;
		double part2 = exp((r.Integral(ThisTime, NextTime)-d.Integral(ThisTime, NextTime)) / 2);
		double p_u = pow((part2 - 1 / part1) / (part1 - 1 / part1), 2);
		double p_d = pow(( 1 / part1-part2 ) / (part1 - 1 / part1), 2);
		double p_m = 1 - p_u - p_d;
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+1,k++)
        {
            double Spot = TheTree[index][k].first;
			
            double futureDiscountedValue = 
                            Discounts[index]*(p_d*TheTree[index+1][k].second+p_m*TheTree[index+1][k+1].second + p_u * TheTree[index + 1][k + 2].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }
    return TheTree[0][0].second;
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

