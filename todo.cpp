#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<limits>
#include<ios>
#include<iomanip>
void addTask();
void showall();
void deleteTask();
void markDone();
void modifyData();
using namespace std;

void menuheader(int x){
	cout<<endl<<endl;
	for(int i=0;i<x;i++){
		cout << "\xB2";
	}
	cout << " TO_DO_LIST ";
	for(int i=0;i<x;i++){
		cout << "\xB2";
	}
	cout<<endl<<endl;	
}

class Task
{
	char task[60];
	int priority;
	public:
	void getTask()
	{
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
		system("cls");
		menuheader(40);
		cout << "\t"<<"Enter Your Task : ";
		cin.get(task, 60);
		cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
		cout <<"\t"<< "Enter the priority high or low (1 / 0)  : ";
		cin>>priority;
	}
	void taskHeader(){
		system("cls");
		menuheader(40);
		cout <<"  S NO"<< "\tTASK\t\t\t\t\t\t\t\t   PRIORITY "<<endl;
	}
	void outData(){
		cout<<"\t"<<setw(70)<<setiosflags(ios::left)<<task<<" "<<priority;
	}
};

void menu(void)
{
	int choice;
	linenor:
	system("color 0A");
	system("cls");
	menuheader(40);
	cout <<"\t"<< "1. Add a Task" << endl;
	cout <<"\t"<< "2. Mark as Done" << endl;
	cout <<"\t"<< "3. Delete Task"<<endl;
	cout <<"\t"<< "4. Modify Task"<<endl;
	cout <<"\t"<< "5. Show All Task"<<endl;
	cout <<"\t"<< "6. Exit"<<endl<<endl;
	cout <<"\t"<< "Enter Your Choice : ";
	cin>>choice;
	switch (choice)
	{
	case 1:
		addTask();
		goto linenor;
	case 2:
		markDone();
		goto linenor;
		break;
	case 3:
		deleteTask();
		goto linenor;
		break;
	case 4:
		modifyData();
		goto linenor;
		break;
	case 5:
		showall();
		goto linenor;
	case 6:
		exit(0);
		break;
	default:
		system("color 04");
		cout <<endl<<"\t"<< "Wrong Choice" << endl<<endl;
		system("pause");
		goto linenor;
	}
}

int main()
{
	menu();
	return 0;
}
//program funtion are declared here.....
void addTask()
{
	system("color 05");	
	Task t;
	fstream file;
	try{
		file.open("task.txt", ios::app);
		if(!file){
			system("color 04");
			cout <<endl<<"\t"<< "File Not Created" << endl<<endl;
			file.close();
			throw(1);
		}
		else{
			//cin.ignore(numeric_limits<streamsize>::max(),'\n'); //flushing the buffer (imp code)
			t.getTask();
			file.write((char*)&t,sizeof(t));
			file.close();	
			cout<<endl<<"\t"<<" Task Added "<<endl<<endl;
			system("pause");
			return;		
		}
	}
	catch(int x){
		cout <<"\t"<< "Restart the Program" << endl<<endl;
		exit(0);
	}
	
}
void showall(){
	system("color 0e");
	Task x;
	fstream file,tfile;
	tfile.open("task.txt", ios::in);
	try{
		file.open("task.txt", ios::in);
		if(!file){ 
			x.taskHeader();
			throw(1);
		}
		else{
			x.taskHeader();
			int i=1;
			if(tfile.read((char*)&x, sizeof(x))){
				tfile.close();
			}
			else{
				cout<<"\t No Task Available"<<endl;
				cout<<"\t Add Task To View"<<endl;
				tfile.close();
				system("pause");
				return;
			}
			while(file.read((char*)&x, sizeof(x))){
				cout<<"   "<<i;
				x.outData();
				cout<<endl;
				i++;
			}
			file.close();
			cout<<endl<<"\t"<<" ALL TASKS DISPLAYED "<<endl<<endl;
			system("pause");
			return;
		}
	}
	catch(int x){
		cout<<"\t No Task Available"<<endl;
		cout<<"\t Add Task To View"<<endl;
		file.close();
		system("pause");
		return;
	}
}
void deleteTask(){
	showall();
	system("color 06");
	int del,i=1,flag=0;
	Task x;
	fstream tfile;
	tfile.open("task.txt",ios::in);
	if(tfile.read((char*)&x, sizeof(x))){
		tfile.close();
	}
	else{
		cout<<"\t No Record Available"<<endl;
		tfile.close();
		system("pause");
		return;
	}
	cout<<"\n\n\tEnter the S.NO. of Task to delete : ";
	cin>>del;
	fstream dfile;
	fstream rfile;
	dfile.open("task.txt",ios::in);
	if(!dfile){
		cout<<"\n\tfile not found"<<endl;
	}
	rfile.open("temp.txt",ios::out);
	if(!rfile){
		cout<<"\n\t Record Can't be deleted'"<<endl;
	}
	while(dfile.read((char*)&x, sizeof(x))){
				if(i==del){
					flag=1;
					cout<<"\n\tThe deleted record is : \n"<<endl;
					x.outData();
					cout<<endl;
				}
				else{
					rfile.write((char*)&x,sizeof(x));
					i++;
				}
				
			}
	dfile.close();
	rfile.close();
	remove("task.txt");
	rename("temp.txt","task.txt");
	if(flag==1){
		cout<<"\n\t Record Deleted"<<endl<<endl;
	}
	else{
		cout<<"\n\t Record not found"<<endl<<endl;
	}
	system("pause");
	return;
}
void markDone(){
	showall();
	system("color 07");
	int del,i=1,flag=0;
	Task x;
	fstream tfile;
	tfile.open("task.txt",ios::in);
	if(tfile.read((char*)&x, sizeof(x))){
		tfile.close();
	}
	else{
		cout<<"\t Add Record to Mark them as Done"<<endl;
		tfile.close();
		system("pause");
		return;
	}
	cout<<"\n\n\tEnter the S.NO. of Task Which is Done : ";
	cin>>del;
	fstream dfile;
	fstream rfile;
	dfile.open("task.txt",ios::in);
	if(!dfile){
		cout<<"\n\tfile not found"<<endl;
	}
	rfile.open("temp.txt",ios::out);
	if(!rfile){
		cout<<"\n\t Record Can't be Mark as Done"<<endl;
	}
	while(dfile.read((char*)&x, sizeof(x))){
				if(i==del){
					flag=1;
					cout<<"\n\tThe record is : \n"<<endl;
					x.outData();
					cout<<endl;
				}
				else{
					rfile.write((char*)&x,sizeof(x));
					i++;
				}
				
			}
	dfile.close();
	rfile.close();
	remove("task.txt");
	rename("temp.txt","task.txt");
	if(flag==1){
		cout<<"\n\t Record Mark as Done"<<endl<<endl;
	}
	else{
		cout<<"\n\t Record not found"<<endl<<endl;
	}
	system("pause");
	return;
}
void modifyData(){
	showall();
	system("color 03");
	int del,i=1,flag=0;
	Task x;
	fstream tfile;
	tfile.open("task.txt",ios::in);
	if(tfile.read((char*)&x, sizeof(x))){
		tfile.close();
	}
	else{
		cout<<"\t Add Record to Modify them "<<endl;
		tfile.close();
		system("pause");
		return;
	}
	cout<<"\n\n\tEnter the S.NO. of Task Which you want to modify : ";
	cin>>del;
	fstream dfile;
	fstream rfile;
	dfile.open("task.txt",ios::in);
	if(!dfile){
		cout<<"\n\tfile not found"<<endl;
	}
	rfile.open("temp.txt",ios::out);
	if(!rfile){
		cout<<"\n\t Record Can't be Modify"<<endl;
	}
	while(dfile.read((char*)&x, sizeof(x))){
				if(i==del){
					flag=1;
					cout<<"\n\t Enter The new Record is : \n"<<endl;
					x.getTask();
					rfile.write((char*)&x,sizeof(x));
					cout<<endl;
				}
				else{
					rfile.write((char*)&x,sizeof(x));
					i++;
				}
				
			}
	dfile.close();
	rfile.close();
	remove("task.txt");
	rename("temp.txt","task.txt");
	if(flag==1){
		cout<<"\n\t Record Modify"<<endl<<endl;
	}
	else{
		cout<<"\n\t Record can't be modified"<<endl<<endl;
	}
	system("pause");
	return;
}







