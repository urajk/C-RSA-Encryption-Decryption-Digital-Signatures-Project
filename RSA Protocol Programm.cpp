#include <iostream>
#include <map>
#include <vector>
#include <sstream>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
string Encrypt(string sPlaintext, int p, int q);
string Decrypt(string sCipherText, int d, int n);
string EncodeWord(string sWord);
bool coPrimeCheck(int n1, int n2);
int findD(int e, int phi);
string calculateCipherText(string m, int n, int e);
int modExp(int nBase, int nExponent, int n);
//---------------------------------------------------------------------------
int main()
{
	int choice;
	
	cout << "Enter 1 for Encryption 2 for Decryption: ";
	cin >> choice;
	if(choice == 1)
	{
	
		int p;
		int q;
		string sWord;
		
		cout << "Enter 2 distinct prime numbers:" << endl;
		cout << "" << endl;
		cin >> p;
		cin >> q;
		
		cout << "Enter a word to encrypt (all capitals)" << endl;
		cin >> sWord;
			
		string sInput = sWord;
		string sSplitMessage = "";
		cout << "Message Entered: " + sInput << endl;
		
		int count = 0;
		for(char c : sInput)
		{
			if(count == 2)
			{
				count = 0;
				sSplitMessage += " ";
				sSplitMessage += c;    // My attempt at splitting the encoded text into chunks of 4.
			}
			else
			{
				sSplitMessage += c;
			}
			count++;
		}
		
		int nLengthFixer = sWord.length() % 2;
		
		
		string sEncodedText = EncodeWord(sSplitMessage);
		
		if (nLengthFixer == 1)
		{
			sEncodedText += "00"; // In case the last chunk only has 1 letter encoding 
								  // we add 2 zeros at the end to fix the chunks format.
		}
		
		cout << "Encoded Text: " + sEncodedText << endl;
		
		string EncryptedMessage = Encrypt(sEncodedText, p, q);
	}
	else
	{
		string Text;
		int d, n;
		
		cout << "Enter the message's cipher text: " << endl;
		cin.ignore();
		getline(cin, Text);
		cout << "Enter d and n in that order: " << endl;
		cin >> d >> n;
		
		string sMessage = Decrypt(Text, d, n);
		
		cout << "Decrypted Message: " + sMessage << endl;
	}
}
//---------------------------------------------------------------------------
string Encrypt(string sEncodedText, int p, int q)
{
	int e;
	cout << "Enter a prime number between 1 and " << p * q << endl;
	cin >> e;
	
	int n = p * q;
	int r = (p - 1) * (q - 1);
	string sPublicKey = "(" + to_string(n) + "," + to_string(e) + ")";
	cout << "Picked e: " << e << endl;
	cout << "Public Key (n,e): " << sPublicKey << endl;
	cout << "r = (p-1)(q-1): " << r << endl;
	
	int d;
	if(coPrimeCheck(r, e))
	{
		cout << "Numbers r and e ARE co-prime." << endl;
		d = findD(e, r);
		cout << "d = " << d << endl;
	}
	else 
	{
		cout << "Numbers r and e ARE NOT coprime." << endl;
	}
	
	string sCipherText = calculateCipherText(sEncodedText, n, e);
	cout << "Encrypted Message: " + sCipherText << endl;
	
	return sCipherText;
}
//---------------------------------------------------------------------------
string Decrypt(string sCipherText, int d, int n)
{
	vector<int> sCipherTextParts;
	
	stringstream ss(sCipherText);
	string part;
	string returnValue = "";
	
	while (ss >> part)
	{
        sCipherTextParts.push_back(stoi(part));
    }
    
    for(int i = 0; i < sCipherTextParts.size(); i++)
    {
    	if(i > 0)
    	{
    		returnValue += " ";
		}
		
    	int cPart = modExp(sCipherTextParts[i], d, n);
    	returnValue += to_string(cPart);
	}
	
	return returnValue;
}
//---------------------------------------------------------------------------
string EncodeWord(string sWord)
{
	
	string sResult = "";
	
    map<char, string> oLetterEquivilents = 
	{
	    {'A', "00"},
	    {'B', "01"},
	    {'C', "02"},
	    {'D', "03"},
	    {'E', "04"},
	    {'F', "05"},
	    {'G', "06"},
	    {'H', "07"},
	    {'I', "08"},
	    {'J', "09"},
	    {'K', "10"},
	    {'L', "11"},
	    {'M', "12"},
	    {'N', "13"},
	    {'O', "14"},
	    {'P', "15"},
	    {'Q', "16"},
	    {'R', "17"},
	    {'S', "18"},
	    {'T', "19"},
	    {'U', "20"},
	    {'V', "21"},
	    {'W', "22"},
	    {'X', "23"},
	    {'Y', "24"},
	    {'Z', "25"},
	};
		
    for(char c : sWord)
    {
    	if(c == ' ')
    	{
    		sResult += " ";
		}
		else
		{
			sResult += oLetterEquivilents[(char)toupper(c)];
		}
	}
	
	return sResult;
}
//---------------------------------------------------------------------------
bool coPrimeCheck(int n1, int n2)
{
	
	int nLargerNumber;
	int nSmallerNumber;
	
	if(n1 > n2)
	{
		nLargerNumber = n1;
		nSmallerNumber = n2;
	} 
	else
	{
		nLargerNumber = n2;
		nSmallerNumber = n1;
	}
	
	for(int i = 2; i <= nLargerNumber; i++)
	{
		if(nLargerNumber % i == 0 && nSmallerNumber % i == 0)
		{
			return false;
		} 	
	}
	return true;
}
//---------------------------------------------------------------------------
int findD(int e, int phi)
{
	for(int i = 2; i < phi; i++)
	{
		if(e*i % phi == 1)
		{
			return i;
		}
	}
}
//---------------------------------------------------------------------------
string calculateCipherText(string m, int n, int e)
{
	string returnValue = "";
	vector<int> sMessageParts;
	
	stringstream ss(m);
	string part;
	
	while (ss >> part) 
	{
        sMessageParts.push_back(stoi(part));
    }
    
    for(int i = 0; i < sMessageParts.size(); i++)
    {
    	if(i > 0)
    	{
    		returnValue += " ";
		}
		
    	int cPart = modExp(sMessageParts[i], e, n);
    	returnValue += to_string(cPart);
	}
	
	return returnValue;
}
//---------------------------------------------------------------------------
int modExp(int nBase, int nExponent, int n)
{
	long long c = 1;
	
	for (int i = 0; i < nExponent; i++) 
	{
    	c = (c * nBase) % n; // This is a manual way of calculating power and taking the modulo, 
							 // since there is no power function in c++ that 
							 // works with integers for some reason.
	}
    
    return c;
}
//---------------------------------------------------------------------------