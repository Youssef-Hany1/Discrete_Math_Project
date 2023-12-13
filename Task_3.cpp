#include <string>
#include <iostream>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;

string Encryption(string Plaintext)
{
	char alphabet[21]={'A','B','C','D','E','F','G','H','I','L','M','N','O','P','R','S','T','U','V','Z'};

	string Ciphertext = ""; 
    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	
	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		bool found = false;
		for (int j = 0; i < 21; i++)
		{
			if(Plaintext[i]==alphabet[j]){
				//encryption formula (ax + b) mod m
				Ciphertext += alphabet[(((a * (j-21)) + b) % 21)+21];
				cout << Ciphertext << endl;
				found = true;
			}
		}
		if (!found)
			Ciphertext += Plaintext[i];
	}
	return Ciphertext;
}

string Decryption(string Ciphertext)
{
	char alphabet[21]={'A','B','C','D','E','F','G','H','I','L','M','N','O','P','R','S','T','U','V','Z'};

	string Plaintext = "";
	int a_inv = 0; //a^-1
    for(int i=0; i < Ciphertext.length(); i++)
        Ciphertext[i] = toupper (Ciphertext[i]);

	//Find a^-1
	for (int i = 0; i < 21; i++)
	{
		if ((a * i) % 21 == 1)
			a_inv = i;
	}
    
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		bool found = false;
		for (int j = 0; i < 21; i++)
		{
			if(Plaintext[i]==alphabet[j]){
				//decryption formula a^-1*(x - b) mod m
				Plaintext += alphabet[((a_inv * (((j+21) - b)) % 21))+21];
				found = true;
			}
		}
		if (!found)
			Ciphertext += Plaintext[i];
	}
	return Plaintext;
}

//Driver Program
int main()
{
	string Plaintext = "AMO LA CRITTOGRAFIA";

	cout << Plaintext << endl;
	
	//Calling Encryption function
	cout << "Encrypted Message is: " << Encryption(Plaintext) <<endl;

	cout << "Decrypted Message is: " << Decryption(Encryption(Plaintext)) <<endl;
	return 0;
}