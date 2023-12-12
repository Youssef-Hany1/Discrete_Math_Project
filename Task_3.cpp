#include <string>
#include <iostream>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;

string Encryption(string Plaintext)
{
	string Ciphertext = ""; 
    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if(Plaintext[i]!=' ')
			if ('A'<=Plaintext[i]&&Plaintext[i]<='Z')
				//encryption formula (ax + b) mod m
				Ciphertext += (char) ((((a * (Plaintext[i]-'A')) + b) % 21) + 'A');
			else
				Ciphertext += Plaintext[i];
		else
			Ciphertext += Plaintext[i];	 
	}
	return Ciphertext;
}

string Decryption(string Ciphertext)
{
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
		if(Ciphertext[i]!=' ')
			if ('A'<=Plaintext[i]&&Plaintext[i]<='Z')
				//decryption formula a^-1*(x - b) mod m
				Plaintext += (char) (((a_inv * ((Ciphertext[i]-'A' - b)) % 21)) + 'A');
			else
				Plaintext += Ciphertext[i];
		else
			Plaintext += Ciphertext[i]; 
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