#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "budget.h"
#include "account.h"
#include "record.h"
#include "date.h"
#include"user.h"

using namespace std;


void check_month(Record ar[], int rnum, User & user){
  //function : calculate the monthly expenses already in the records in current month.
  //input : an array of records ar[], the number of records in the array rnum, the user information user.
  //output : None.
  string month=ar[rnum-1].date.month;
  string year=ar[rnum-1].date.year;
  for(int i=0;i<rnum;i++){
    if(ar[i].date.year==year && ar[i].date.month==month){
      if(ar[i].amount<0){
      user.budget.expenses-=ar[i].amount;
      }
    }
  }
}


void motify_date(Record ar[],int pos){
  //function : to change the date information of a record.
  //input : an array of records ar[], the position of the record pos.
  //output : None.
  cout << "Please enter the date(DD/MM/YYYY):";
  string date;
  cin >> date;
  int n = date.length();
  for (int i = 0; i < n; ++i){
    // change the character '/' into ' ' so as to use istringstream.
    if (date[i] == '/'){
      date[i] = ' ';
    }
  }
  istringstream out(date);
  //get day, month, year respectively.
  out >> ar[pos].date.day >> ar[pos].date.month >> ar[pos].date.year;
}

void choose_type(Record ar[], int pos, int &sign) {
  //function : choose the type of the record from the given list.
  //input : an array of records ar[], the position of the record pos, the sign of the amount (-1 for expense, 1 for income).
  //output : None.
  int i;
  cout<<"\n1.expense 2.income"<<endl;
  cout << "Please enter the type:";
	cin >> i;
  if (i == 1){
    //if it is an expense record.
    sign = -1;
    cout << endl;
    cout << "1. food expense" << endl;
    cout << "2. fixed expense" << endl;
    cout << "3. commodity expense" << endl;
    cout << "4. entertainment expense" << endl;
    cout << "Please enter the type of expense:";
    cin >> i;
    switch(i){
      case 1:
        ar[pos].type = "food_expense";
        break;
      case 2:
        ar[pos].type = "fixed_expense";
        break;
      case 3:
        ar[pos].type = "commodity_expense";
        break;
      case 4:
        ar[pos].type = "entertainment_expense";
        break;
    }
  }

  else{
    //if it is an income record.
    cout << "1. earned income" << endl;
    cout << "2. portfolio income" << endl;
    cout << "3. passive income" << endl;
    cout << "Please enter the type of expense:";
    cin >> i;
    switch(i){
      case 1:
        ar[pos].type = "earned_income";
        break;
      case 2:
        ar[pos].type = "portfolio_income";
        break;
      case 3:
        ar[pos].type = "passive_income";
        break;
    }
  }
}

void choose_account(Record ar[], Account ac[], int pos){
  //function: choose the type of the record from the given list.
  //input : an array of records ar[], the array of accounts ac[], the position of the record pos.
  //output : None.
  int i;
  cout<<"\n1.Cash 2.Bank Card 3.Credit Card"<<endl;
  cout << "Please enter the account:";
	cin >> i;
  switch(i){
    case 1:
      ar[pos].account = ac[0];
      break;
    case 2:
      ar[pos].account = ac[1];
      break;
    case 3:
      ar[pos].account = ac[2];
      break;
  }
}

void grow_record(Record * &ar, int &num){
  //function: enlarge the array if more records need to be added in.
  //input : a pointer pointing to the first element of the record array * ar, the number of new positions for storage num.
  //output : None.
  Record * ar_new = new Record [2 * num];

  for (int i = 0; i < num; i++){
    ar_new[i] = ar[i];
  }

  delete [] ar;
  ar = ar_new;
  num *= 2;
}

int load_record(string filename, Record * &ar, Account ac[], int &num){
  //function: import records from file.
  //input : the name of the source file filename, a pointer pointing to the first element of the record array * ar, the array of accounts ac[], the number of new positions for storage num.
  //output : the number of records imported from the file.
  ifstream fin;
  fin.open(filename.c_str());

  if (fin.fail()){
    cout << "Failed to open the file." << endl;
    exit(1);
  }

  int i = 0;
  string line;

  while(getline(fin, line)){
    if (i >= num){
      //enlarge the array.
      grow_record(ar, num);
    }

    if (i < num){
      istringstream line_in(line);
      line_in >> ar[i].date.day;
      line_in >> ar[i].date.month;
      line_in >> ar[i].date.year;
      line_in >> ar[i].type;
      line_in >> ar[i].account.name;
      line_in >> ar[i].amount;
      line_in >> ar[i].note;
      //change accounts' balance.
      ar[i].account.balance += ar[i].amount;
      i++;
    }
  }

   fin.close();
  return i;
}

void output_record(string filename, Record ar[], int &rnum){
  //function : output the records to a file when exitting the program.
  //input :  the name of the output file filename, the array of records ar[], the number of records rnum.
  //output : None.
  ofstream fout;
  fout.open(filename.c_str());
  if (fout.fail()){
    cout << "Failed to output records into " << filename << "." << endl;
    exit(1);
  }
  for (int i = 0; i < rnum; i++){
    fout << ar[i].date.day << " " << ar[i].date.month << " " << ar[i].date.year << " " << ar[i].type << " " << ar[i].account.name << " " << ar[i].amount << " " << ar[i].note << endl;
  }
  fout.close();
}

void show_record(Record ar[], int rnum){
  //function : print out all records in the file.
  //input : the array of records ar[], the number of records rnum.
  //output : None.
  cout << setw(7) << "Number" << setw(12) << "Date" << setw(20) << "Type" << setw(16) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
    for(int i = 0; i < rnum; i++){
    cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(20) << ar[i].type << setw(16) << ar[i].account.name << setw(10) << ar[i].amount << setw(20) << ar[i].note << endl;
  }
}

void edit_record(Record ar[], int rnum , User user){
  //function : edit one record in the file.
  //input : the array of records ar[], the number of records rnum, the user information user.
  //output : None.
  int x;
  char ans;
  double amount;
  show_record(ar, rnum);
  cout << "Please choose the record to edit:";
  cin >> x;

  int sign = ar[x-1].amount / abs(ar[x-1].amount);

  double origin_amount=ar[x-1].amount;

  cout << "Change the date(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    motify_date(ar, x - 1);
  }

  cout << "Change the type(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    choose_type(ar,x - 1, sign);
  }

  cout << "Change the amount(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    ar[x-1].account.balance -= ar[x-1].amount;
    cout << "Please enter the amount:";
    cin >> amount;
    ar[x-1].amount = amount * sign;
    ar[x-1].account.balance += ar[x-1].amount;
  }

  cout << "Change the note(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the note:";
    cin >> ar[x-1].note;
  }

  cout << "Modify completed!" << endl << endl;
  //check if the monthly expense has been over the budget.
  if(user.budget.check){
    if(sign==-1){
      if(ar[x-1].date.year==ar[rnum-1].date.year && ar[x-1].date.month==ar[rnum-1].date.month){
        user.budget.expenses+=origin_amount;
        user.budget.expenses-=ar[x-1].amount;
        user.check_budget();
      }
    }
  }
}

void delete_record(Record *&ar, Account ac[], int &rnum){
  //function : delete one record in the file.
  //input : a pointer pointing to the firt element of the record array * ar, the array of accounts ac[], the number of records rnum.
  //output : None.
  show_record(ar,rnum);
  char ans;
  int x;
  cout << "Please choose the record to be deleted:";
  cin >> x;
  cout << "Delete record " << x << "(Y/N)?";
  cin >> ans;

  if (ans == 'Y'){
    rnum--;
    Record * new_r = new Record [rnum];
    //restore the records.
    for (int i = 0; i < x - 1; i++){
      new_r[i] = ar[i];
    }
    for (int i = x; i <= rnum; i++){
      new_r[i-1] = ar[i];
    }
    ar = new_r;
  }

  cout << "Record " << x << " deleted." << endl << endl;
}

void add_record(Record ar[], Account ac[], int &rnum , User & user){
  //function : add new record to the account.
  //input : the array of records ar[], the array of accounts ac[], the number of records rnum, the user information user.
  //output : None.
  // flush the keyboard buffer.
	string str;
	getline(cin, str);
  int i,sign = 1;
  double d;

	motify_date(ar,rnum);
  choose_type(ar, rnum, sign);
  choose_account(ar, ac, rnum);

  cout << "Please enter the amount: ";
  cin >> d;
  ar[rnum].amount = d * sign;
  ar[rnum].account.balance += ar[rnum].amount;

  cout << "Please enter the note: ";
  cin>> ar[rnum].note;

  cout << endl;
  //display the information of the added record.
	cout << "Date:" << ar[rnum].date.showdate() << endl;
  cout << "Type:" << ar[rnum].type << endl;
  cout << "Account:" << ar[rnum].account.name << endl;
  cout << "Amount:" << ar[rnum].amount << endl;
  cout << "Note:" << ar[rnum].note << endl;
  cout << "1 record added." << endl << endl;
  //check if the monthly expsenses has been over the budget.
  if(user.budget.check==1){
    if(sign==-1){
      if(ar[rnum].date.year==ar[rnum-1].date.year && ar[rnum].date.month==ar[rnum-1].date.month){
        user.budget.expenses -= ar[rnum].amount;
        user.check_budget();
      }
    }
  }
  //update the number of records.
  rnum++;
}

void sort_record(Record ar[], int rnum){
  //function : sort the records by date or by amount.
  //input : the array of records ar[], the number of records rnum.
  //output : None.
  int i, j, idx;
  int x;
  cout << "1.Date 2.Amount" << endl;
  cout << "Choose how to sort the records:";
  cin >> x;

  Date min;
  double min1;
  switch(x){
    case 1:
    //sort by date.
    for (i = 0; i < rnum - 1; i++){
      //selection sort.
      min = ar[i].date;
      idx = i;
      for (j = i + 1; j < rnum; j++){
        if (ar[j].date.year < min.year || (ar[j].date.year == min.year && ar[j].date.month < min.month) || (ar[j].date.year == min.year && ar[j].date.month ==min.month && ar[j].date.day < min.day)){
          min = ar[j].date;
          idx = j;
        }
      }
      if (idx != i){
        Record temp;
        temp = ar[i];
        ar[i] = ar[idx];
        ar[idx] = temp;
      }
    }
    break;

    case 2:
    //sort by amount.
    for (i = 0; i < rnum - 1; i++){
      //selection sort.
      min1 = ar[i].amount;
      idx = i;
      for (j = i + 1; j < rnum; j++){
        if (ar[j].amount < min1){
          min1 = ar[j].amount;
          idx = j;
        }
      }
      if (idx != i){
        Record temp;
        temp = ar[i];
        ar[i] = ar[idx];
        ar[idx] = temp;
      }
    }
    break;
  }
}

void search_record(Record ar[], int rnum){
  //function : search certain records by date, type or account.
  //input : the array of records ar[], the number of records rnum.
  //output : None.
  cout << "1.Date 2.Type 3.Account" << endl;
  cout << "Choose which category you want to search by:";
  int x, count = 0;
  string ans;
  cin >> x;
  switch(x){
    case 1:
    //search by date.
    cout << "Please enter the date(DD/MM/YYYY):";
    cin >> ans;
    for(int i = 0; i < rnum; i++){
      string date = ar[i].date.showdate();
      if (date.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(20) << "Type" << setw(16) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(20) << ar[i].type << setw(16) << ar[i].account.name << setw(10) << ar[i].amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;

    case 2:
    //search by type.
    int i;
    cout<<"\n1.expense 2.income"<<endl;
    cout << "Please enter the type:";
  	cin >> i;
    //to choose a center type from the given list.
    if (i == 1){
      cout << endl;
      cout << "1. food expense" << endl;
      cout << "2. fixed expense" << endl;
      cout << "3. commodity expense" << endl;
      cout << "4. entertainment expense" << endl;
      cout << "Please enter the type of expense:";
      cin >> i;
      switch(i){
        case 1:
          ans = "food_expense";
          break;
        case 2:
          ans = "fixed_expense";
          break;
        case 3:
          ans = "commodity_expense";
          break;
        case 4:
          ans = "entertainment_expense";
          break;
      }
    }
    else{
      cout << "1. earned income" << endl;
      cout << "2. portfolio income" << endl;
      cout << "3. passive income" << endl;
      cout << "Please enter the type of expense:";
      cin >> i;
      switch(i){
        case 1:
          ans = "earned_income";
          break;
        case 2:
          ans = "portfolio_income";
          break;
        case 3:
          ans = "passive_income";
          break;
      }
    }

    for(int i = 0; i < rnum; i++){
      string type = ar[i].type;
      if (type.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << ar[i].amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;

    case 3:
    //search by account.
    cout << "Please enter the account:";
    //to choose a certain account from the given list.
    cout<<"\n1.Cash 2.Bank Card 3.Credit Card"<<endl;
    cout << "Please enter the account:";
  	cin >> i;
    switch(i){
      case 1:
        ans = "cash";
        break;
      case 2:
        ans = "bank_card";
        break;
      case 3:
        ans = "credit_card";
        break;
    }
    for(int i = 0; i < rnum; i++){
      string account = ar[i].account.name;
      if (account.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << ar[i].amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;
  }
  //print ht number of records satisfied.
  cout << count <<"record(s) found." << endl << endl;
}

void monthly_statement(Record ar[], int rnum){
  //function : output a monthly statement of certain month to the file.
  //input : the array of records ar[], the number of records rnum.
  //output : None.
  string year,month;
  cout << "Please input the year and the month you want to search:" << endl;
  cin >> year >> month;
  Record *  nr = new Record [rnum];
  int j = 0;
  for (int i = 0; i < rnum; i++){
    if (ar[i].date.year == year && ar[i].date.month == month){
      nr[j] = ar[i];
      j++;
    }
  }
  //get all records of the exact month.
  double total_expense = 0, food_expense = 0, fixed_expense = 0, commodity_expense = 0, entertainment_expense = 0;
  double total_income = 0, earned_income = 0, portfolio_income = 0, passive_income = 0, debt_expense = 0;
  for (int i = 0; i < j; i++){
    if (nr[i].type == "food_expense"){
      food_expense -= nr[i].amount;
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "fixed_expense"){
      fixed_expense -= nr[i].amount;
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "commodity_expense"){
      commodity_expense -= nr[i].amount;
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "entertainment_expense"){
      entertainment_expense -= nr[i].amount;
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "earned_income"){
      earned_income += nr[i].amount;
      total_income += nr[i].amount;
    }
    else if (nr[i].type == "portfolio_income"){
      portfolio_income += nr[i].amount;
      total_income += nr[i].amount;
    }
    else if (nr[i].type == "passive_income"){
      passive_income += nr[i].amount;
      total_income += nr[i].amount;
    }
  }
  for (int i = 0; i < j; i++){
    if (nr[i].account.name == "credit_card"){
      if(nr[i].amount<0){
      debt_expense -= nr[i].amount;
      }
    }
  }
  //calculate total amount of different types.


  string filename = "statement_of_" + year + "_" + month + ".txt";
  ofstream fout;
  fout.open(filename.c_str());

  if (fout.fail()){
    cout << "Opening " << filename << ".txt failed." << endl;
    exit(1);
  }

  fout << fixed << setprecision(2);
  fout << "******** Monthly Statement ********" << endl;
  fout << "************* " << year << ", " << month << " *************" << endl;

  fout << "Income: " << endl;

  if(total_income!=0){
    double earned_ratio = earned_income / total_income * 100;
    double portfolio_ratio = portfolio_income / total_income * 100;
    double passive_ratio = passive_income / total_income * 100;


    fout << left;
    fout << setfill('-');
    fout << setw(30) <<"  Earned income " << earned_income << "   " << earned_ratio << '%' << endl;
    fout << setw(30) <<"  Portfolio income " << portfolio_income << "   " << portfolio_ratio << '%' << endl;
    fout << setw(30) <<"  Passive Earned income " << passive_income << "   " << passive_ratio << '%' << endl;
  }

  fout << setw(30) <<"  Total income " << total_income << endl;
  fout << endl;

  fout << "Expenses: " << endl;

  if(total_expense!=0){
      double food_ratio = food_expense / total_expense * 100;
      double fixed_ratio = fixed_expense / total_expense * 100;
      double commodity_ratio = commodity_expense / total_expense * 100;
      double entertainment_ratio = entertainment_expense / total_expense * 100;

      fout << left;
      fout << setfill('-');
      fout << setw(30) <<"  Food expense " << food_expense << "   " << food_ratio << '%' << endl;
      fout << setw(30) <<"  Fixed expense " << fixed_expense << "   " << fixed_ratio << '%' << endl;
      fout << setw(30) <<"  Commodity expense " << commodity_expense << "   " << commodity_ratio << '%' << endl;
      fout << setw(30) <<"  Entertainment expense " << entertainment_expense << "   " << entertainment_ratio << '%' << endl;
    }

  fout << setw(30) <<"  Total expense " << total_expense << endl;
  fout << endl;

  if(total_expense!=0){
    double debt_ratio = debt_expense / total_expense * 100;
    fout << setw(30) <<"  Expense on debt " << debt_expense << "   " << debt_ratio << '%' << endl;
    fout << endl;
  }

  if(total_income!=0){
    double expenses_ratio = total_expense / total_income * 100;
    fout << setw(30) <<"  Expense over income " << expenses_ratio << '%' << endl;
  }

  fout.close();
  delete [] nr;
  //print monthly statement into the file.
  cout << "Monthly statement has successfully stored in " << filename << "!" << endl;
}

void financial_analysis(Record ar[], int rnum){
  //function : output a fanancial analysis of certain month to the file.
  //input : the array of records ar[], the number of records rnum.
  //output : None.
  string year,month;
  cout << "Please input the year and the month you want to search:" << endl;
  cin >> year >> month;
  Record * nr = new Record [rnum];
  int j = 0;
  for (int i = 0; i < rnum; i++){
    if (ar[i].date.year == year && ar[i].date.month == month){
      nr[j] = ar[i];
      j++;
    }
  }

  //get all records of the exact month.

  double total_expense = 0, food_expense = 0;
  double total_income = 0, earned_income = 0, portfolio_income = 0, passive_income = 0, debt_expense = 0;
  for (int i = 0; i < j; i++){
    if (nr[i].type == "food_expense"){
      food_expense -= nr[i].amount;
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "fixed_expense"){
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "commodity_expense"){
      total_expense -= nr[i].amount;
    }
    else if (nr[i].type == "entertainment_expense"){
      total_expense -= nr[i].amount;
    }
    else {
      total_income += nr[i].amount;
    }
  }
  for (int i = 0; i < j; i++){
    if (nr[i].account.name == "credit_card"){
      if(nr[i].amount<0){
      debt_expense -= nr[i].amount;
      }
    }
  }

  //calculate total amount of different types.

  string filename = "financial_analysis_" + year + "_" + month + ".txt";
  ofstream fout;
  fout.open(filename.c_str());
    if (fout.fail()){
        cout << "Opening " << filename << ".txt failed." << endl;
        exit(1);
    }

    if(total_expense==0 ){
        fout<<"Total expense = 0. Unable to analyse."<<endl;
    }
    if(total_income==0){
        fout<<"Total income = 0. Unable to analyse."<<endl;
    }
    //make sure that total expense and total income are not equal to zero (else may cause 'divided by zero')

    if(total_income!=0 && total_expense!=0){

  double food_ratio = food_expense / total_expense * 100;
  double debt_ratio = debt_expense / total_expense * 100;
  double expenses_ratio = total_expense / total_income * 100;

  //calculate ratios.

  fout << fixed << setprecision(2);
  fout << "******** Financial Analysis ********" << endl;
  fout << "************* " << year << " , " << month << " *************" << endl;
  fout << endl;
  fout << "Liability ratio = " << debt_ratio << '%' << endl;
  if (debt_ratio > 25){
    fout << "Liability ratio is too high. You may face the risk of being deep in debt!"<<endl;
  }
  else{
    fout << "Liability ratio is normal. You may not face debt risk!"<<endl;
  }
  fout << endl;
  fout << "Engel Ratio = " << food_ratio << '%' << endl;
  if (food_ratio > 30){
    fout << "Keep moving! You can be richer!"<<endl;
  }
  else{
    fout << "Congratulations! You are living a wealthy life!"<<endl;
  }
  fout << endl;
  fout << "Expense ratio = " << expenses_ratio << '%' << endl;
  if (expenses_ratio > 70){
    fout << "Spent too much! You need to save money!"<<endl;
  }
  else{
    fout << "Expense ratio is normal. Good Job!"<<endl;
  }
    }
  fout.close();
  cout << "Financial analysis has successfully stored in " << filename << "!" << endl;
}

int selection_menu(){
  //function:print the selection menu and return user's choice.
  //input : None.
  //output : choice for the selection menu.
	int choice;

	// print selection menu
  cout << "1. Print all records." << endl;
  cout << "2. Add a new record." << endl;
  cout << "3. Edit the record." << endl;
  cout << "4. Delete the record."<<endl;
  cout << "5. Set budget." << endl;
  cout << "6. Search the records by partial match of the name." << endl;
  cout << "7. Sort the records by date or amount." <<endl;
  cout << "8. Change login password." << endl;
  cout << "9. Show monthly statement." << endl;
  cout << "10. Show financial analysis of the month." << endl;
  cout << "0. Quit. " << endl;
  cout << "Please enter your choice: ";

	// read user selection
	cin >> choice;
	cout << endl;

	return choice;
}


int main(){
  User user;
  Account ac[3]={{"cash",0},{"bank_card",0},{"credit_card",0}};
  bool if_budget;

  //print the welcome screen.
  cout << "********************************" << endl;
  cout << "* Welcome to Accounting system *" << endl;
  cout << "********************************" << endl;
  cout << "Please log in." << endl;
  user.load_user();
  //check user name and password
  bool flag = user.user_login();
  if (flag){
    int num = 3;
    Record * ar = new Record [num];
    string str;
    cout << "Please enter the filename to import records: ";
    cin >> str;
    int rnum = load_record(str, ar, ac, num);
    int choice = selection_menu();
    while (choice != 0){
      switch (choice){
        case 1:
          show_record(ar, rnum);
          break;
        case 2:
          if (rnum >= num){
            grow_record(ar, num);
          }
          add_record(ar, ac, rnum, user);
          break;
        case 3:
          edit_record(ar, rnum, user);
          break;
        case 4:
          delete_record(ar, ac, rnum);
          break;
        case 5:
          user.set_budget();
          check_month(ar, rnum, user);
          user.check_budget();
          break;
        case 6:
          search_record(ar, rnum);
          break;
        case 7:
          sort_record(ar, rnum);
          break;
        case 8:
          user.set_password();
          break;
        case 9:
          monthly_statement(ar,rnum);
          break;
        case 10:
          financial_analysis(ar, rnum);
          break;
        default:
          cout << "Invalid input!!" << endl;
        }
  choice = selection_menu();
    }
  output_record(str, ar, rnum);
  user.output_user();
  cout << "Goodbye!" << endl << endl;
  delete [] ar;
  }
  else{
    cout << "Unsuccessful login." << endl;
    exit(1);
  }

  return 0;
}
