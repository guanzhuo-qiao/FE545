//
//
//              SolveMain1.cpp
//
//
/*
Needs
    BlackScholesFormulas.cpp
    BSCallClass.cpp
    Normals.cpp
*/
#include <Bisection.h>
#include <Integration.h>
#include <cmath>
#include <iostream>
#include <BSCallClass.h>
#include <QuaCallClass.h>
#include <BlackScholesFormulas.h>

using namespace std;

int main()
{
  	double a;
	double b; 
	double c; 


	cout << "\nEnter a\n";
	cin >> a;

	cout << "\nEnter b\n";
	cin >> b;

	cout << "\nEnter c\n";
	cin >> c;


    double low,high;

    cout << "\nlower limit\n";
    cin >> low;

    cout << "\nhigh limit\n";
    cin >> high;

    double  stop_num;


	cout << "\nSteps you want to stop:\n";
	cin >> stop_num;

    QuaCall theQua(a,b,c);

	double integral= Integration(stop_num,low,high,theQua);

    cout << "\nThe integral of this quadratic function is " << integral << "\n";

    double tmp;
    cin >> tmp;

	return 0;
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

