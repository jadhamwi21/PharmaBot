#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
int NumberofSectorsOfThePharmacy;
/*Predicate Function For Comparing 2 Characters In The Following Function(InSensitiveComparison)
We Pass charchecker As The 4th Argument To The Standard STD::equal Function Used In InSensitiveComparison*/
bool charchecker(char c1, char c2)
{
	if (toupper(c1) == toupper(c2))
		return true;
	else
		return false;
}
//Comparing Two Strings, Ignoring Sensitivity Between Them
bool InSensitiveComparison(string s1, string s2)
{
	return ((s1.size() == s2.size()) && (equal(s1.begin(), s1.end(), s2.begin(), charchecker)));
}
//Basic Function To Convert A Regular String To Wstring Type
wstring StringToWstring(string Sample)
{
	wstring Temp(Sample.begin(), Sample.end());
	return Temp;
}
template <class T>
//Swap Elements In An Array Function
void swap(T *a, T *b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}
template <class T>
//Bubble Sort For Sorting Customer's Bill
void BubbleSort(T arry[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (arry[j] < arry[j - 1])
			{
				swap(&arry[j], &arry[j - 1]);
			}
		}
	}
}
//Function For Creating Sector Numbers As Ordinal
string *CreateOrdinalSectors(int NumberOfSectors)
{
	string *ArrayOfSectors = new string[NumberOfSectors];
	/*
	We know that there is no 0 Sector, but we have to start the for loop with the counter
	equals to 0,because the string array that's storing the sector ordinal names will go out of scope
	and will cause memory violaton, so instead we initialized the counter at 0, and modified the
	conditional statements in the for loop, in order to matchup with the sectors numbers.
	*/
	for (int i = 0; i < NumberOfSectors; i++)
	{
		if (i == 0)
		{
			ArrayOfSectors[i] = "1st Sector";
		}
		else if (i == 1)
		{
			ArrayOfSectors[i] = "2nd Sector";
		}
		else if (i == 2)
		{
			ArrayOfSectors[i] = "3rd Sector";
		}
		else
		{
			ArrayOfSectors[i] = to_string(i + 1) + "th Sector";
		}
	}
	return ArrayOfSectors;
}
std::vector<string> SliceString(string Customers_Sentence)
{
	std::vector<string> Slice;
	//this stringstream is for extracting words from the customer's sentence;
	stringstream WantToSlice(Customers_Sentence);
	//temporary string pointer which we will delete after the extraction process
	string tmp = "";
	while (WantToSlice >> tmp)
	{
		if (tmp.find(',') != string::npos)
			tmp.substr(0, tmp.length() - 1);
		Slice.push_back(tmp);
	}
	return Slice;
}
string InputValidate()
{
	string process_String;
	cin >> process_String;
	while (process_String.find_first_not_of("0123456789.") != std::string::npos)
	{
		cout << "Please Enter a Number(Without Any Letters or Words)" << endl;
		cin >> process_String;
	}
	cin.ignore(100, '\n');
	return process_String;
}