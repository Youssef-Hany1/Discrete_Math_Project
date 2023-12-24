#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;
const string italianAlphabet = " ABCDEFGHILMNOPQRSTUVZ";
const string italianAlphabet2 = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHILMNOPQRSTUVZabcdefghilmnopqrstuvz";

int getIndex(char ch) {
    int index = italianAlphabet.find(ch);
    return (index >=0)? index : -1;
}

char getChar(int index) {
    return italianAlphabet[index];
}

int getIndex2(char ch) {
    int index = italianAlphabet2.find(ch);
    return (index >=0)? index : -1;
}

char getChar2(int index) {
    return italianAlphabet2[index];
}

string Encryption(string Plaintext)
{
	string Ciphertext = ""; 
	
    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);
	
	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		int x = getIndex(Plaintext[i]);
		if(x!=-1){
			//encryption formula (ax + b) mod m
			int encrypted_char = (a * x + b) % italianAlphabet.size();
			Ciphertext += getChar(encrypted_char);
		}
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
	for (int i = 0; i < 22; i++)
	{
		if ((a * i) % 22 == 1)
			a_inv = i;
	}
    
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		int x = getIndex(Ciphertext[i]);
		if(x!=-1){
			//decryption formula a^-1*(x - b) mod m
			int decrypted_char = (a_inv * (x - b + italianAlphabet.size())) % italianAlphabet.size();
			Plaintext += getChar(decrypted_char);
		}
		else
		Plaintext += Ciphertext[i];
	}
	return Plaintext;
}

string Advanced_Encryption(string Plaintext)
{
	string Ciphertext = "";

	for (int i = 0; i < Plaintext.length(); i++)
	{
		int x = getIndex2(Plaintext[i]);
		if(x!=-1){
			//encryption formula (ax + b) mod m
			int encrypted_char = (a * x + b) % italianAlphabet2.size();
			Ciphertext += getChar2(encrypted_char);
		}
		else
			Ciphertext += Plaintext[i];
	}

	return Ciphertext;
}

string Advanced_Decryption(string Ciphertext)
{
	string Plaintext = "";
	
	int a_inv = 0; //a^-1

	//Find a^-1
	for (int i = 0; i < 74; i++)
	{
		if ((a * i) % 74 == 1)
			a_inv = i;
	}

	for (int i = 0; i < Ciphertext.length(); i++)
	{
		int x = getIndex2(Ciphertext[i]);
		if(x!=-1){
			//decryption formula a^-1*(x - b) mod m
			int decrypted_char = (a_inv * (x - b + italianAlphabet2.size())) % italianAlphabet2.size();
			Plaintext += getChar2(decrypted_char);
		}
		else
			Plaintext += Ciphertext[i];
	}

	return Plaintext;
}

//Driver Program
int main()
{
	string message1 = "AMO LA CRITTOGRAFIA";
	string message2 = "AMI la crittografia?";

	//Calling Encryption and Decryption function
	cout << "Plain Message is: " << setw(23) << message1 << endl;
	cout << "Encrypted Message is: " << Encryption(message1) <<endl;
	cout << "Decrypted Message is: " << Decryption(Encryption(message1)) << endl << endl;

	//Calling Advanced_Encryption and Advanced_Decryption function
	cout << "Plain Message is: " << setw(33) << message2 << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(message2) << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Advanced_Encryption(message2)) << endl << endl;
	return 0;
}