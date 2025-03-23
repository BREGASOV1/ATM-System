#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

struct stClientData {
	string AcccountNumber, Name, Phone, PINCode;
	double balance = 0.0;
	bool mark = false;
};

enum enATM_Actions{ QuickWithdrawl = 1, NormalWithdrawl, Deposit, Balance, Logout};

string ClientsFile = "Clients.txt";

stClientData Client;

void ATM_MainMenue();

void LoginOperation();

void QuickWithDrawlScreen();

short EnterNumberWithCondition(short limit) {
	short number;
	cin >> number;
	while (number > limit || number < 1) {
		cout << "\nInvalid Input, Enter a Number from [1,2,3,4,5,6]\n";
		cin >> number;
	}
	return number;
}

string setw(short number, string delim) {
	string text = "";
	for (short i = 0; i < number; i++)
		text += delim;
	return text;
}

vector<string>  SplitString(string text, string delim) {
	string word = "";
	vector<string> vWords;

	short pos = 0;
	while ((pos = text.find(delim)) != std::string::npos) {
		word = text.substr(0, pos);
		if (word != " ")
			vWords.push_back(word);
		text = text.erase(0, pos + delim.length());
	}
	if (text != " ")

		vWords.push_back(text);
	return vWords;
}

stClientData ConvertClientLineIntoRecord(string line) {
	vector<string> vClients = SplitString(line, "#//#");
	stClientData Client;
	Client.AcccountNumber = vClients.at(0);
	Client.PINCode = vClients.at(1);
	Client.PINCode = vClients.at(2);
	Client.balance = stod(vClients.at(4));

	return Client;

}

stClientData ConvertClientDataLineIntoRecord(string line) {
	vector<string> vClientData = SplitString(line, "#//#");
	stClientData ClientData;
	ClientData.AcccountNumber = vClientData.at(0);
	ClientData.PINCode = vClientData.at(1);
	ClientData.Name = vClientData.at(2);
	ClientData.Phone = vClientData.at(3);
	ClientData.balance = stod(vClientData.at(4));

	return ClientData;

}

vector<stClientData> StoreFileInClientDataVector() {
	fstream File;
	vector<stClientData> vClientsData;
	string line;
	File.open(ClientsFile, ios::in);
	if (File.is_open()) {
		while (getline(File, line))
		{
			if (line != "")
				vClientsData.push_back(ConvertClientDataLineIntoRecord(line));

		}
	}
	File.close();
	return vClientsData;
}

void StoreClientDataLineInFile(string FileName, string ClientDataLine, vector<stClientData>& vClients) {
	fstream File;
	File.open(FileName, ios::out | ios::app);
	if (File.is_open())
		if (ClientDataLine != "")
			File << ClientDataLine << endl;
	File.close();
	vClients = StoreFileInClientDataVector();

}

void RfreshClientData() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	for (stClientData& client : vClients) {
		if (client.AcccountNumber == Client.AcccountNumber) {
			Client = client;
			break;
		}
	}
}

string ConvertDataRecordIntoLine(stClientData ClientData) {
	string ClientDataLine = "";
	ClientDataLine += ClientData.AcccountNumber + "#//#";
	ClientDataLine += ClientData.PINCode + "#//#";
	ClientDataLine += ClientData.Name + "#//#";
	ClientDataLine += ClientData.Phone + "#//#";
	ClientDataLine += to_string(ClientData.balance);
	return ClientDataLine;
}

void StoreVectorOfClientsInFile(vector<stClientData> vClients, string FileName) {
	fstream File;
	File.open(FileName, ios::out);
	if (File.is_open()) {
		for (stClientData& Client : vClients)
		{
			if (!Client.mark)
				File << ConvertDataRecordIntoLine(Client) << endl;
		}
	}
	File.close();

}

bool CheckClientByNameAndPassword(stClientData Client) {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	for (stClientData& client : vClients) {
		if (client.AcccountNumber == Client.AcccountNumber && client.PINCode == Client.PINCode) {
			
			return true;
		}
	}
	return false;
}

void LoginInterface() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Login Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	LoginOperation();
}

void LoginOperation() {
	cout << "\nEnter your Account Number:......\n";
	getline(cin >> ws, Client.AcccountNumber);
	cout << "\nEneter your Password:...\n";
	getline(cin >> ws, Client.PINCode);
	while (!CheckClientByNameAndPassword(Client)) {
		cout << "\nLogin Failed, wrong password or username...!!\n";
		cout << "\npress any key to login again";
		system("pause>0");
		LoginInterface();
	}
	RfreshClientData();
	ATM_MainMenue();
}

void BackToATM_Menue() {
	cout << "\npress any key to go back to Main Menue";
	system("pause>0");
	ATM_MainMenue();
}

void MainMenueShape() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "ATM Main Menue Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << setw(3, "	") << "[1] Quick Withdrawl" << "\n";
	cout << setw(3, "	") << "[2] Normal Withdrawl" << "\n";
	cout << setw(3, "	") << "[3] Deposit" << "\n";
	cout << setw(3, "	") << "[4] Check Balance" << "\n";
	cout << setw(3, "	") << "[5] LogOut" << "\n";
	cout << setw(40, "==") << "\n";

}

void QuickWithDrawlAction(short WithDrawlVaue) {
	vector<stClientData> vClients =StoreFileInClientDataVector();
	char answer;
	if (Client.balance<WithDrawlVaue)
	{
		cout << "\nYou can not with drawl " << WithDrawlVaue << endl;
		cout << "\nYour balance is: " << Client.balance;
		cout << "\nPress any key to go back to Quick Withdrawl Screen...";
		system("pause>0");
		QuickWithDrawlScreen();
	}
	cout << "\nAre you sure you want to withdral " << WithDrawlVaue << " From your account? Y/N\n";
	cin >> answer;
	if (tolower(answer) == 'y') {
		for (stClientData& client : vClients) {
			if (client.AcccountNumber == Client.AcccountNumber) {
				client.balance -= WithDrawlVaue;

				break;
			}
		}
		StoreVectorOfClientsInFile(vClients,ClientsFile);
		RfreshClientData();
		cout << "\nWithdrawl has been done successfuly, your new balance is " << Client.balance << "\n";
		BackToATM_Menue();
	}
	else
		BackToATM_Menue();




}

void QuickWithDrawlScreen(){
	short WithDrawlChoice;
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Quick Withdrawl Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << left;
	cout << setw(15) << " [1] 20  " <<  "[2] 50  " << endl;
	cout << setw(15) << " [3] 100 " <<  "[4] 200 " << endl;
	cout << setw(15) << " [5] 500 " <<  "[6] 700 " << endl;
	cout << setw(15) << " [7] 1000" <<  "[8] 2000" << endl<<" [9] Exit\n";
	cout << "\nYour Balance is " << Client.balance;
	cout << "\nChoose What value you want to withdarwl [ 1 to 9 ] " << endl;
	WithDrawlChoice = EnterNumberWithCondition(9);
	switch (WithDrawlChoice)
	{
	case 1:
		QuickWithDrawlAction(20);
		break;
	case 2:
		QuickWithDrawlAction(50);
		break;
	case 3:
		QuickWithDrawlAction(100);
		break;
	case 4:
		QuickWithDrawlAction(200);
		break;
	case 5:
		QuickWithDrawlAction(500);
		break;
	case 6:
		QuickWithDrawlAction(700);
		break;
	case 7:
		QuickWithDrawlAction(1000);
		break;
	case 8:
		QuickWithDrawlAction(2000);
		break;
	case 9:
		ATM_MainMenue();
		break;
	}
	
}

void EnsureValueisNumberMuliples(short number, int &value) {
	while (value% number != 0)
	{
		printf( "\nEnter the value you want to withdrawl, it should be a %d value...\n",number);
		cin >> value;
	}
	
}

void NormalWithdrawlAction() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	int WithDrawlValue;
	char answer;
	cout << "\nEnter the value you want to withdrawl, it should be a *5 value...\n";
	cin >> WithDrawlValue;
	EnsureValueisNumberMuliples(5, WithDrawlValue);
	while (Client.balance < WithDrawlValue) {
		cout << "\nThis ammount excceds your balance, your balance is  " << Client.balance << endl;
		cin >> WithDrawlValue;
	    EnsureValueisNumberMuliples(5, WithDrawlValue);
	}
	cout << "\nAre you sure you want to withdrawl " << WithDrawlValue << " From your account? Y/N\n";
	cin >> answer;
	if (tolower(answer) == 'y') {
		for (stClientData& client : vClients) {
			if (client.AcccountNumber == Client.AcccountNumber) {
				client.balance -= WithDrawlValue;

				break;
			}
		}
		StoreVectorOfClientsInFile(vClients, ClientsFile);
		RfreshClientData();
		cout << "\nWithdrawl has been done successfuly, your new balance is "<<Client.balance<<"\n";
		BackToATM_Menue();
	}
	else
		BackToATM_Menue();

		
	
}

void NormalWithdrawlScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Normal Withdrawl Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << "\nYour Balance is: " << Client.balance;
	NormalWithdrawlAction();
}
 
void DepositAction() {
	vector<stClientData> vClients = StoreFileInClientDataVector();
	double DepositValue;
	char answer;
	cout << "\nEnter the value you want to deposit...\n";
	cin >> DepositValue;
	
	while (DepositValue<=0) {
		cout << "\nYou shoule enter a real value......" << endl;
		cin >>DepositValue;
		
	}
	cout << "\nAre you sure you want to deposit " << DepositValue << " to your account? Y/N\n";
	cin >> answer;
	if (tolower(answer) == 'y') {
		for (stClientData& client : vClients) {
			if (client.AcccountNumber == Client.AcccountNumber) {
				client.balance += DepositValue;

				break;
			}
		}
		StoreVectorOfClientsInFile(vClients, ClientsFile);
		RfreshClientData();
		cout << "\nDeposit has been done successfuly, your new balance is " << Client.balance << "\n";
		BackToATM_Menue();
	}
	else
		BackToATM_Menue();



}

void DepositScreen() {
	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Deposit Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << "\nYour Balance is: " << Client.balance;
	DepositAction();
}

void CheckBalanceScreen() {

	system("cls");
	cout << setw(40, "==") << "\n\n";
	cout << setw(13, "  ") << "Balance Screen" << "\n\n";
	cout << setw(40, "==") << "\n";
	cout << "\nYour Current Balance is: " << Client.balance;
	BackToATM_Menue();

}

void ATM_MainMenue() {
	MainMenueShape();
	enATM_Actions MenueAction;
	cout << "Choose What do you want to do from [ 1 to 5 ] " << endl;
	MenueAction = (enATM_Actions)EnterNumberWithCondition(5);
	switch (MenueAction)
	{
	case QuickWithdrawl:
		QuickWithDrawlScreen();
		break;
	case NormalWithdrawl:
		NormalWithdrawlScreen();
		break;
	case Deposit:
		DepositScreen();
		break;
	case Balance:
		CheckBalanceScreen();
		break;
	case Logout:
		LoginInterface();
		break;
	
	}

}

int main()
{
	LoginInterface();
}
