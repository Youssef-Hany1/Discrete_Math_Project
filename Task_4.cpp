#include <string>
#include <iostream>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;

string Decryption(string Ciphertext)
{
	string Plaintext = "";
	int a_inv = 0; //a^-1
    for(int i=0; i < Ciphertext.length(); i++)
        Ciphertext[i] = toupper (Ciphertext[i]);

	//Find a^-1
	for (int i = 0; i < 26; i++)
	{
		if ((a * i) % 26 == 1)
			a_inv = i;
	}
    
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		if(Ciphertext[i]!=' ')
			//decryption formula a^-1*(x - b) mod m
			Plaintext += (char) (((a_inv * ((Ciphertext[i]+'A' - b)) % 26)) + 'A');
		else
			Plaintext += Ciphertext[i]; 
	}

	return Plaintext;
}

//Driver Program
int main()
{
	string Ciphertext = "OFHSBJFHM HXZPU";
	
	//Calling Decryption function
	cout << "Decrypted Message is: " << Decryption(Ciphertext);

	return 0;
}