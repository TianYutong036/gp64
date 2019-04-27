#ifndef RECORD_H_
#define RECORD_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "date.h"
#include "account.h"

using namespace std;

struct Record{
  string note;
  Date date;
  Account account;
  double amount;
  string type;
};

#endif
