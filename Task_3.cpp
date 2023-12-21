#include <string>
#include <iostream>
#include <iomanip>
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

string Advanced_Encryption(string Plaintext)
{
	string Ciphertext = ""; 
	string Plaintext1 = Plaintext;

    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if('A'<=Plaintext[i]){
			int x = getIndex(Plaintext[i]);
			if(x!=-1){
				//encryption formula (ax + b) mod m
				int encrypted_char = (a * x + b) % italianAlphabet.size();
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

	for(int i=0; i < Plaintext.length(); i++){
		if(Plaintext1[i]!=Plaintext[i])
			Ciphertext[i]=tolower(Ciphertext[i]);
	} 

	return Ciphertext;
}

string Advanced_Decryption(string Ciphertext)
{
	string Plaintext = "";
	string Ciphertext1 = Ciphertext;
	
	int a_inv1 = 0; //a^-1(1)
	int a_inv2 = 0; //a^-1(2)

    for(int i=0; i < Ciphertext.length(); i++)
        Ciphertext[i] = toupper (Ciphertext[i]);

	//Find a^-1(1)
	for (int i = 0; i < 21; i++)
	{
		if ((a * i) % 21 == 1)
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
		if('A'<=Ciphertext[i]){
			int x = getIndex(Ciphertext[i]);
			if(x!=-1){
				//encryption formula (ax + b) mod m
				int decrypted_char = (a_inv1 * (x - b + italianAlphabet.size())) % italianAlphabet.size();
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
	
	for(int i=0; i < Ciphertext.length(); i++){
		if(Ciphertext1[i]!=Ciphertext[i])
			Plaintext[i]=tolower(Plaintext[i]);
	} 

	return Plaintext;
}

//Driver Program
int main()
{
	string Plaintext = "AMO LA CRITTOGRAFIA";
	string Plaintext2 = "AMO LA CRITTOGRAFIA 1256?!+* asdf";

	//Calling Encryption and Decryption function
	cout << "Plain Message is: " << setw(23) << Plaintext << endl;
	cout << "Encrypted Message is: " << Encryption(Plaintext) <<endl;
	cout << "Decrypted Message is: " << Decryption(Encryption(Plaintext)) << endl << endl;

	//Calling Advanced_Encryption and Advanced_Decryption function
	cout << "Plain Message is: " << setw(46) << Plaintext2 << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(Plaintext2) << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Advanced_Encryption(Plaintext2)) << endl;
	return 0;
}