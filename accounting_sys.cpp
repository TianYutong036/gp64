#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

class User{
public:
  bool user_login();
  void set_password();
  void set_budget();
  string username;
  string password;
  int budget;
};

struct Account{
  string name;
  double balance;
};

class Date{
public:
  string year, month, day;
  string showdate();
};

struct Record{
  string note;
  Date date;
  Account account;
  double amount;
  string type;
  int sign;
};

string dtos(double n){
  //fuction: convert a double number into string format.
  ostringstream stream;
  stream << n;
  return stream.str();
}

bool User :: user_login(){
  //function: to check the username and password for login(3 attempts to enter the password).
  int i = 3;
  string un;
  while (1){
    cout << "Username:";
    cin >> un;
    if (un == username){
      break;
    }
    cout << "Incorrect username!"<<endl;
  }

  string pw;
  cout << "Password:";
  while (1) {
    cin >> pw;
    if (pw == password){
      return true;
    }
    i--;
    if (i == 0){
      return false;
    }

    cout << "Incorrect password. Please try again."<<endl;
    cout << "Password:";
  }
}

void User :: set_budget(){
  //function: to set a monthly budget.
  int x;
  cout << "Please enter the budget:";
  cin >> x;
  budget = x;
  cout << "Budget set up."<< endl;
}

void User :: set_password(){
  //function:reset the password.
  string pw, pwcheck;
  cout << "Please enter the original password:";
  cin >> pw;

  while (pw != password){
    cout << "Wrong password. Please try again." << endl;
    cout << "Please enter the original password:";
    cin >> pw;
  }

    cout << "Please enter the new password:";
    cin >> pw;
    cout << "Re-enter the new password:";
    cin >>pwcheck;

    while (pw != pwcheck){
      cout << "Wrong pastword entered! Please try again." << endl;
      cout << "Re-enter the new password:";
      cin >>pwcheck;
    }

      cout << "Password motified successfully."<< endl;
      password = pw;
}

string Date :: showdate(){
  //function: print the date in the format of "DD/MM/YYYY".
  string r = day +'/' + month + '/' + year;
  return r;
}

void motify_date(Record ar[],int pos){
  string date;
  cin >> date;
  int n = date.length();
  for (int i = 0; i < n; ++i){
    if (date[i] == '/'){
      date[i] = ' ';
    }
  }
  istringstream out(date);
  out >> ar[pos].date.day >> ar[pos].date.month >> ar[pos].date.year;
}

void choose_type(Record ar[], int pos, int &sign) {
  int i;
  cout<<"\n1.expense 2.income"<<endl;
  cout << "Please enter the type:";
	cin >> i;
  if (i == 1){
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
  int i;
  cout<<"\n1.Cash 2.Bank Card 3.Credit Card"<<endl;
  cout << "Please enter the account:";
	cin >> i;
  switch(i){
    case 1:
      ar[pos].account=ac[0];
      break;
    case 2:
      ar[pos].account=ac[1];
      break;
    case 3:
      ar[pos].account=ac[2];
      break;
  }
}

void grow_record(Record * &ar, int &num){
  //function: enlarge the array if more records need to be added in.
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
      grow_record(ar, num);
    }

    if (i < num){
      istringstream line_in(line);
      line_in >> ar[i].date.day;
      line_in >> ar[i].date.month;
      line_in >> ar[i].date.year;
      line_in >> ar[i].type;
      line_in >> ar[i].account;
      line_in >> ar[i].amount;
      ar[i].account.balance += ar[i].amount;
      line_in >> ar[i].note;
      i++;
    }
  }

   fin.close();
  return i;
}

void output_record(string filename, record &ar, int &rnum){
  ofstream fout;
  fout.open(filename.c_str());
  if(fout.fail()){
    cout<<"Failed to output records into "<<filename<<"."<<endl;
    exit(1);
  }
  for(int i=0;i<rnum;i++){
    fout<<ar[i].date<<" "<<ar[i].type<<" "<<ar[i].account<<" "<<ar[i].amount<<" "<<ar[i].note<<endl;
  }
  fout.close();
}

void User::load_user(User & user){
  string filename="user_info.txt";
  ifstream fin;
  fin.open(filename.c_str());
  if(fin.fail()){
    cout<< "Fail to get user information."<<endl;
    exit(1);
  }
    fin>>user.username;
    fin>>user.password;
    fin.close();
}

void User::output_user(User & user){
  string filename="user_info.txt";
  ofstream fout;
  fout.open(filename.c_str());
  if(fout.fail()){
    cout<<"Failed to output user information into "<<filename<<"."<<endl;
    exit(1);
  }
  fout<<user.username<<endl;
  fout<<user.password<<endl;
  fout.close();
}

void show_record(Record ar[], int rnum){
  //function:print out all records in the file.
    for(int i = 0; i < rnum; i++){
    string amount = ar[i].sign + dtos(ar[i].amount);
    cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
    cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << amount << setw(20) << ar[i].note << endl;
  }
}

void edit_record(Record ar[], int rnum){
  //function:edit one record in the file.
  show_record(ar,num);
  cout << "Please choose the record to edit:";
  cin >> x;

  int x;
  char ans;
  double amount;
  int sign = ar[x-1].amount / abs(ar[x-1].amount);

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
    getline(cin,ar[x-1].note);
  }

  cout << "Modify completed!"<< endl;
}

void delete_record(Record ar[], Account ac[], int &rnum){
  //function:delete one record in the file.
  show_record(ar,rnum);
  char ans;
  int x;
  cout << "Please choose the record to edit:";
  cin >> x;
  cout << "Delete record " << x << "(Y/N)?";
  cin >> ans;

  if (ans == 'Y'){
    rnum--;
    Record * new_r = new Record [rnum];
    for (int i = 0; i < x - 1; i++){
      new_r[i] = ar[i];
    }
    for (int i = x; i < rnum; i++){
      new_r[i] = ar[i];
    }
    ar = new_r;
  }
}

void add_record(Record ar[], Account ac[], int &rnum){
  //function: add new record to the account.
	string str;
	getline(cin, str); // flush the keyboard buffer
  int i,sign = 1;
  double d;

	cout << "Please enter the date: ";
	motify_date(ar,rnum);
  choose_type(ar, rnum, sign);
  choose_account(ar, ac, rnum);

  cout << "Please enter the amount: ";
  cin >> d;
  ar[rnum].amount = d * sign;
  ar[rnum].account.balance += ar[rnum].amount;

  cout << "Please enter the note: ";
  getline(cin,ar[rnum].note);

	cout << "Date:\t" << ar[rnum].date << endl;
  cout << "Type:\t" << ar[rnum].type << endl;
  cout << "Account:\t" << ar[num].account.name << endl;
  cout << "Amount:\t" << ar[rnum].amount << endl;
  cout << "Note:\t" << ar[rnum].note << endl;
  cout << "1 record added." << endl;
	rnum++;
}

void sort_record(Record ar[], int rnum){
  int i, j, idx;
  int x;
  cout << "1.Date 2.Amount" << endl;
  cout << "Choose how to sort the records:";
  cin >> x;
  switch(x){
    case 1:
    Date min;
    for (i = 0; i < rnum - 1; i++){
      min = ar[i].date;
      idx = i;
      for (j = i + 1; j < rnum; j++){
        if (ar[j].date.year < ar[i].date.year || (ar[j].date.year == ar[i].date.year && ar[j].date.month < ar[i].date.month) || (ar[j].date.year == ar[i].date.year && ar[j].date.month == ar[i].date.month && ar[j].date.day < ar[i].date.day)){
          min = ar[j].date;
          idx = j;
        }
      }
      if (idx != i){
        Record temp;
        temp = ar[i];
        ar[i] = ar[j];
        ar[j] = temp;
      }
    }
    break;

    case 2:
    double min;
    for (i = 0; i < rnum - 1; i++){
      min = ar[i].amount;
      idx = i;
      for (j = i + 1; j < rnum; j++){
        if (ar[j].amount < min){
          min = ar[j].amount;
          idx = j;
        }
      }
      if (idx != i){
        Record temp;
        temp = ar[i];
        ar[i] = ar[j];
        ar[j] = temp;
      }
    }
    break;
  }
}

void search_record(Record ar[], int rnum){
  cout << "1.Date 2.Type 3.Account" << endl;
  cout << "Choose which category you want to search by:";
  int x, count = 0;
  string ans;
  cin >> x;
  switch(x){
    case 1:
    cout << "Please enter the date(DD/MM/YYYY):";
    cin >> ans;
    for(int i = 0; i < rnum; i++){
      string date = ar[i].date.showdate();
      if (date.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;

    case 2:
    cout << "Please enter the type:";
    //print type list
    cin >> ans;
    for(int i = 0; i < rnum; i++){
      string type = ar[i].type;
      if (type.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;

    case 3:
    cout << "Please enter the account:";
    //print account list
    cin >> ans;
    for(int i = 0; i < rnum; i++){
      string account = ar[i].account.name;
      if (Account.find(ans) != -1){
        cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << << setw(10) << "Account" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
        cout << setw(7) << i+1 << setw(12) << ar[i].date.showdate() << setw(10) << ar[i].type << setw(10) << ar[i].account.name << setw(10) << amount << setw(20) << ar[i].note << endl;
        count++;
      }
    }
    break;
  }

  cout << count <<"record(s) found." << endl;
}

void monthly_statement(Record ar[], int rnum){
  string year,month;
  cout<<"Please input the year and the month you want to search:"<<endl;
  cin>>year>>month;
  Record *nr= new Record[rnum];
  int j=0;
  for(int i=0;i<rnum;i++){
    if(ar[i].date.year==year && ar[i].date.month==month){
      nr[j]=ar[i];
      j++;
    }
  }
  //get all records of the exact month.
  double total_expense=0, food_expense=0, fixed_expense=0, commodity_expense=0, entertainment_expense=0;
  double total_income=0, earned_income=0, portfolio_income=0, passive_income=0, debt_expense=0;
  for(int i=0;i<j;i++){
    if(nr[i].type=="food_expense"){
      food_expense+=nr[i].amount;
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="fixed_expense"){
      fixed_expense+=nr[i].amount;
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="commodity_expense"){
      commodity_expense+=nr[i].amount;
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="entertainment_expense"){
      entertainment_expense+=nr[i].amount;
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="earned_income"){
      earned_income+=nr[i].amount;
      total_income+=nr[i].amount;
    }
    else if(nr[i].type=="portfolio_income"){
      portfolio_income+=nr[i].amount;
      total_income+=nr[i].amount;
    }
    else if(nr[i].type=="passive_income"){
      passive_income+=nr[i].amount;
      total_income+=nr[i].amount;
    }
  }
  for(int i=0;i<j;i++){
    if(nr[i].account.name=="credit card"){
      debt_expense+=nr[i].amount;
    }
  }
  //calculate total amount of different types.
  double food_ratio=food_expense/total_expense*100;
  double fixed_ratio=fixed_expense/total_expense*100;
  double commodity_ratio=commodity_expense/total_expense*100;
  double entertainment_ratio=entertainment_expense/total_expense*100;
  double earned_ratio=earned_income/total_income*100;
  double portfolio_ratio=portfolio_income/total_income*100;
  double passive_ratio=passive_income/total_income*100;
  double expenses_ratio=total_expense/total_income*100;
  double debt_ratio=debt_expense/total_expense*100;
  //calculate ratios.
  string filename="statement_of_"+year+"_"+month+".txt";
  ofstream fout;
  fout.open(filename.c_str());
  if(fout.fail()){
    cout<<"Opening "<<filename<<".txt failed."<<endl;
    exit(1);
  }
  fout<<fixed<<setprecision(2);
  fout<<"******** Monthli Statement ********"<<endl;
  fout<<"********** "<<year<<", "<<month<<" **********"<<endl;
  fout<<"Income: "<<endl;
  fout<<"  Earned income --------"<<earned_income<<"   "<<earned_ratio<<'%'<<endl;
  fout<<"  Portfolio income --------"<<portfolio_income<<"   "<<portfolio_ratio<<'%'<<endl;
  fout<<"  Passive Earned income --------"<<passive_income<<"   "<<passive_ratio<<'%'<<endl;
  fout<<"Total income ----------------"<<total_income<<endl;
  fout<<endl;
  fout<<"Expenses: "<<endl;
  fout<<"  Food expense --------"<<food_expense<<"   "<<food_ratio<<'%'<<endl;
  fout<<"  Fixed expense --------"<<fixed_expense<<"   "<<fixed_ratio<<'%'<<endl;
  fout<<"  Commodity expense --------"<<commodity_expense<<"   "<<commodity_ratio<<'%'<<endl;
  fout<<"  Entertainment expense --------"<<entertainment_expense<<"   "<<entertainment_ratio<<'%'<<endl;
  fout<<"Total expense ----------------"<<total_expense<<endl;
  fout<<endl;
  fout<<"  Expense on debt --------"<<debt_expense<<"   "<<debt_ratio<<'%'<<endl;
  fout<<endl;
  fout<<"  Expense over income --------"<<expenses_ratio<<'%'<<endl;
  fout.close()
  delete []nr;
  //print monthly statement into the file.
  cout<<"Monthly statement has successfully stored in "<<filename<<"!"<<endl;
}

void financial_analysis(Record ar[], int rnum){
  string year,month;
  cout<<"Please input the year and the month you want to search:"<<endl;
  cin>>year>>month;
  Record *nr= new Record[rnum];
  int j=0;
  for(int i=0;i<rnum;i++){
    if(ar[i].date.year==year && ar[i].date.month==month){
      nr[j]=ar[i];
      j++;
    }
  }
  //get all records of the exact month.
  double total_expense=0, food_expense=0;
  double total_income=0, earned_income=0, portfolio_income=0, passive_income=0, debt_expense=0;
  for(int i=0;i<j;i++){
    if(nr[i].type=="food_expense"){
      food_expense+=nr[i].amount;
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="fixed_expense"){
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="commodity_expense"){
      total_expense+=nr[i].amount;
    }
    else if(nr[i].type=="entertainment_expense"){
      total_expense+=nr[i].amount;
    }
    else {
      total_income+=nr[i].amount;
    }
  }
  for(int i=0;i<j;i++){
    if(nr[i].account.name=="credit card"){
      debt_expense+=nr[i].amount;
    }
  }
  //calculate total amount of different types.
  double food_ratio=food_expense/total_expense*100;
  double expenses_ratio=total_expense/total_income*100;
  double debt_ratio=debt_expense/total_expense*100;
  //calculate ratios.
  string filename="financial_analysis_"+year+"_"+month+".txt";
  ofstream fout;
  fout.open(filename.c_str());
  if(fout.fail()){
    cout<<"Opening "<<filename<<".txt failed."<<endl;
    exit(1);
  }
  fout<<fixed<<setprecision(2);
  fout<<"******** Monthli Statement ********"<<endl;
  fout<<"********** "<<year<<", "<<month<<" **********"<<endl;
  fout<<endl;
  fout<<"Liability ratio = "<<debt_ratio<<'%'<<endl;
  if(debt_ratio>25){
    fout<<"Liability ratio is too high. You may face the risk of being deep in debt!"
  }
  else{
    fout<<"Liability ratio is normal. You may not face debt risk!"
  }
  fout<<endl;
  fout<<"Engel Ratio = "<<food_ratio<<'%'<<endl;
  if(food_ratio>30){
    fout<<"Keep moving! You can be richer!"
  }
  else{
    fout<<"Congratulations! You are living a wealthy life!"
  }
  fout<<endl;
  fout<<"Expense ratio = "<<expenses_ratio<<'%'<<endl;
  if(expenses_ratio>70){
    fout<<"Spent too much! You need to save money!"
  }
  else{
    fout<<"Expense ratio is normal. Good Job!"
  }
  fout.close();
  cout<<"Financial analysis has successfully stored in "<<filename<<"!"<<endl;
}

string selection_menu(){
  //可能还有更多功能要加！！！
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
  Account ac[3]={{"cash",0},{"bank card",0},{"credit card",0}};

  cout << "********************************" << endl;
  cout << "* Welcome to Accounting system *" << endl;
  cout << "********************************" << endl;
  bool flag = user.user_login();//check user name and password
  if (flag){
    int num = 3;
    Record * ar = new Record [num];
    string str;
    cout << "Please enter the filename to import records: ";
    cin >> str;
    int rnum = load_record(str, ar, num);
    string choice = selection_menu();
    while (choice != "0"){
      switch (choice){
        case 1:
          show_record(ar, rnum);
          break;
        case 2:
          if (rnum >= num){
            grow_record(ar, num);
          }
          add_record(ar, ac, rnum);
          break;
        case 3:
          edit_record(ar, rnum);
          break;
        case 4:
          delete_record(ar, ac, rnum);
          break;
        case 5:
          user.set_budget();
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
          cout << "Invalid input!" << endl;
        }
  choice = selection_menu();
    }
  output_record(str, ar, rnum);
  User::output_user(user);
  cout << "Goodbye!" << endl << endl;
  delete [] ar;
  }
  else{
    cout << "Unsuccessful login." << endl;
    exit(1);
  }

  return 0;
}
