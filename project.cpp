#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";

//void ShowMainMenu();

struct sClient
{
    string  AccountNumber;
    string  PinCode;
    string  Name;
    string  Phone;
    double  AccountBalance;
    bool    MarkForeDelete = false;
};

vector<string>SplitString(string S1, string Delim)
{
    vector<string> vString;
    short   pos = 0;
    string  sWord;
    while((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if(sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return (vString);
}

sClient ConvertLinetoRecord(string  Line,   string delim = "#//#")
{
    sClient Client;
    vector<string> vClient;
    vClient = SplitString(Line, delim);

    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);
    return (Client);
}

string  ConvertRecordtoLine(sClient Client, string delim = "#//#")
{
    string  stClient = "";
    stClient += Client.AccountNumber + delim;
    stClient += Client.PinCode + delim;
    stClient += Client.Name + delim;
    stClient += Client.Phone + delim;
    stClient += to_string(Client.AccountBalance);
    return (stClient);
}

bool ClientExistsByAccountNumber(string AccoutNumber, string FileName)
{
    //vector<sClient> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in); //read mod

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccoutNumber)
            {
                MyFile.close();
                return true;
            }
            //vClient.push_back(Client);
        }
        MyFile.close();
    }
    return (false);
}

sClient ReadNewClient()
{
    sClient Client;
    cout<<"Enter Account Number : ";
    getline(cin >> ws, Client.AccountNumber); //usage of std::ws will allthe whitespace character 
    while ((ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)))
    {
        cout<<"\nClient with [" << Client.AccountNumber << "] alreadu exits, Enter another Account Number";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout<<"Enter PinCode : ";
    getline(cin, Client.PinCode);
    cout<<"Enter Name : ";
    getline(cin, Client.Name);
    cout<<"Enter Phone : ";
    getline(cin, Client.Phone);
    cout<<"Enter AccountBalance : ";
    cin>>Client.AccountBalance;
    return (Client);
}

vector<sClient> LoadClientsFDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string  Line;
        sClient  Client;

        while(getline (MyFile,  Line))
        {
            Client  = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return (vClients);
}

void    PrintClientRecordLine(sClient   Client)
{
    cout<<"| "<<setw(15)<<left<<Client.AccountNumber;
    cout<<"| "<<setw(10)<<left<<Client.PinCode;
    cout<<"| "<<setw(40)<<left<<Client.Name;
    cout<<"| "<<setw(12)<<left<<Client.Phone;
    cout<<"| "<<setw(12)<<left<<Client.AccountBalance;
}

void    ShowAllClientsScreen()
{
    vector<sClient> vClients = LoadClientsFDataFromFile(ClientsFileName);
    cout<<"\n\t\t\t\tClient List ("<< vClients.size()<<") Clients.";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout<<"| "<<left<<setw(15)<<"Accout Number";
    cout<<"| "<<setw(10)<<left<<"Pin Code";
    cout<<"| "<<setw(40)<<left<<"Client Name";
    cout<<"| "<<setw(12)<<left<<"Phone";
    cout<<"| "<<setw(12)<<left<<"Balance";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if(vClients.size() == 0)
    {
        cout<<"\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for(sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout<<endl;
        }
    }
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void    PrintClientCard(sClient Client)
{
    cout<<"\nThe following are the client details:\n";
    cout<<"-----------------------------------";
    cout<<"\nAccout Number: " <<
}