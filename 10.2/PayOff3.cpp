//
//
//                          PayOff3.cpp
//
//

#include <PayOff3.h>
#include <minmax.h>

PayOffCall::PayOffCall(MJArray Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
    return max(Spot-Strike[0],0.0);
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}


double PayOffPut::operator () (double Spot) const
{
    return max(Strike[0]-Spot,0.0);
}

PayOffPut::PayOffPut(MJArray Strike_) : Strike(Strike_)
{
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
}

PayOffDoubleDig::PayOffDoubleDig(MJArray Strike_) : Strike(Strike_)
{
}

double PayOffDoubleDig::operator () (double Spot) const
{
	if (Spot < Strike[0] && Spot > Strike[1])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

PayOff* PayOffDoubleDig::clone() const
{
	return new PayOffDoubleDig(*this);
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

