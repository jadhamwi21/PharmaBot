/*Sapi.h | BasicVoice.h | MaleType.h | FemaleType.h | Functions.h
first 4 are created for text to speech synthesizer,the last one Functions.h is Functions Used In
Our Project(Like Sorting-Comparing Strings-etc)*/
#define FKG_FORCED_USAGE 1
#include <sphelper.h>
#undef FKG_FORCED_USAGE
#include "BasicVoice.h"
#include "FemaleType.h"
#include "Functions.h"
#include "MaleType.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sapi.h>
#include <set>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#define Conv StringToWstring
using namespace std;
//Item Specifications
struct Item
{
	string Type;
	string Name;
	double Price;
	long Quantity;
	string SectorBelongsTo;
	Item(string Type, string Name, double Price, long Quantity)
	{
		srand(time(0));
		this->Type = Type;
		this->Name = Name;
		this->Price = Price;
		this->Quantity = Quantity;
		string *ArrayStoringSectors = CreateOrdinalSectors(NumberofSectorsOfThePharmacy);
		if (NumberofSectorsOfThePharmacy == 1)
		{
			this->SectorBelongsTo = ArrayStoringSectors[0];
		}
		else if (InSensitiveComparison(Type, "eyeglass"))
		{
			this->SectorBelongsTo = ArrayStoringSectors[NumberofSectorsOfThePharmacy - 1];
		}
		else if (InSensitiveComparison(Type, "remedy"))
		{
			this->SectorBelongsTo = ArrayStoringSectors[rand() % (NumberofSectorsOfThePharmacy - 1)];
		}
		else
		{
			this->SectorBelongsTo = -1;
		}
		delete[] ArrayStoringSectors;
	}
};
//Pharmacy Class For Creating A Pharmacy Object And Storing Information About The New Created Pharmacy
class Pharmacy
{
public:
	string Pharmacy_Name;
	string Pharmacist_Name;
	string *Sectors;

	std::vector<Item> Remedies;
	std::vector<Item> EyeGlasses;
	Pharmacy(string Pharmacy_Name, string Pharmacist_Name, int sectors)
	{
		NumberofSectorsOfThePharmacy = sectors;
		this->Pharmacist_Name = Pharmacist_Name;
		this->Pharmacy_Name = Pharmacy_Name;
		//The array (Sectors) will store sectors as ordinal numbers, returned by the function Create
		//Ordinal Sectors.
		this->Sectors = CreateOrdinalSectors(sectors);
	}
	//A Function That Add Item To The Pharmacy(It Either Exists Or Not) If It Exists It Just Increment The Quantity
	//If The Type Isn't Supported In The Pharmacy Then A Sorry Message Pops Up
	void AddItemToPharmacy(Item ItemInsertion)
	{
		string Name = ItemInsertion.Name;
		if (InSensitiveComparison(ItemInsertion.Type, "remedy"))
		{
			//this iterator will point to the item(Remedy) if it was found in the vector Remedies
			//if it wasn't found it will return an iterator to the address after the last element in vector
			auto remedy_itr = std::find_if(Remedies.begin(), Remedies.end(), [Name](Item &Remedy) {
				return InSensitiveComparison(Name, Remedy.Name);
			});
			//if not found ->
			if (remedy_itr != Remedies.end())
			{
				remedy_itr->Price = ItemInsertion.Price;
				remedy_itr->Quantity += ItemInsertion.Quantity;
				cout << "This Item Already Exists In The Pharmacy, It's Updated As Follows :" << endl;
				cout << "Price : " << remedy_itr->Price << endl;
				cout << "Quantity : " << remedy_itr->Quantity << endl;
				return;
			}
			//if found ->
			else
			{
				Remedies.push_back(ItemInsertion);
				cout << "The Item Has Been Successfully Added As Follows :" << endl;
				cout << "Name : " << ItemInsertion.Name << endl;
				cout << "Price : " << ItemInsertion.Price << endl;
				cout << "Quantity : " << ItemInsertion.Quantity << endl;
				cout << "Type : Remedy" << endl;
				cout << "------------------------------------------------------" << endl;
				return;
			}
		}
		if (InSensitiveComparison(ItemInsertion.Type, "eyeglass"))
		{
			//this iterator will point to the item(Remedy) if it was found in the vector Remedies
			//if it wasn't found it will return an iterator to the address after the last element in vector
			auto eyeglass_itr = std::find_if(EyeGlasses.begin(), EyeGlasses.end(), [Name](Item &Eyeglass) {
				return InSensitiveComparison(Name, Eyeglass.Name);
			});
			//if not found ->
			if (eyeglass_itr != EyeGlasses.end())
			{
				eyeglass_itr->Price = ItemInsertion.Price;
				eyeglass_itr->Quantity += ItemInsertion.Quantity;
				cout << "This Item Already Exists In The Pharmacy, It's Updated As Follows :" << endl;
				cout << "Price : " << eyeglass_itr->Price << endl;
				cout << "Quantity : " << eyeglass_itr->Quantity << endl;
				return;
			}
			//if found ->
			else
			{
				EyeGlasses.push_back(ItemInsertion);
				cout << "The Item Has Been Successfully Added As Follows :" << endl;
				cout << "Name : " << ItemInsertion.Name << endl;
				cout << "Price : " << ItemInsertion.Price << endl;
				cout << "Quantity : " << ItemInsertion.Quantity << endl;
				cout << "Type : Eyeglass" << endl;
				cout << "------------------------------------------------------" << endl;
				return;
			}
		}
	}
	void ShowItems()
	{
		cout << "----------------------------" << endl;
		cout << "Remedies [ Name -- Price ]" << endl;
		if (Remedies.size() != 0)
			for (auto remedy : Remedies)
			{
				cout << "[ " << remedy.Name << " -- " << remedy.Price << "$ ]" << endl;
			}
		if (EyeGlasses.size() != 0)
		{
			cout << "----------------------------" << endl;
			cout << "Eyeglasses [Name -- Price]" << endl;
			for (auto eyeglass : EyeGlasses)
			{
				cout << "[ " << eyeglass.Name << " -- " << eyeglass.Price << "$ ]" << endl;
			}
		}
		cout << "----------------------------" << endl;
	}
};
class Bot
{
private:
	//ID Of The Bot
	static int ID;
	//Name Of The Bot
	string Name;
	//Sentences To Say For The Customer
	std::vector<string> Sentences[3];
	//this vector will store the items that the customer asked about for later use
	std::vector<Item> StuffsCustomerAskedAbout;
	//this pointer variable Bot_Voice Is Responsible for declaring the bot's voice
	BasicVoice *Bot_Voice;

public:
	void _Background_Voice_(string Sentence)
	{
		Bot_Voice->SpeakPhrase(Conv(Sentence));
	}
	//Constructor Consisting Bot ID,and Name,Plus The Sentences The Bot Can Say
	Bot(string Name, string Gendre)
	{
		this->ID = ID++;
		this->Name = Name;
		this->Bot_Voice = BasicVoice::CreateGendre(Gendre);
		Sentences[0] = {
			"Hello Sir How Can I Help You?",
			"Hello Sir,I'm " + Name + ",How Can I Help You?",
		};
		Sentences[1] = {
			"It's Available",
			"I Found It",
			"Sorry Sir,It's Not Available,Any More Questions?",
			"My Name Is " + Name + " Sir",
			"You Can Find",
			"Sir , You Have To Enter How Many Piece You Want From Each Item",
			"I Didn't Quite Understand Sir,Can You Clarify?",
		};
		Sentences[2] = {
			"You're Very Welcomed Sir!Good Bye"};
	}
	//This Function Does The Most Part,The Ability Of The BOT To Analyze The Phrase And Reply Back
	void AnswerCustomer(string Customers_Sentence, Pharmacy PharmacyInclude)
	{
		//this vector is for storing words the customer has entered
		std::vector<string> Slice = SliceString(Customers_Sentence);
		//Switch For The Bot So He Knows What To Say To The Customer
		int Logicswitch = 0;
		for (unsigned int i = 0; i < Slice.size(); i++)
		{
			if (InSensitiveComparison(Slice[i], "Looking") || InSensitiveComparison(Slice[i], "Searching"))
			{
				Logicswitch = 1;
				break;
			}
			if (InSensitiveComparison(Slice[i], "Name") || InSensitiveComparison(Slice[i], "what"))
			{
				Logicswitch = 2;
				break;
			}
			if (InSensitiveComparison(Slice[i], "Where") || InSensitiveComparison(Slice[i], "Location") || InSensitiveComparison(Slice[i], "Spot"))
			{
				Logicswitch = 3;
				break;
			}
			if (InSensitiveComparison(Slice[i], "Total") || InSensitiveComparison(Slice[i], "Cost"))
			{
				Logicswitch = 4;
				break;
			}
		}
		//Here We're Letting The Bot Pick The Right Phrase According To The Customer's Sentence
		//If The Bot Didn't Understand
		if (Logicswitch == 0)
		{
			string Miss_Understanding_Message = Sentences[1][6];
			cout << Miss_Understanding_Message << endl;
			Bot_Voice->SpeakPhrase(Conv(Miss_Understanding_Message));
		}
		//Giving Information For The Customer About Items He Asked For
		if (Logicswitch == 1)
		{
			int ItemIndex;
			//Loop is used here for picking up the right word that represents the product the customer is looking for
			for (int i = 0; i < Slice.size(); i++)
			{
				if (InSensitiveComparison(Slice[i], "for"))
				{
					ItemIndex = i + 1;
					break;
				}
			}
			//Crop The Comma From The Vector Product Element, because the comma affects the understanding of the bot
			if (Slice[ItemIndex].find(','))
			{
				int EndOfItem = Slice[ItemIndex].find(',');
				Slice[ItemIndex] = Slice[ItemIndex].substr(0, EndOfItem);
			}
			// Pointer To The Item If Found;
			Item *Found_Item_Pointer = NULL;
			//string of the item the customer's looking for
			string Requested_Item = Slice[ItemIndex];
			// Remedies And Eyeglasses Vector Sizes;
			int Rem_Vec_Size = PharmacyInclude.Remedies.size();
			int Eyegls_Vec_Size = PharmacyInclude.EyeGlasses.size();
			// Iterators To The Beginning of Remedies And Eyeglasses Vector
			std::vector<Item>::iterator Rem_Iterator = PharmacyInclude.Remedies.begin();
			std::vector<Item>::iterator Eyegls_Iterator = PharmacyInclude.EyeGlasses.begin();
			//Lambda Function Which Will Compare Requested_Item And The Current_Item
			auto Search_Predicate = [Requested_Item, &Found_Item_Pointer](Item current_item) {
				return (InSensitiveComparison(Requested_Item, current_item.Name));
			};
			//just a flag variable to keep in check that the item was found or not
			bool Is_Present = false;
			auto Search_Remedy = std::find_if(Rem_Iterator, Rem_Iterator + Rem_Vec_Size, Search_Predicate);
			auto Search_Eyeglass = std::find_if(Eyegls_Iterator, Eyegls_Iterator + Eyegls_Vec_Size, Search_Predicate);
			auto Search_Stuffs = std::find_if(StuffsCustomerAskedAbout.begin(), StuffsCustomerAskedAbout.end(), Search_Predicate);
			//This If To Check If The Item Is Found In The Remedy Vector
			if (Search_Remedy != Rem_Iterator + Rem_Vec_Size)
			{
				Found_Item_Pointer = new Item(*Search_Remedy);
				Is_Present = true;
				//If Statement To Check Wether the customer asked about this item recently or nah(so we won't add it to the bot's memory)
				if (Search_Stuffs == StuffsCustomerAskedAbout.end())
				{
					StuffsCustomerAskedAbout.push_back(*Found_Item_Pointer);
				}
			}
			//Else If The Item Wasn't Found In Remedies Vector
			//Search In The Eyeglasses Vector
			else if (Search_Eyeglass != Eyegls_Iterator + Eyegls_Vec_Size)
			{
				//dynamically creating a new item which is a copy of the item that was found
				Found_Item_Pointer = new Item(*Search_Eyeglass);
				Is_Present = true;
				//If Statement To Check Wether the customer asked about this item recently or nah(so we won't add it to the bot's memory)
				if (Search_Stuffs == StuffsCustomerAskedAbout.end())
				{
					StuffsCustomerAskedAbout.push_back(*Found_Item_Pointer);
				}
			}
			//If Not,Don't Push It Back,But Display The Quantity And Price
			else
			{
				string Suitable_Message = "Sorry , I Couldn't Find " + Slice[ItemIndex] + ". Any More Questions?";
				_Background_Voice_(Suitable_Message);
				cout << Suitable_Message << endl;
			}
			//If The Item Was Found Print A Suitable Message
			if (Is_Present)
			{
				stringstream Temporary;
				srand(time(0));
				Temporary << Sentences[1][rand() % 2] << "\nPrice Is " << std::setprecision(10) << Found_Item_Pointer->Price << "$\nQuantity Is " << Found_Item_Pointer->Quantity << ".\nWhat Else?";
				string Replyback = Temporary.str();
				_Background_Voice_(Replyback);
				cout << Replyback << endl;
			}
			delete Found_Item_Pointer;
		}
		//Answering Question For Bot's Name
		if (Logicswitch == 2)
		{
			_Background_Voice_(Sentences[1][3]);
			cout << Sentences[1][3] << endl;
		}
		//Guiding The Customer Through Sectors
		if (Logicswitch == 3)
		{
			//If The Customer Didn't Ask The Bot About Any Item ->
			if (StuffsCustomerAskedAbout.empty())
			{
				string Miss_Understanding_Message = "Sir, You Didn't Tell Me What are The Items You Looking For !";
				_Background_Voice_(Miss_Understanding_Message);
				cout << Miss_Understanding_Message << endl;
			}
			//If He Asked About 1 Item
			else if (StuffsCustomerAskedAbout.size() == 1)
			{
				string One_Item_Message = Sentences[1][4] + " It In The " + StuffsCustomerAskedAbout.begin()->SectorBelongsTo;
				_Background_Voice_(One_Item_Message);
				cout << One_Item_Message << endl;
			}
			//If He Asked About 2 Or More Items
			else
			{
				//Collection Of Phrases,The Bot Randomly Chooses The Phrase
				string Compilation[] = {
					"You Can Find It In The ",
					"This One You Go To The ",
					"You Got To Go Through The "};
				string Opening_Message = Sentences[1][4] + " Them In These Sectors:\n";
				cout << Opening_Message << endl;
				_Background_Voice_(Opening_Message);
				cout << "__________________________________________" << endl;
				srand(time(0));
				std::for_each(StuffsCustomerAskedAbout.begin(), StuffsCustomerAskedAbout.end(), [&](auto current_item) {
					string Curr_Item_Message = current_item.Name + " " + Compilation[rand() % 3] + current_item.SectorBelongsTo + ".";
					//_Background_Voice_(Curr_Item_Message);
					cout << Curr_Item_Message << endl;
				});
			}
		}
		//Calculate The Bill For Stuffs Customer Asked About
		if (Logicswitch == 4)
		{
			//In Case Customer Didn't Ask About Anything
			if (StuffsCustomerAskedAbout.empty())
			{
				string Bill_Message = "Sorry Sir But You Didn't Ask For Any Items Yet";
				_Background_Voice_(Bill_Message);
				cout << Bill_Message << endl;
			}
			//Processing Data And Designing A Template For The Bill
			else
			{
				/*Is To Ask The Customer About How Much Quantity He Wants From Each Item
				And Then Do Some Arithmetic Operations And Then Add Them To An Array Called LinesOfItems
				(Array Of Strings) After The Customer Finished Entering The Quantities Then The Bot Will Displays
				The Bill For Him*/
				_Background_Voice_(Sentences[1][5]);
				cout << Sentences[1][5] << endl;
				cout << "Name";
				cout << setw(15) << "Quantity" << endl;
				string *LinesOfItems = new string[StuffsCustomerAskedAbout.size()];
				//This Refers To Which Line We've Reached In The Bill
				int LineNumber = 0;
				long Bill_Total = 0;
				/*Just A Temporary Variable To Let The CUSTOMER Enters How Much He Wants For A Certain Item
				He Asked About*/
				long Customers_Quantity;
				for (auto Itr = StuffsCustomerAskedAbout.begin(); Itr != StuffsCustomerAskedAbout.end(); Itr++)
				{
					cout << Itr->Name << string(7 - (Itr->Name.size() - 4), ' ');
					Customers_Quantity = stol(InputValidate());
					//Print Item Name : Quantity/So The Customer Knows What Item's Quantity Is He Entering
					while (Customers_Quantity > Itr->Quantity)
					{
						string Error = "Sorry Sir, Only " + to_string(Itr->Quantity) + " Is Available, So Enter How Many ? !\n";
						_Background_Voice_(Error);
						cout << Error;
						cout << Itr->Name << string(7 - (Itr->Name.size() - 4), ' ');
						Customers_Quantity = stol(InputValidate());
					}
					//BillTotal To Sum All The Items The Customer Wants
					Bill_Total += Customers_Quantity * (Itr->Price);
					//StringStream Line Is Declared Here So We Can Format Bill's Line Infos By Using String Manipulation(SetW)
					stringstream Line;
					Line << setw(10) << Itr->Name << setw(13) << to_string(Customers_Quantity) << setw(10) << Customers_Quantity * Itr->Price << setw(15) << Itr->Price << endl;
					//Adding The Line To The Array That's Storing These Lines
					LinesOfItems[LineNumber++] = Line.str();
				}
				cout << "_____________________________________________________________" << endl;
				BubbleSort(LinesOfItems, StuffsCustomerAskedAbout.size());
				cout << setw(10) << "Name" << setw(13) << "Quantity" << setw(10) << "Price" << setw(15) << "Individual" << endl;
				for (int i = 0; i < StuffsCustomerAskedAbout.size(); i++)
				{
					cout << LinesOfItems[i];
				}
				cout << "____________________________________________________________" << endl;
				string Total = "Bill Total  =  " + to_string(Bill_Total) + "$";
				_Background_Voice_(Total);
				cout << Total << endl;
				delete[] LinesOfItems;
			}
		}
	}
	void ChatBotActivate(Pharmacy P)
	{
		srand(time(0));
		//This Is The Opening message
		string Greeting_Message = Sentences[0][rand() % 2];
		//the object bot_voice which will basically call the function speakphrase who's responsible on spelling the phrase
		_Background_Voice_(Greeting_Message);
		cout << Greeting_Message << endl;
		//while the customer didn't finish with all his questions
		while (true)
		{
			string CustomerQuestion;
			//the GetLine is not showing inputed words until the bot has finished speaking
			getline(cin, CustomerQuestion);
			std::vector<string> Tmp = SliceString(CustomerQuestion);
			auto Thank_Search = std::find_if(Tmp.begin(), Tmp.end(), [](string S) { return InSensitiveComparison(S, "Thank"); });
			auto Thanks_Search = std::find_if(Tmp.begin(), Tmp.end(), [](string S) { return InSensitiveComparison(S, "Thanks"); });
			if (Thank_Search != Tmp.end() || Thanks_Search != Tmp.end())
			{
				_Background_Voice_(Sentences[2][0]);
				cout << Sentences[2][0] << endl;
				break;
			}
			AnswerCustomer(CustomerQuestion, P);
		}
	}
};
int Bot::ID = 1;
void ProgramInterface()
{
	Pharmacy *PharmacyHolder = NULL;
	Bot *Current_Bot = NULL;
	int gen = -1;
	while (true)
	{
		cout << "1 - Setup" << endl;
		cout << "2 - Activate" << endl;
		cout << "3 - Terminate" << endl;
		gen = stoi(InputValidate());
		if (gen == 3)
		{
			exit(0);
		}
		system("cls");
		switch (gen)
		{
		case 1:
		{
			int Innerswitch = -1;
			while (true)
			{
				cout << "1 - Initialize Pharmacy" << endl;
				cout << "2 - Add Items" << endl;
				cout << "3 - Add Bot" << endl;
				cout << "4 - Exit" << endl;
				Innerswitch = stoi(InputValidate());
				if (Innerswitch == 4)
				{
					system("cls");
					break;
				}
				system("cls");
				switch (Innerswitch)
				{
				case 1:
				{
					string PharmacyName, PharmacistName;
					int Sectors;
					cout << "Pharmacy Name : ";
					getline(cin, PharmacyName);
					cout << "Pharmacist Name : ";
					getline(cin, PharmacistName);
					cout << "Number Of Sectors : ";
					Sectors = stoi(InputValidate());
					PharmacyHolder = new Pharmacy(PharmacyName, PharmacistName, Sectors);
					if (PharmacyHolder != NULL)
					{
						cout << "Pharmacy Initialized Successfully  " << endl;
					}
					else
					{
						cout << "Sorry We Couldn't Create This Pharmacy Please Try Again With Valid Information" << endl;
					}
					break;
				}
				case 2:
				{
					system("cls");
					if (PharmacyHolder == NULL)
					{
						cout << "You Have To Create A Pharmacy First,In Order To Add Items To It" << endl;
						break;
					}
					string ItemType, ItemName;
					double ItemPrice;
					int ItemQuantity;
					cout << "How Many Items You Wanna Add?" << endl;
					int NumberOfItems;
					NumberOfItems = stoi(InputValidate());
					cout << "------------------------------------------------------" << endl;
					for (int i = 0; i < NumberOfItems; i++)
					{
						cout << "Item Type : ";
						cin >> ItemType;

						if (!InSensitiveComparison(ItemType, "remedy") && !InSensitiveComparison(ItemType, "eyeglass"))
						{
							cout << "Sorry This Type Of Products Isn't Available" << endl;
							i--;
							continue;
						}
						cout << "Item Name : ";
						cin >> ItemName;

						cout << "Item Price : ";
						ItemPrice = stod(InputValidate());

						cout << "Item Quantity : ";
						ItemQuantity = stoi(InputValidate());

						Item ItemAdd(ItemType, ItemName, ItemPrice, ItemQuantity);
						PharmacyHolder->AddItemToPharmacy(ItemAdd);
					}
					break;
				}
				case 3:
				{
					Bot *TempBot;
					string Gendre;
					string BotName;
					if (PharmacyHolder == NULL)
					{
						cout << "Create A Pharmacy First Please " << endl;
						break;
					}
					cout << "Bot Name : ";
					cin >> BotName;

					cout << "Bot Gender :  -Male  |  -Female" << endl;
					cin >> Gendre;
					while (!InSensitiveComparison(Gendre, "Female") && !InSensitiveComparison(Gendre, "Male"))
					{
						cin >> Gendre;
					}
					cin.ignore(100, '\n');
					if (InSensitiveComparison(Gendre, "Female"))
						Gendre = "Female";
					else
						Gendre = "Male";
					TempBot = new Bot(BotName, Gendre);
					if (TempBot != NULL)
					{
						Current_Bot = new Bot(*TempBot);
						cout << "Bot Added Successfully " << endl;
					}
					else
					{
						cout << "Sorry Couldn't Add The Bot,Make Sure You Entered Accurate Information " << endl;
					}
					delete TempBot;
					TempBot = NULL;
					break;
				}
				}
				cin.get();
				system("cls");
			}
			break;
		}
		case 2:
		{
			int Botswitch = -1;
			while (true)
			{
				cout << "1 - Activate Bot" << endl;
				cout << "2 - Show Items" << endl;
				cout << "3 - Exit" << endl;
				Botswitch = stoi(InputValidate());

				if (Botswitch == 3)
				{
					system("cls");
					break;
				}
				system("cls");
				switch (Botswitch)
				{
				case 1:
				{
					cout << "Chatbot Activated !!" << endl;
					cin.get();
					system("cls");
					Current_Bot->ChatBotActivate(*PharmacyHolder);
					cin.get();
					break;
				}

				case 2:
				{
					PharmacyHolder->ShowItems();
					cin.get();
				}
				}
				system("cls");
			}
			system("cls");
		}
		}
	}
}
int main()
{
	ProgramInterface();
	return 0;
}