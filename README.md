# Accouting system
## problem statement
**Learn how to manage our financial status is an important lesson for all of us. More and more people choose to use digital tools to manage their wealth efficiently. In this idea, we target to build an accounting system to help people keep track of their income and expense. Minimally, the system shall include basic functions including:**
- add records of income and expenses; 
- the records should contain some basic information, like amount, date, types of income or expense (e.g. food, game, salary, etc.), account (e.g cash, bank card, credit card, etc.); 
- the records could be deleted and edited at any time; 
- users could view their records by date, type, and account; 
- the system should provide statistical report of users’ financial state (e.g. monthly income and expenses, percentage of food expenses, etc.); 
- the accounting system allows budget setting. When expenses reach the budget, there should be an alert from the system. 
- the system could analyze users’ financial situation and give advice accordingly.
## problem setting
**The system includes two main files:
A file records personal financial information( balance);
A file records basic information of income and expenses(amount, date, types of income or expense (e.g. food, game, salary, etc.), account (e.g cash, bank card, credit card, etc.)).**
In the code we will have a few functions for information management:
```
show_records
```
List all records in a particular month in a file “records.txt”
`edit_record`
Allow users to edit one record in the system.
`delete_record`
Allow users to delete selected records from the system.
`add_record`
Add one record of income / expense to the system.
`monthly_statement`
List out the monthly income, expenses,  balance and debt in a file “monthly statement.txt”
`financial_analysis`
Calculate the percentage of each type and list them in a file “monthly financial analysis.txt”
