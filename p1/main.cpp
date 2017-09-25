#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

struct Person
{
	string Surname;
	int Height;
	tm DateOfBirth;
	Person *Prev, *Next;
	void print_info();
	Person(){
		Prev = Next = NULL;
	}
};

class List
{
	Person *Head;
	int n;
public:
	List(){
		n = 0;
		Head = NULL;
	};
	~List(){
		Person *temp;
		while (Head && Head->Next){
			temp = Head;
			Head = Head->Next;
			delete temp;
			n--;
		}
		if (Head)
			delete Head;
	}
	void printlist();
	void revprintlist();
	void add_elem(int i);
	void del_elem(int i);
	void del_surname(string s);
	Person *get_i(int i);
	void sort_surname();
	void save_file(string fname);
	void get_file(string fname);
};

void Person::print_info()
{
	cout << Surname << " " << Height << " ";
	cout << DateOfBirth.tm_mday << "/" << DateOfBirth.tm_mon << "/" << DateOfBirth.tm_year << endl;
}

void List::printlist()
{
	Person *temp;
	temp = Head;
	if (!n){
		cout << "The List is empty" << endl;
	} else{
		while (temp){
			temp->print_info();
			temp = temp->Next;
		}
	}
}

void List::revprintlist()
{
	Person *temp;
	temp = Head;
	if (!n){
		cout << "The List is empty" << endl;
	} else{
		while(temp->Next){
			temp = temp->Next;
		}
		while(temp != Head){
			temp->print_info();
			temp = temp->Prev;
		}
		temp->print_info();
	}
}

void List::add_elem(int i)
{
	char c;
	if (i > n){
		cout << "index is too big" << endl;
		return;
	}
	Person *p = new Person;
	cout << "Please enter information:" << endl;
	cout << "Surname: ";
	cin >> p->Surname;
	cout << endl << "Height: ";
	cin >> p->Height;
	cout << endl << "Date Of Birth(dd/mm/yyyy): ";
	cin >> p->DateOfBirth.tm_mday;
	cin >> c;
	cin >> p->DateOfBirth.tm_mon;
	cin >> c;
	cin>> p->DateOfBirth.tm_year;
	cout << endl;
	Person *temp;
	temp = Head;
	if (i == n){
		while(temp != NULL && temp->Next != NULL)
			temp = temp->Next;
		if(temp != NULL){
			p->Prev = temp;
			temp->Next = p;
			p->Next = NULL;
		} else{
			p->Next = NULL;
			p->Prev = NULL;
			Head = p;
		}
		n++;
	} else if (i == 0){
		p->Next = Head;
		if (Head != NULL)
			Head->Prev = p;
		Head = p;
		p->Prev = NULL;
		n++;
	} else{
		while(temp != NULL && temp->Next != NULL && i--)
			temp = temp->Next;
		if (Head != NULL){
			p->Prev = temp;
			if(temp->Next != NULL){
				p->Next = temp->Next;
				temp->Prev->Next = p;
			} else{
				p->Next = NULL;
			}
			temp->Next = p;
			n++;
		}
	}
}

void List::del_elem(int i)
{
	Person *temp;
	temp = Head;
	if (i > n){
		cout << "index is too big" << endl;
		return;
	}
	while (i-- && temp->Next != NULL){
		temp = temp->Next;
	}
	if (temp->Prev != NULL && temp->Next != NULL){
		temp->Prev->Next = temp->Next;
		temp->Next->Prev = temp->Prev;
		n--;
	}
	if (temp->Prev == NULL && temp->Next != NULL){
		Head = temp->Next;
		temp->Next->Prev = NULL;
		n--;
	}
	if (temp->Prev != NULL && temp->Next == NULL){
		temp->Prev->Next = NULL;
		n--;
	}
	if (temp != Head){
		delete temp;
	} else{
		delete Head;
		Head = NULL;
	}
}

Person *List::get_i(int i)
{
	Person *temp;
	temp = Head;
	while (i--){
		temp = temp->Next;
	}
	return temp;
}

void List::sort_surname()
{
	string buffer;
	int buf;
	tm bf;
	Person *temp, *temp1, *temp2;
	temp = Head;
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			temp1 = get_i(i);
			temp2 = get_i(j);
			if (strcmp(temp1->Surname.c_str(), temp2->Surname.c_str()) > 0){
				buffer = temp1->Surname;
				temp1->Surname = temp2->Surname;
				temp2->Surname = buffer;
				buf = temp1->Height;
				temp1->Height = temp2->Height;
				temp2->Height = buf;
				bf = temp1->DateOfBirth;
				temp1->DateOfBirth = temp2->DateOfBirth;
				temp2->DateOfBirth = bf;
			}
		}
	}
}

void List::del_surname(string s)
{
	Person *temp;
	temp = Head;
	while (temp){
		if (!strcmp(temp->Surname.c_str(), s.c_str())){
			if (temp->Prev != NULL && temp->Next != NULL){
				temp->Prev->Next = temp->Next;
				temp->Next->Prev = temp->Prev;
				n--;
			}
			if (temp->Prev == NULL && temp->Next != NULL){
				Head = temp->Next;
				temp->Next->Prev = NULL;
				n--;
			}
			if (temp->Prev != NULL && temp->Next == NULL){
				temp->Prev->Next = NULL;
				n--;
			}
		}
		temp = temp->Next;
	}
	delete temp;
}

void List::get_file(string fname)
{
	Person *temp, *temp1;
	char c;
	temp = Head;
	ifstream fin(fname);
	string buffer;
	if (!Head){
		if (fin >> buffer){
			temp = new Person;
			temp->Next = NULL;
			temp->Prev = NULL;
			temp->Surname = buffer;
			fin >> temp->Height;
			fin >> temp->DateOfBirth.tm_mday;
			fin >> c;
			fin >> temp->DateOfBirth.tm_mon;
			fin >> c;
			fin >> temp->DateOfBirth.tm_year;
			Head = temp;
			n++;
		} else
			cout << "The file is empty" << endl;
	}
	while(fin>>buffer){
		temp1 = new Person;
		temp->Next = temp1;
		temp1->Prev = temp;
		temp = temp->Next;
		temp->Surname = buffer;
		fin >> temp->Height;
		fin >> temp->DateOfBirth.tm_mday;
		fin >> c;
		fin >> temp->DateOfBirth.tm_mon;
		fin >> c;
		fin >> temp->DateOfBirth.tm_year;
		n++;
	}
	temp->Next = NULL;
	fin.close();
}

void List::save_file(string fname)
{
	ofstream fout(fname);
	Person *temp;
	temp = Head;
	while(temp){
		fout << temp->Surname << " " << temp->Height << " ";
		fout << temp->DateOfBirth.tm_mday << "/" << temp->DateOfBirth.tm_mon << "/" << temp->DateOfBirth.tm_year << endl;
		temp = temp->Next;
	}
	fout.close();
}

int main()
{
	List *l = new List;

	char key = ' ';
	while(key != '9'){
		system("cls"); // Cleaning the screen before working
	
		cout << "Choose the act:" << endl;
		cout << "1) Show all the elements of the list" << endl;
		cout << "2) Show all the elements of the reversed list" << endl;
		cout << "3) Add an element to the list (with index)" << endl;
		cout << "4) Delete an element from the list (with index)" << endl;
		cout << "5) Delete all the elements with the exact surname from the list (surname needed)" << endl;
		cout << "6) Sort all the elements of the list by surname" << endl;
		cout << "7) Save the list to the file (file_name needed)" << endl;	
		cout << "8) Extract the list from the file (file_name needed)" << endl;
		cout << "9) Exit" << endl;

		cin >> key;
		switch(key)
		{
		case '1':
			{
				system("cls");
				l->printlist();
				system("pause");
				break;
			}
		case '2':
			{
				system("cls");
				l->revprintlist();
				system("pause");
				break;
			}
		case '3':
			{
				system("cls");
				int i;
				cout << "Type in index" << endl;
				cin >> i;
				l->add_elem(i);
				system("pause");
				break;
			}
		case '4':
			{
				system("cls");
				int i;
				cout << "Type in index" << endl;
				cin >> i;
				l->del_elem(i);
				system("pause");
				break;
			}
		case '5':
			{
				system("cls");
				string sn;
				cout << "Type in surname" << endl;
				cin >> sn;
				l->del_surname(sn);
				system("pause");
				break;
			}
		case '6':
			{
				system("cls");
				l->sort_surname();
				system("pause");
				break;
			}
		case '7':
			{
				system("cls");
				string fn;
				cout << "Type in file_name.txt" << endl;
				cin >> fn;
				l->save_file(fn);
				system("pause");
				break;
			}
		case '8':
			{
				system("cls");
				string fn;
				cout << "Type in file_name.txt" << endl;
				cin >> fn;
				l->get_file(fn);
				system("pause");
				break;
			}
		default: break;
		}
	}
	delete l;
	
	system("pause");
	return 0;
}