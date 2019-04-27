#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

class Date{
public:
  string year, month, day;
  string showdate();
};

#endif
