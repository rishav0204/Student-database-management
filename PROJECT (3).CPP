#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include<iomanip.h>

//File where the data is stored is student.dat


class date
{
	int d;
	int m;
	int y;
public:
	void getdate();
	void show()
	{
		cout<<d<<"\\"<<m<<"\\"<<y;
	}

};

void date::getdate()
{
	do
	{
		cout<<"\n\t\tdd ->";
		cin>>d;
		cout<<"\t\tmm ->";
		cin>>m;
		cout<<"\t\tyyyy ->";
		cin>>y;
		if((d<1||d>31)||(m<1||m>12)||(y<1990||y>2019))
			cout<<"Invalid date of birth entered. Make sure you have entered a valid date.\n";
	}
	while((d<1||d>31)||(m<1||m>12)||(y<1990||y>2019));
}

class student
{
	char name[35];
	int roll;
	date dob;
	int admn;
	int std;
	char sec;
	char stream[12];
	char sub[5][20];
	float marks[2][5][2];			//marks[sem][sub][theory/internal]
	float tot_marks[5][3];					//tot_marks[sub][total type]   where total type 0 =>sem1, 1=>sem2, 2=>total(out of 200)
	void getsubs();
	void get_total();			//sets the values of tot_marks by reading marks
	void null_student();
public:
	student()
	{
		null_student();
	}
	void create();	//create a new student entry...
	void getstream();//For class 10th going to 11th students. Gives stream options to students.
	void getmarks();	//get marks for the various subjects.
	void delete_student();	// Assigns null value to all data members
	void display();	//Display student report case
	float getavg();	//Returns the average marks scored by a student in all subjects
	void student_record();
	int check_admn(int);
	void SetAsMax();
	void show_marks();
	void null_marks();
	void setAdmn(int x)
	{
		admn=x;
	}
};

int getoption();//MENU OPERATION. Provides an interactive interface to the users

int admission_no=0;    //Maximum admission number that has been assigned to any student in the school

int getadmn();	//Gets admission number for any required operation

void list(); //shows the name class and section for the admission nos.

void Add();

void Modify(int);

void Delete(int);

int GetPosition(int);

void ReportCard(int);

void max_admno();

void main()
{
	clrscr();
	max_admno();
	int x=1, admn=0;
	do
	{
		switch(getoption())
		{
			case 1:	clrscr();
				++admission_no;
				Add();
				cout<<"\n\nOperation compleated successfully...";
				break;
			case 2: clrscr();
				list();
				getch();
				break;

			case 3:	clrscr();
				admn=getadmn();
				if(admn!=-1)
					Modify(admn);
				getch();
				break;

			case 4: clrscr();
				admn=getadmn();
				if(GetPosition(admn)>-1)
				{
					int pos=GetPosition(admn);
					{
							fstream f("student.dat", ios::binary|ios::in|ios::out);
							f.seekg(pos);
							student s;
							f.read((char*) &s,  sizeof(s));
							f.seekp(pos);
							s.getmarks();
							f.write((char*) &s, sizeof(s));
							f.close();

					}
				}
				getch();
				break;
			case 5: clrscr();
				admn=getadmn();
				if(GetPosition(admn)>-1)
				{
					int pos=GetPosition(admn);
					{
							fstream f("student.dat", ios::binary|ios::in|ios::out);
							f.seekg(pos);
							student s;
							f.read((char*) &s,  sizeof(s));
							f.seekp(pos);
							s.getmarks();
							f.write((char*) &s, sizeof(s));
							f.close();
					}

				}
				getch();
				break;

			case 6:	clrscr();
				admn=getadmn();
				fstream fio("student.DAT", ios::binary|ios::in|ios::out);
				student S;
				while(!fio.eof()&&fio.read((char*) &S, sizeof(S)))
				{
					if(S.check_admn(admn) == 1)
					{
						break;
						S.null_marks();
						fio.seekg(fio.tellg()-sizeof(S), ios::beg);
						fio.write( (char*) &S, sizeof(S));
					}
				}
				break;

			case 7:	clrscr();
				admn=getadmn();
				ifstream fin1("student.DAT", ios::binary);
				student S1;
				while(!fin1.eof() && fin1.read((char*) &S1, sizeof(S1)))
				{
					if(S.check_admn(admn)==1)
					{
						S1.show_marks();
						break;
					}
				}
				break;

			case 8: clrscr();
				admn=getadmn();
				Delete(admn);
				getch();
				break;

			case 9: clrscr();
				admn=getadmn();
				if(admn>-1)
					ReportCard(admn);
				getch();
				break;

			case 10: x=0;
				break;

			case 2308:
				clrscr();
				cout<<"Are you sure you want to delete all data??? Enter y to continue and any other char to cancel: ";
				char k='n';
				cin>>k;
				if(k=='y')
				{
					remove("student.DAT");
					ofstream x("student.dat", ios::binary);
					x.close();
				}
				clrscr();
				break;

			default:
				break;
		}

	}
	while(x);
}

void ReportCard(int admn)
{
	student s;
	ifstream fin("student.dat", ios::binary);
	int pos=GetPosition(admn);
	fin.seekg(pos);
	fin.read((char*) &s, sizeof(s));
	if(pos==-1)
		cout<<"No Entry found";
	else
		s.display();
	fin.close();
}

int student::check_admn(int x)
{
	if (x==admn)
		return 1;
	else
		return 0;
}

void student::null_student()
{
	strcpy(name, "");
	std=-1;
	sec= '\0';
	roll=-1;
	admn=-1;
	for(int i=0; i<5; i++)
	{
		strcpy(sub[i],"");
		for(int j=0; j<2; j++)
			for(int k=0; k<2; k++)
				marks[j][i][k]=-1;
		tot_marks[i][2]=-1;
		tot_marks[i][1]=-1;
		tot_marks[i][0]=-1;

	}
	strcpy(stream, "");
}

int getoption()
{
	clrscr();
	int opt;
	do
	{
	for(int i=0; i<79; i++)
		cout<<"=";
	cout<<"\n\t\t\t\t||STUDENT MANAGEMENT||\n";
	for(int j=0; j<79; j++)
	    cout<<"=";
	cout	<<"\n\t\t\t1\t-\tAdd New Student\n"
		<<"\t\t\t2\t-\tList all student entries\n"
		<<"\t\t\t3\t-\tModify student details\n"
		<<"\t\t\t4\t-\tAdd marks\n"
		<<"\t\t\t5\t-\tModify marks\n"
		<<"\t\t\t6\t-\tDelete marks\n"
		<<"\t\t\t7\t-\tDisplay marks\n"
		<<"\t\t\t8\t-\tDelete student\n"
		<<"\t\t\t9\t-\tDisplay report card\n"
		<<"\t\t\t10\t-\tExit\n";
		for(int k=0; k<79; k++)
			cout<<"=";
	cout	<<"\n\n\t\t\t"<<setw(28)<<"Enter the desired option: ";
		    cin>>opt;
	    if((opt<1||opt>10)&&opt!=2308)
		{
			clrscr();
			cout<<"\aYOU ENTERED A WORNG OPTION\n\n**PRESS ENTER TO CONTINUE**";
			getch();
			clrscr();
			cout<<endl;
		}
	}
	while((opt<1||opt>10)&&opt!=2308);
	return opt;
}

void student::create()
{
	admn=admission_no;
	cout<<"Enter the following student details:\n\n"
	    <<setw(15)<<"Name"<<setw(10)<<":\t";
	gets(name);
	cout<<setw(15)<<"Date of Birth\n";
	dob.getdate();
	do
	{	clrscr();
		cout<<"Enter the following student details:\n\n"  ;
		cout<<setw(15)<<"Class"<<setw(10)<<":\t";
		cin>>std;
		if(std<1||std>12)
		{
			cout<<"\tInvalid class entered. Please Enter a class between 1 to 12:\n\nPress Enter to continue... " ;
			getch();
			clrscr();
		}
	}
	while(std<1||std>12);
	if(std==11)
	{
		getstream();
	}
	else
	{
		clrscr();
		cout<<"Enter the following student details:\n\n"  ;
		cout<<setw(15)<<"\nEnter the section"<<setw(10)<<":\t";
		cin>>sec;
		sec=toupper(sec);
		if (std==12)
		{
			switch(sec)
			{
				case 'A':
					strcpy(stream, "Science");
					break;
				case 'B':
					strcpy(stream, "Commerce");
					break;
				case 'C':
					strcpy(stream, "Humanities");
					break;
				
				default:
					strcpy(stream, "-N/a-");
			}
		}
	}
	clrscr();
	cout<<"Enter the following student details:\n\n"  ;
	cout<<setw(15)<<"Roll No"<<setw(10)<<":\t";
	cin>>roll;
	getsubs();
}

void student::getsubs()
{
	if(std<11)      //no branch division
	{
	       strcpy(sub[0], "Maths");
	       strcpy(sub[1], "Science");
	       strcpy(sub[2], "Social Studies");
	       strcpy(sub[3], "English");
		   if(std<9)
				strcpy(sub[4], "Hindi");
			else
			{
				cout	<<"\nEnter optional subject selected for class "<<std<<": \n"
						<<setw(15)<<"(a)"<<"\tHindi\n"
						<<setw(15)<<"(b)"<<"\tSanskrit";
				char ch;
				cout<<endl<<setw(15)<<""<<"--> ";
				do
				{
					cin>>ch;
					ch=tolower(ch);
					switch(ch)
					{
						case 'a': strcpy(sub[4], "Hindi"); break;
						case 'b': strcpy(sub[4], "Sankrit"); break;
						default: cout<<"\tWrong option entered. Enter valid option: ";
							 clrscr();
							 break;
					}
				}
				while(ch!='a'&&ch!='b');

			}
	}
	else                         //for class 11 and 12 stream required
	{
		switch(sec)
		{
			case 'A': //science
			{
				strcpy(sub[0], "Chemistry");
				strcpy(sub[1], "Physics");
				strcpy(sub[2], "English");
				clrscr();
				cout<<"Select the optional subjects:\n";
				cout<<"\tEnter \n\t(a) if subject is Maths \n\t(b) if subject is Biology\n\t(c) if you have both\n\n\t=> ";
				char ch;
				do
				{
					cin>>ch;
					ch=tolower(ch);
					switch(ch)
					{
						case 'a': strcpy(sub[3], "Maths"); break;
						case 'b': strcpy(sub[4], "Maths");
						case 'c': strcpy(sub[3], "Biology"); break;
						default: cout<<"\tWrong option entered. Enter valid option: ";
					}
				}
				while(ch!='a'&&ch!='b'&&ch!='c');
				if(ch!='c')
				{
				cout<<"\n\tEnter \n\t(a) if subject is C++ \n\t(b) if subject is Physical Education\m\t=> ";
				do
				{
					cin>>ch;
					switch(ch)
					{
						case 'a': strcpy(sub[4], "C++"); break;
						case 'b': strcpy(sub[4], "Physical Education");
							  break;
						default: cout<<"\tWrong option entered. Enter valid option: ";
					}
				}
				while(ch!='a'&&ch!='b');
				}
				break;
			}
			case 'B':
			{       char ch;
				strcpy(sub[0], "English");
				strcpy(sub[1], "Buisness Studies");
				strcpy(sub[2], "Accountancy");
				strcpy(sub[3], "Economics");
				cout<<"\tEnter \n\t(a) if subject is C++ \n\t(b) if subject is Physical Education  \n\t(c) if subject is Maths: ";
				do
				{
					cin>>ch;
					switch(ch)
					{
						case 'a': strcpy(sub[4], "C++"); break;
						case 'b': strcpy(sub[4], "Physical Education"); break;
						case 'c': strcpy(sub[4], "Maths"); break;
						default: cout<<"\tWrong option entered. Enter valid option: ";
					}
				}
				while(ch!='a'&&ch!='b'&&ch!='c');
				break;

			}
			case 'C':
			{   char ch;
				strcpy(sub[0], "English");
				strcpy(sub[1], "C++");
				strcpy(sub[2], "Geography");
				strcpy(sub[3], "Economics");
				strcpy(sub[4], "Physical Education");
				break;
			}
		}
	}
}

int getadmn()
{

	int admn=-1;
	if (admission_no>=0)
	{
			cout<<"Enter the admission number of the student: ";
			cin>>admn;
			if(admn>admission_no||admn<0)
			{
				clrscr();
				cout<<"Invalid admission number. Pls try again" ;
				getch;
				clrscr();
			}
	}
	else
		cout<<"No entries found";

	return admn;
}

void student::getmarks()
{
	for(int j=0; j<2; j++)
	{
		clrscr();
		cout <<"Enter the marks scored by "<<name<<" in class "<<std<<" in:\n\t"<<j+1<<"st semester: \n";
		for(int i=0; i<5; ++i)
		{
			cout<<"\t"<<sub[i]<<": \n\t\t Theory:  ";
			cin>>marks[j][i][0];
			if (marks[j][i][0]<0||marks[j][i][0]>70)
			{	
				cout<<"\n \tThe theory marks entered should be between 0 to 70. Please try again..\n";
				i--;
				continue;
			}
			cout<<"\t\tInternals:  ";
			cin>>marks[j][i][1];
			if (marks[j][i][1]<0||marks[j][i][1]>30)
			{	
				cout<<"\n \tThe internal marks entered should be between 0 to 30. Please try again..\n";
				i--;
			}
		}
		cout<<"\n\nPress Enter to continue...";
		getch();
	}
	get_total();
}

void student::display()
{
	int ab=0;
	for(int a=0; a<5; a++)
	{
			if (tot_marks[a][2]==-1)
			{
				ab++;
			}
	}
	if(ab!=5)
	{
		clrscr();
		for(int i=0; i<79; i++)			//print a line of '-'
			cout<<"-";

		cout<<"\t\t\t\t||||||||||STUDENT REPORT CARD||||||||||\n";
		
		for(int j=0; j<79; j++)			//print a line of '-'
			cout<<"-";
		
		cout<<"\n\n\tName\t\t:\t"<<name
			<<"\n\tDob\t\t:\t";
		dob.show();
		cout<<"\n\tAdmission No\t:\t"<<admn<<"\n";

		for(int p=0; p<79; p++)			//print a line of '-'
			cout<<"-";
		
		cout<<"\n\n\tClass\t:\t"<<std<<"\tSec\t:\t"<<sec<<"\tStream\t:";

		if (std<11)
			cout<<"-N/A-\n\n";
		else
			cout<<setw(10)<<stream<<"\n\n";

		for(int l=0; l<79; l++)		//print a line of '-'
			cout<<"-";
		
		cout<<endl
				<<"Subject"<<setw(15-strlen("subject"))<<""<<"Semester 1"<<setw(25-strlen("semester 1"))<<""<<"Semester 2"<<setw(25-strlen("semester 1"))<<""<<"Total\n"
				<<setw(15)<<""<<"Theory"<<setw(6)<<""<<"Internal"<<setw(5)<<""<<"Theory"<<setw(6)<<""<<"Internal"<<setw(5)<<"\n\n";

		for(int k=0; k<5; ++k)
		{
			cout<<sub[k]<<setw(15-strlen(sub[k]))<<""<<marks[0][k][0]<<setw(10)<<""<<marks[0][k][1]<<setw(11)<<""<<marks[1][k][0]<<setw(10)<<""<<marks[1][k][1]<<setw(11)<<""<<tot_marks[k][2]<<"\n";
		}
		

		for(int m=0; m<79; m++)
			cout<<"=";

		cout<<"\nThe average marks scored by "<<name<<" is "<<getavg()<<"\n";

		for(int n=0; n<79; n++)
			cout<<"=";
	}
	else
		cout<<"\n\nPlease add/update marks to view the report card";
	}


	float student::getavg()
	{
		int avg=0;
		for(int j=0; j<5;++j)
		{
			avg+=tot_marks[j][2];
		}
		avg/=5;
		float percent =  (avg/200.0)*100;
		return percent;
	}

	void student::student_record()
	{
		int num_of_dig=0;
		{
			int x=roll;
			while(x!=0)
			{
				x=x/10;
				num_of_dig++;
			}
		}
		cout<<admn<<"\t"<<name<<setw(31-strlen(name))<<std;
		cout<<"\t\t"<<sec<<"\t\t "<<roll<<"\n";
}

void student::getstream()
{
	std=10;
	getsubs();
	getmarks();
	std++;
	int x;//for stream selection
	if(getavg()>80)
	{
	cout<<"\tStream:\n\t\t1- Science\n\t\t2- Commerce\n\t\t3- Humanities\n\t\tEnter option:";
		do
		{
		cin>>x;
			switch(x)
			{
				case 1:strcpy(stream, "Science"); sec='A';  break;
				case 2:strcpy(stream, "Commerce");sec='B' ; break;
				case 3:strcpy(stream, "Humanities");sec='C'; break;
				default: cout<<"Entered wrong option. Enter the valid choice"; break;
			}
		}
	while(x<1||x>3);
	}
	else if (getavg()>60)
	{
		cout<<"\tStream:\n\t\t1- Commerce\n\t\t2- Humanities\n\t\tEnter option:";
		do
		{
			cin>>x;
			switch(x)
			{
				case 1:strcpy(stream, "Commerce"); sec='B';  break;
				case 2:strcpy(stream, "Humanities");sec='C' ; break;
				default: cout<<"Entered wrong option. Enter the valid choice"; break;
			}
		}
		while(x!=1&&x!=2&&x!=3);
	}
	else
	{
		cout<<"\n You have been assigned humanities on the basis of your marks. ";
		strcpy(stream, "Humanities");
	}
}

int GetPosition(int admn)
{
	ifstream fin("student.dat", ios::binary);
	student s;
	while(!fin.eof()&&fin.read((char*) &s, sizeof(s)))
	{
		if(s.check_admn(admn))
			return (fin.tellg()-1*sizeof(s));
	}
	fin.close();
	return -1;
}

void Add()
{
	clrscr();
	student S;
	ofstream fout("student.dat", ios::binary|ios::app);
	S.create();
	fout.write((char*) &S, sizeof(S));
	fout.close();
}

void Modify(int admn)
{
	fstream f("student.dat", ios::binary|ios::in|ios::out);
	student S;
	while(f.read((char*) &S, sizeof(S)) && !f.eof() )
	{
		if(S.check_admn(admn))
		{
			f.seekp(f.tellg() -1*sizeof(S), ios::beg);
			S.create();
			f.write((char*) &S, sizeof(S));
			break;
		}
	}
	f.close();
}

void Delete(int admn)
{
	ifstream fin("student.dat", ios::binary);
	ofstream fout("temp.dat", ios::binary);
	student S;
	while(fin.read((char*) &S, sizeof(S)) &&!fin.eof())
	{
		if(S.check_admn(admn))
			continue;
		else
			fout.write((char*) &S, sizeof(S));
	}
	fin.close();
	fout.close();
	remove("student.dat");
	rename("temp.dat", "student.dat");
}

void list()
{
	clrscr();
	cout<<"Admno"<<setw(7)<<"Name"<<setw(30)<<"Class"<<"\tSection"<<setw(10)<<""<<"Rollno\n\n";
	ifstream fin("student.dat", ios::binary);
	student s;
	int i=0;
	if(fin.eof())
		cout<<"No entries found";
	while(fin.read((char*) &s, sizeof(s)) && !fin.eof())
	{
		if(i==15)
			getch();
		s.student_record();
		i++;

	}
	fin.close();
}

void max_admno()
{
	ifstream fin;
	fin.open("student.dat", ios::binary);
	student S;
	while(fin.read((char*) &S, sizeof(S)) && !fin.eof());
	if(fin.tellg()!=0)
	{
		fin.seekg(fin.tellg()-1*sizeof(S));
		fin.read((char*) &S, sizeof(S));
		S.SetAsMax();
	}
}

void student::SetAsMax()
{
	admission_no=admn;
}

void student::get_total()
{
	for (int j=0;j<5 ;j++ )
	{
		for (int i=0; i<2; i++)
		{
			tot_marks[j][i]=marks[i][j][0]+marks[i][j][1];
		}
		tot_marks[j][2]=tot_marks[j][0]+tot_marks[j][1];
	}
}

void student::show_marks()
{
	clrscr();
	for(int i=0; i<2; i++)
	{
		cout<<"Semester "<<i+1<<":\n";
		for(int j=0; j<5; j++)
		{
			cout<<"\t"<<sub[j]<<":\n";
			cout<<"\t\tInternals: "<<marks[i][j][1];
			cout<<"\n\t\tTheory: "<<marks[i][j][0]<<endl;
		}
		cout<<"\nPress enter to continue...";
		getch();
		clrscr();
	}
}

void student::null_marks()
{
	for (int i=0; i<2 ;i++ )
	{
		for (int j=0;j<5 ; j++)
		{
			marks[i][j][0]=-1;
			marks[i][j][1]=-1;
		}
	}
}