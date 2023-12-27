#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// English alphabet strings
const string Alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string Alphabet2 = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//Function to get the index of a character in the first English alphabet string
int getIndex(char ch) {
    int index = Alphabet.find(ch);
    return (index >=0)? index : -1;
}

// Retrieve a character from the first English alphabet string by index
char getChar(int index) {
    return Alphabet[index];
}

//Function to get the index of a character in the second English alphabet string
int getIndex2(char ch) {
    int index = Alphabet2.find(ch);
    return (index >=0)? index : -1;
}

// Retrieve a character from the second English alphabet string by index
char getChar2(int index) {
    return Alphabet2[index];
}

string Decryption(string Ciphertext, int a, int b)
{
	string Plaintext = "";
	int a_inv = 0; //a^-1

	// convert all to uppercase
    for(int i=0; i < Ciphertext.length(); i++)
        Ciphertext[i] = toupper (Ciphertext[i]);

	//Find a^-1
	for (int i = 0; i < 27; i++)
	{
		if ((a * i) % 27 == 1)
			a_inv = i;
	}
    
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		int x = getIndex(Ciphertext[i]);
		if(x!=-1){
			//decryption formula a^-1*(x - b) mod m
			int decrypted_char = (a_inv * (x - b + Alphabet.size())) % Alphabet.size();
			Plaintext += getChar(decrypted_char);
		}
		else
			Plaintext += Ciphertext[i]; 
	}

	return Plaintext;
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
			int encrypted_char = (a * x + b) % Alphabet.size();
			Ciphertext += getChar(encrypted_char);
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
	for (int i = 0; i < 84; i++)
	{
		if ((a * i) % 84 == 1)
			a_inv = i;
	}
	
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		int x = getIndex2(Ciphertext[i]);
		if(x!=-1){
			//decryption formula a^-1*(x - b) mod m
			int decrypted_char = (a_inv * (x - b + Alphabet2.size())) % Alphabet2.size();
			Plaintext += getChar2(decrypted_char);
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
			int encrypted_char = (a * x + b) % Alphabet2.size();
			Ciphertext += getChar2(encrypted_char);
		}
		else
			Ciphertext += Plaintext[i];
	} 

	return Ciphertext;
}

//Driver Program
int main()
{
	string message1 = "OFHSBJFHM HXZPU ";
	string message2 = "Do we move at night?";

	//Key values of a and b
	int a=5;
	int b=8;

	cout << "----------------Given Sentence----------------" << endl << endl;
	cout << "----------------Using Basic Functions----------------" << endl;
	//Calling Decryption and Encryption function
	cout << "Message is: " << setw(26) << message1 << endl;
	cout << "Decrypted Message is: " << Decryption(message1,a,b) << endl;
	cout << "Encrypted Message is: " << Encryption(Decryption(message1,a,b),a,b) << endl << endl;

	cout << "----------------Using Advanced Functions----------------" << endl;
	//Calling Advanced_Decryption and Advanced_Encryption function
	cout << "Message is: " << setw(39) << message2 << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(message2,a,b) << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Advanced_Encryption(message2,a,b),a,b) << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(Advanced_Decryption(Advanced_Encryption(message2,a,b),a,b),a,b) << endl << endl;

	string sentence;
	int a1, b1;
	
	cout << "----------------User Input----------------" << endl << endl;
	cout << "Enter the sentence to decipher: ";
	getline(cin,sentence);
	cout << "Enter the value of 'a': ";
	cin >> a1;
	cout << "Enter the value of 'b': ";
	cin >> b1;
	cout << "Decrypted Message is: "<< Decryption(sentence, a1, b1) << endl;
	cout << "Encrypted Message is: " << Encryption(Decryption(sentence,a1,b1),a1,b1) << endl;

	return 0;
}