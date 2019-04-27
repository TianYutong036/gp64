#include "date.h"

using namespace std;

string Date :: showdate(){
  //function : print the date in the format of "DD/MM/YYYY".
  //input : None.
  //output : None.
  string r = day +'/' + month + '/' + year;
  return r;
}
