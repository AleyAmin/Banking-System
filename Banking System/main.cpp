#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;
struct Customers
{
 int Arrival_time;
 int Waiting_time;
 int Transaction_duration;
 int Leaving_time;
 char* Service;
};
struct Teller
{
 int working_hours_of_Teller;
 int Teller_idle_time;
 int Teller_leaving_time;
};
float working_bank_hours ();
int no_of_Tellers ();
void working_hours_Teller ( int x , Teller T[], int y );
int no_of_customers_per_day ();
int input_transactions(char transactions[][50],int transaction_durations[]);
void customer_durations(int Num_of_transactions,int transaction_durations[],Customers C[],int Num_of_customers);
void Arrival_time(float Bank_working_hours, int Max_duration, Customers C[],int Num_of_customers);
int max_duration(Customers C[],int Num_of_customers);
void sorting_array(Customers C[],int Num_of_customers);
void teller_leavingtime (Teller T[],int Num_of_tellers);
void waiting_time(Customers C[],Teller T[],int Num_of_customers,int Num_of_tellers);
void leaving_time(Customers C[],int Num_of_customers);
int transaction_service(Customers C[],int Num_of_customers);
void output_txt(Customers C[],int Num_of_customers, int served);
void output_txt_T(Teller T[],int no_of_tellers);
int main()
{ int Num_of_customers,No_ofTellers,Num_of_transactions,Max_duration,served,transaction_durations[10];
 float bank_hours;
 char transactions[10][50];
 bank_hours = working_bank_hours ();
 No_ofTellers = no_of_Tellers ();
 Teller *T= new Teller[No_ofTellers];
 working_hours_Teller (No_ofTellers , T, bank_hours );
 Num_of_customers = no_of_customers_per_day ();
 Customers *C = new Customers[Num_of_customers];
 Num_of_transactions = input_transactions(transactions,transaction_durations);
 customer_durations(Num_of_transactions,transaction_durations,C,Num_of_customers);
 Max_duration = max_duration(C,Num_of_customers);
 Arrival_time(bank_hours,Max_duration,C,Num_of_customers);
 sorting_array(C,Num_of_customers);
 teller_leavingtime (T,No_ofTellers);
 waiting_time(C,T,Num_of_customers,No_ofTellers);
 leaving_time(C,Num_of_customers);
 served=transaction_service(C,Num_of_customers);
 output_txt(C,Num_of_customers,served);
 output_txt_T(T,No_ofTellers);
 cout<<" Tellers & Customers information has been generated into 2 seperate txt files "<<endl<< "successfully"<<endl;
 delete[] C;
 delete[] T;
 return 0;
}
int no_of_Tellers ()
{
int x;
do
{
cout<<" Please enter the numbers of Tellers : ";
cin>> x ;
}
while ( x <=0 || x>=50 );
return x;
}
float working_bank_hours ()
{
int x ;
do
{
cout<<" Please enter the working hours of the bank per day : ";
cin>> x ;
}
while ( x<=0 || x>=16 );
return x*60;
}
void working_hours_Teller ( int x ,Teller T[], int y )
{
for ( int i = 0 ; i < x ; i++ )
{
cout << " Working hours for teller number "<<i+1<<" = ";
cin>> T[i].working_hours_of_Teller;
T[i].working_hours_of_Teller*=60;
for ( int j =0 ; (T[i].working_hours_of_Teller> y)||(T[i].working_hours_of_Teller==0) ; j++ )
{
cout << " Working hours for teller number "<<i+1<<" again = ";
cin>> T[i].working_hours_of_Teller;
T[i].working_hours_of_Teller*=60;
}
}
}
int no_of_customers_per_day ()
{
int x = 0 ;
cout<<" please enter the number of customers per day ";
cin>>x ;
for ( int i =0 ; x<120 ||x>250; i++ )
 {
cout<<" please enter the number of customers per day again ";
cin>>x ;
 }
return x;
}
int input_transactions(char transactions[][50],int transaction_durations[])
{
 int Num_of_transactions;
 cout<<" Enter the amount of transactions available : ";
 cin>>Num_of_transactions;
 for(int i=0;Num_of_transactions>5||Num_of_transactions<=0;i++)
 {
 cout<<" Enter the amount of transactions available again : ";
 cin>>Num_of_transactions;
 }
 cout<<endl;
 for(int i =0;i<Num_of_transactions;i++)
 {
 cout<<" Enter type of transaction : "<<i+1<<" : ";
 cin.ignore();
 cin.getline(transactions[i],50);
 cout<<" Enter duration of transaction : "<<i+1<<" in minutes : ";
 cin>>transaction_durations[i];
 for(int j=0;transaction_durations[i]>60||transaction_durations[i]<=0;j++)
 {
 cout<<" Enter duration of transaction : "<<i+1<<" in minutes again : ";
 cin>>transaction_durations[i];
 }
 cout<<endl;
 }
 return Num_of_transactions;
}
void customer_durations(int Num_of_transactions,int transaction_durations[],Customers C[],int Num_of_customers)
{
 int tmp =0;
 srand(time(0));
 for (int i =0; i<Num_of_customers;i++)
 {
 tmp=rand()%Num_of_transactions;
 C[i].Transaction_duration= transaction_durations[tmp];
 }
}
void Arrival_time(float Bank_working_hours, int Max_duration, Customers C[],int Num_of_customers)
{
 int start_of_work_day =8*60;
 srand(time(0));
 for (int i =0; i<Num_of_customers;i++)
 {
 C[i].Arrival_time= start_of_work_day +rand()%int(Bank_working_hours-2*Max_duration);
 }
}
void sorting_array(Customers C[],int Num_of_customers)
{
 int mini,temp;
 for (int i = 0; i < Num_of_customers - 1; i++)
 {
 mini = i;
 for (int j = i + 1; j < Num_of_customers; j++)
 {
 if (C[j].Arrival_time < C[mini].Arrival_time)
 mini = j;
 }
 if (mini != i)
 {
 temp = C[mini].Arrival_time;
 C[mini].Arrival_time = C[i].Arrival_time;
 C[i].Arrival_time = temp;
 }
 }
}
int max_duration(Customers C[],int Num_of_customers)
{
 int max = 0;
 for(int i =0; i<Num_of_customers;i++)
 {
 if(max< C[i].Transaction_duration)
 max = C[i].Transaction_duration;
 }
 return max;
}
void waiting_time(Customers C[],Teller T[],int Num_of_customers,int Num_of_tellers)
{
 int temp[50] ,mini=2000, index,idle_temp,flag=0;
 for(int i=0;i<Num_of_tellers;i++)
 {
 temp[i]=8*60;
 T[i].Teller_idle_time=0;
 }
 for(int i =0; i<Num_of_customers;i++)
 {
 flag=0;
 for(int j=0;j<Num_of_tellers;j++)
 {
 if(C[i].Arrival_time>=T[j].Teller_leaving_time&&flag!=Num_of_tellers)
 {
 temp[j]=8000;
 flag++;
 }
 }
 for(int j=0;j<Num_of_tellers;j++)
 {
 if(mini>=temp[j])
 {
 mini = temp[j];
 index =j;
 }
 }
 if(C[i].Arrival_time>=temp[index]&&(flag !=Num_of_tellers))
 {
 idle_temp=(C[i].Arrival_time-temp[index]);
 T[index].Teller_idle_time+=idle_temp;
 C[i].Waiting_time=0;
 }
 else if(C[i].Arrival_time<temp[index]&&(flag !=Num_of_tellers))
 {
 C[i].Waiting_time=(-C[i].Arrival_time+temp[index]);
 idle_temp =0;
 }
 temp[index]+=(idle_temp+C[i].Transaction_duration);
 mini =temp[index];
 if (flag ==Num_of_tellers) C[i].Waiting_time=-1;
 }
}
void leaving_time(Customers C[],int Num_of_customers)
{
 for(int i =0; i<Num_of_customers;i++)
 {
 if(C[i].Waiting_time==-1)
 C[i].Leaving_time = C[i].Arrival_time;
 else
 C[i].Leaving_time = C[i].Arrival_time+C[i].Transaction_duration+C[i].Waiting_time;
 }
}
int transaction_service(Customers C[],int Num_of_customers)
{
 int count=0;
 srand(time(0));
 for(int i =0; i<Num_of_customers;i++)
 {
 bool tmp;
 if(C[i].Waiting_time==-1)
 {tmp = 0; C[i].Waiting_time=0;}
 else
 tmp= rand()%2;
 if(tmp==0)
 C[i].Service = "Not served";
 else
 {C[i].Service = "Served"; count++;}
 }
 return count;
}
void output_txt(Customers C[],int Num_of_customers, int served )
{
 ofstream File;
 File.open("Banking_system_simulation_results_Customers.txt");
 File<<"Customers per day";
 File<<endl<<endl;
 File<<"Start of working day is at 08:00 "<<endl<<endl;
 File<<"All of the following timings are in the 24 hour format except the waiting time in minutes"<<endl<<
endl;
 File<<"-----------------------------------------------------------------------------------------"<<endl;
 File<<setw(3)<<left<<"ID"<<" |"<<setw(9)<<"Arrival"<<" |"<<setw(6)<<
 "waiting"<<" |"<<setw(9)<<"Leaving"<<" |"<<setw(6)<<"Service"<<endl;
 for(int i =0;i<Num_of_customers;i++)
 {
 File<<setw(3)<<left<<i+1<<" | "<<setw(3)<<C[i].Arrival_time/60<<": "<<setw(3)<<C[i].Arrival_time%60<<
 " | "<<setw(6)<<C[i].Waiting_time<<" | "<<setw(3)<< C[i].Leaving_time/60<<": "<<setw(3)<<C[i].
Leaving_time%60<<" | "<<setw(3)<<C[i].Service<<endl;
 }
 File<<endl<<endl;
 File<<"Amount of served customers = "<<served<<" out of "<<Num_of_customers<<" Customers ";
 File.close();
}
void teller_leavingtime (Teller T[],int Num_of_tellers)
{
 for (int i =0;i<Num_of_tellers;i++)
 T[i].Teller_leaving_time=(T[i].working_hours_of_Teller+8*60);
}
void output_txt_T(Teller T[],int no_of_tellers)
{
 ofstream File;
 File.open("Banking_system_simulation_results_Tellers.txt");
 File<<"Tellers information per day";
 File<<endl<<endl;
 File<<"Start of working day is at 08:00 "<<endl<<endl;
 File<<"All of the following timings are in minutes"<<endl<<endl;
 File<<"-------------------------------------------"<<endl;
 File<<setw(3)<<left<<"ID"<<" |"<<setw(4)<<"Idle Time"<<" |"<<setw(4)<<
 "Utility Time"<<endl;
 for(int i =0;i<no_of_tellers;i++)
 {
 File<<setw(3)<<left<<i+1<<" | "<<setw(9)<<T[i].Teller_idle_time<<
 "| "<<setw(6)<<(T[i].working_hours_of_Teller)-(T[i].Teller_idle_time)<<endl;
 }
 File<<endl<<endl;
 File.close();
}
