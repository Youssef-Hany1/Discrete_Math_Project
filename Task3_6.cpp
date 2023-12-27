#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// Italian alphabet strings
const string italianAlphabet = " ABCDEFGHILMNOPQRSTUVZ";
const string italianAlphabet2 = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHILMNOPQRSTUVZabcdefghilmnopqrstuvz";

//Function to get the index of a character in the first italian alphabet string
int getIndex(char ch) {
    int index = italianAlphabet.find(ch);
    return (index >=0)? index : -1;
}

// Retrieve a character from the first Italian alphabet string by index
char getChar(int index) {
    return italianAlphabet[index];
}

//Function to get the index of a character in the second italian alphabet string
int getIndex2(char ch) {
    int index = italianAlphabet2.find(ch);
    return (index >=0)? index : -1;
}

// Retrieve a character from the second Italian alphabet string by index
char getChar2(int index) {
    return italianAlphabet2[index];
}

string Encryption(string Plaintext, int a, int b)
{
	string Ciphertext = ""; 
	
	// convert all to uppercase
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

string Decryption(string Ciphertext, int a, int b)
{
	string Plaintext = "";
	int a_inv = 0; //a^-1

	// convert all to uppercase
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

string Advanced_Encryption(string Plaintext, int a, int b)
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

string Advanced_Decryption(string Ciphertext, int a, int b)
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

	//Key values of a and b
	int a=5;
	int b=8;

	cout << "----------------Given Sentence----------------" << endl << endl;
	cout << "----------------Using Basic Functions----------------" << endl;
	//Calling Encryption and Decryption function
	cout << "Plain Message is: " << setw(23) << message1 << endl;
	cout << "Encrypted Message is: " << Encryption(message1,a,b) <<endl;
	cout << "Decrypted Message is: " << Decryption(Encryption(message1,a,b),a,b) << endl << endl;

	cout << "----------------Using Advanced Functions----------------" << endl;
	//Calling Advanced_Encryption and Advanced_Decryption function
	cout << "Plain Message is: " << setw(33) << message2 << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(message2,a,b) << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Advanced_Encryption(message2,a,b),a,b) << endl << endl;

	string sentence;
	int a1, b1;
	
	cout << "----------------User Input----------------" << endl << endl;
	cout << "Enter the sentence to cipher: ";
	getline(cin,sentence);
	cout << "Enter the value of 'a': ";
	cin >> a1;
	cout << "Enter the value of 'b': ";
	cin >> b1;
	cout << "Decrypted Message is: "<< Encryption(sentence, a1, b1) << endl;
	cout << "Encrypted Message is: " << Decryption(Encryption(sentence,a1,b1),a1,b1) << endl;

	return 0;
}