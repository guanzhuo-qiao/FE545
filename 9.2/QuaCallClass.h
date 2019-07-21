//
//
//                  BSCallClass.h
//
//

#ifndef QUA_CALL_CLASS_H
#define QUA_CALL_CLASS_H
class QuaCall
{

public:

    QuaCall(double a_, double b_,
                     double c_);

    double operator()(double x) const;


private:

    double a;
    double b;
    double c;


};
#endif

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

