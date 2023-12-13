#include <string>
#include <iostream>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;
const string italianAlphabet = "ABCDEFGHILMNOPQRSTUVZ";

int getIndex(char ch) {
    int index = italianAlphabet.find(ch);
    return (index >=0)? index : -1;
}

char getChar(int index) {
    return italianAlphabet[index];
}

string Encryption(string Plaintext)
{
	string Ciphertext = ""; 
	
    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);
	
	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if(Plaintext[i]!=' '){
			int x = getIndex(Plaintext[i]);
			if(x!=-1){
				//encryption formula (ax + b) mod m
				int encrypted_char = (a * x + b) % italianAlphabet.size();
				Ciphertext += getChar(encrypted_char);
			}
			else
				Ciphertext += Plaintext[i];
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
	for (int i = 0; i < 21; i++)
	{
		if ((a * i) % 21 == 1)
			a_inv = i;
	}
    
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		if(Ciphertext[i]!=' '){
			int x = getIndex(Ciphertext[i]);
			if(x!=-1){
				//encryption formula (ax + b) mod m
				int decrypted_char = (a_inv * (x - b + italianAlphabet.size())) % italianAlphabet.size();
				Plaintext += getChar(decrypted_char);
			}
			else
				Plaintext += Ciphertext[i];
		}
		else
			 Plaintext += Ciphertext[i];
	}
	return Plaintext;
}

//Driver Program
int main()
{
	string Plaintext = "AMO LA CRITTOGRAFIA";

	cout << "Plain Message is: " << Plaintext << endl;
	
	string Ciphertext = Encryption(Plaintext);

	//Calling Encryption function
	cout << "Encrypted Message is: " << Encryption(Plaintext) <<endl;

	cout << "Decrypted Message is: " << Decryption(Encryption(Plaintext)) <<endl;
	return 0;
}