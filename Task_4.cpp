#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Key values of a and b
const int a = 5;
const int b = 8;
const string Alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int getIndex(char ch) {
    int index = Alphabet.find(ch);
    return (index >=0)? index : -1;
}

char getChar(int index) {
    return Alphabet[index];
}

string Decryption(string Ciphertext)
{
	string Plaintext = "";
	int a_inv = 0; //a^-1

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
			int encrypted_char = (a * x + b) % Alphabet.size();
			Ciphertext += getChar(encrypted_char);
		}
		else
			Ciphertext += Plaintext[i];	 
	}
	
	return Ciphertext;
}

string Advanced_Decryption(string Ciphertext)
{
	string Plaintext = "";
	
	int a_inv1 = 0; //a^-1(1)
	int a_inv2 = 0; //a^-1(2)

    for(int i=0; i < Ciphertext.length(); i++)
        Ciphertext[i] = toupper (Ciphertext[i]);

	//Find a^-1(1)
	for (int i = 0; i < 27; i++)
	{
		if ((a * i) % 27 == 1)
			a_inv1 = i;
	}
    
	//Find a^-1(2)
	for (int i = 0; i < 33; i++)
	{
		if ((a * i) % 33 == 1)
			a_inv2 = i;
	}
	
	for (int i = 0; i < Ciphertext.length(); i++)
	{
		if('A'<=Ciphertext[i]||' '==Ciphertext[i]){
			int x = getIndex(Ciphertext[i]);
			if(x!=-1){
				//decryption formula a^-1*(x - b) mod m
				int decrypted_char = (a_inv1 * (x - b + Alphabet.size())) % Alphabet.size();
				Plaintext += getChar(decrypted_char);
			}
			else
				Plaintext += Ciphertext[i];
		}
		else if('!'<=Ciphertext[i])
			Plaintext += (char) (((a_inv2 * ((Ciphertext[i]+'!' - b)) % 33)) + '!');
		else
			Plaintext += Ciphertext[i]; 
	}

	return Plaintext;
}

string Advanced_Encryption(string Plaintext)
{
	string Ciphertext = "";

    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if('A'<=Plaintext[i]||' '==Plaintext[i]){
			int x = getIndex(Plaintext[i]);
			if(x!=-1){
				//encryption formula (ax + b) mod m
				int encrypted_char = (a * x + b) % Alphabet.size();
				Ciphertext += getChar(encrypted_char);
			}
			else
				Ciphertext += Plaintext[i];
		}
		else if('!'<=Plaintext[i])
			Ciphertext += (char) ((((a * (Plaintext[i]-'!')) + b) % 33) + '!');
		else
			Ciphertext += Plaintext[i];	 
	} 

	return Ciphertext;
}

//Driver Program
int main()
{
	string Ciphertext1 = "OFHSBJFHM HXZPU ";
	string Ciphertext2 = "OFHSBJFHM HXZPU 1256?!+* asdf";

	//Calling Decryption and Encryption function
	cout << "Message is: " << setw(26) << Ciphertext1 << endl;
	cout << "Decrypted Message is: " << Decryption(Ciphertext1) << endl;
	cout << "Encrypted Message is: " << Encryption(Decryption(Ciphertext1)) << endl << endl;

	//Calling Advanced_Decryption and Advanced_Encryption function
	cout << "Message is: " << setw(48) << Ciphertext2 << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Ciphertext2) << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(Advanced_Decryption(Ciphertext2)) << endl << endl;

	return 0;
}