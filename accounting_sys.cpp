#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int max_num=1000;
//set limited number of the records.

class User{
public:
  string username = "Kit";
  string password = "000000";
  int budget;
  bool user_login();
  void set_password();
  void set_budget();
};

struct Account{
  string name;
  double balance;
};

struct Date{
  string year, month, day
};

class Record{
public:
  string note;
  Date date;
  Account account;
  double amount;
  int type;
  char sign;
};


char sign_select[2] = {'+','-'};

string dtos(double n){
  //fuction: convert a double number into string format.
  ostringstream stream;
  stream << n;
  return stream.str();
}

bool User :: user_login(){
  //completed！！！！！
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
  //completed!!!
  int x;
  cout << "Please enter the budget:";
  cin >> x;
  budget = x;
  cout << "Budget set up."<< endl;
}

void User :: set_password(){
  //completed !!!!
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

void grow_record(Record * &ar, int &num){
  //completed !!!!
  //function: enlarge the array if more records need to be added in.
  Record * ar_new = new Record [2 * num];
  for (int i = 0; i < num; i++){
    ar_new[i] = ar[i];
  }
  delete [] ar;
  ar = ar_new;
  num *= 2;
}

int load_record(string filename, Record * &ar, int &rnum){
  //completed!!!
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
      line_in >> ar[i].date;
      line_in >> ar[i].type;
      line_in >> ar[i].account;
      line_in >> ar[i].sign;
      line_in >> ar[i].amount;
      line_in >> ar[i].note;
      i++;
    }
  }
  fin.close();
  return i;
}

void show_record(Record ar[], Account ac[], int rnum){
  ///我还没写account list！！！！！
  //function:print out all records in the file.
    for(int i = 0; i < num; i++){
    string amount = ar[i].sign + dtos(ar[i].amount);
    cout << setw(7) << "Number" << setw(12) << "Date" << setw(10) << "Type" << setw(10) << "Amount"<< setw(20) << "Note" << endl;
    cout << setw(7) << i+1 << setw(12) << ar[i].date << setw(10) << ar[i].type << setw(10) << amount << setw(20) << ar[i].note << endl;
  }
}

void edit_record(Record ar[], int rnum){
  //account list 没写！！！
  //function:edit one record in the file.
  show_record(ar,num);
  int x, amount, t;
  char ans;
  string correction;
  cout << "Please choose the record to edit:";
  cin >> x;

  cout << "Change the date(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the date:";
    cin >> ar[x-1].date;
  }

  cout << "Change the type(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the type:";
    cin >> ar[x-1].type;
  }

  cout << "Change the amount(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the amount:";
    cin >> ar[x-1].amount;
  }
  cout << "Change the note(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    cout << "Please enter the note:";
    cin >> ar[x-1].note;
  }
  cout << "Modify completed!"<< endl;
}

void delete_record(Record ar[], int &rnum){
  //balance modify没写！！！
  //function:delete one record in the file.
  //input:the array of all the records, the number of records.
  //output:None.
  show_record(ar,num);
  char ans;
  int x;
  cout << "Please choose the record to edit:";
  cin >> x;
  cout << "Delete record " << x << "(Y/N)?";
  cin >> ans;
  if (ans == 'Y'){
    num--;
    Record * new_r = new Record [num];
    for (int i = 0; i < x - 1; i++){
      new_r[i] = ar[i];
    }
    for (int i = x; i < num; i++){
      new_r[i] = ar[i];
    }
    ar = new_r;
  }
}

void add_record(Record ar[], Account ac[], int &rnum){
  //不知道account能不能用！！！
  //function: add new record to the account.
	string str;
	getline(cin, str); // flush the keyboard buffer
  int i;
  double d;
  cout << "If it is an income record please enter 0, otherwise please enter 1:";
  cin >> i;
  ar[rnum].sign = sign_select[i];
	cout << "Please enter the date: ";
	cin >> str;
  ar[rnum].date = str;
	cout << "Please enter the type: ";
	cin >> i;
  ar[rnum].type = i;
  cout << "Please choose the account:";
  //打印account
  cin >> i;
  ar[rnum].account = i;
  cout << "Please enter the amount: ";
  cin >> d;
  ar[rnum].amount = d;
  cout << "Please enter the note: ";
  cin >> str;
  ar[rnum].note = str;
	cout << "Date:\t" << ar[rnum].date << endl<< endl;
  cout << "Type:\t" << ar[rnum].type << endl << endl;
  cout << "Account:\t" << ac[ar[num].account] << endl << endl;
  cout << "Amount:\t" << ar[rnum].sign << ar[rnum].amount << endl << endl;
  cout << "Note:\t" << ar[rnum].note << endl << endl;
  cout << "Add to record (Y/N)? ";
  char ans;
	cin >> ans;
	if (ans == 'Y'){
    cout << "1 record added." << endl;
		rnum++;
	}
}

void sort_record(Record ar[], int rnum){
//啥都没写！！
}

void search_record(Record ar[], int rnum){
//啥都没写！！
}

void monthly_statement(Record ar[], int rnum, string year, string month){
  Record *nr= new Record[max_num];
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
  string filename="statement_of_"+year+"_"+month;
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
  cout<<"Monthly statement has successfully stored in "<<filename<<".tct!"<<endl;
  cout<<"Please enter the choice:"<<endl;
  cout<<"0. Back to main menu."<<endl;
  cout<<"1. Show financial analysis."<<endl;
  char choice;
  cin>>choice;
  if(choice=='1'){
    financial_analysis(debt_ratio,food_ratio,expenses_ratio,analysis_name);
  }
}

void financial_analysis(double debt_ratio, double food_ratio, double expenses_ratio, string year, string month){
  string filename="financial_analysis_"+year+"_"+month;
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
}

string selection_menu(){
  //可能还有更多功能要加！！！
	string choice;

	// print selection menu
  cout << "1. Add a new record." << endl;
  cout << "2. Print all records." << endl;
  cout << "3. Edit the record." << endl;
  cout << "4. Search the records by partial match of the name." << endl;
  cout << "5. Show monthly statement." << endl;
  cout << "6. Show financial analysis of the month." << endl;
  cout << "7. Set budget." << endl;
  cout << "8. Sort the records by date or amount." <<endl;
  cout << "9. Change login password." << endl;
  cout << "10. Add an account." << endl;
  cout << "0. Quit. " << endl;
  cout << "Please enter your choice: ";

	// read user selection
	cin >> choice;
	cout << endl;

	return choice;
}

int main(){
  User user;
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
        case "1":
          if (rnum >= num){
            grow_record(ar, num);
          }
          add_record(ar, rnum);
          break;
        case "2":
          show_record(ar, rnum);
          break;
        case "3":
          edit_record(ar, rnum);
          break;
        case "4":
          search_record(ar, rnum);
          break;
        case "5":
          monthly_statement(ar,rnum);
          break;
        case "6":
          financial_analysis(ar, rnum);
          break;
        case "7":
          user.set_budget();
          break;
        case "8":
          sort_record(ar, rnum);
          break;
        case "9":
          user.set_password();
          break;
        case "10":
          add_account(ac,anum);
          break;
        default:
          cout << "Invalid input!" << endl;
        }
  choice = selection_menu();
    }
  cout << "Goodbye!" << endl << endl;
  delete [] ar;
  }
  else{
    cout << "Unsuccessful login." << endl;
    exit(1);
  }

  return 0;
}
