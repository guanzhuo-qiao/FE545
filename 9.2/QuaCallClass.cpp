//
//
//                      QuaCallClass.cpp
//
//

#include <QuaCallClass.h>
#include <BlackScholesFormulas.h>

QuaCall::QuaCall(double a_, double b_,
               double c_)
               :
               a(a_),b(b_),
               c(c_)
{}

double QuaCall::operator()(double x) const
{
    return Quadratic(a,b,c,x);
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

