//
//
//                            PayOff3.h
//
//

#ifndef PAYOFF3_H
#define PAYOFF3_H
#include <Arrays.h>

class PayOff
{
public:

    PayOff(){};

    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;

private:
    
};

class PayOffCall : public PayOff
{
public:

    PayOffCall(MJArray Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;

private:

    MJArray Strike;

};


class PayOffPut : public PayOff
{
public:

    PayOffPut(MJArray Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;

private:

	MJArray Strike;

};

class PayOffDoubleDig : public PayOff
{
public:

	PayOffDoubleDig(MJArray Strike_);

	virtual double operator()(double Spot) const;
	virtual ~PayOffDoubleDig() {}
	virtual PayOff* clone() const;

private:

	MJArray Strike;

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

