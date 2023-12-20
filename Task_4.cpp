#include <string>
#include <iostream>
#include <iomanip>
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

string Encryption(string Plaintext)
{
	string Ciphertext = ""; 

    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if(Plaintext[i]!=' ')
            //encryption formula (ax + b) mod m
			Ciphertext += (char) ((((a * (Plaintext[i]-'A')) + b) % 26) + 'A');
		else
			Ciphertext += Plaintext[i];	 
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
	for (int i = 0; i < 26; i++)
	{
		if ((a * i) % 26 == 1)
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
		if('A'<=Ciphertext[i])
			//decryption formula a^-1*(x - b) mod m
			Plaintext += (char) (((a_inv1 * ((Ciphertext[i]+'A' - b)) % 26)) + 'A');
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

string Advanced_Encryption(string Plaintext)
{
	string Ciphertext = ""; 
	string Plaintext1 = Plaintext;

    for(int i=0; i < Plaintext.length(); i++)
        Plaintext[i] = toupper (Plaintext[i]);

	for (int i = 0; i < Plaintext.length(); i++)
	{ 
		if('A'<=Plaintext[i])
            //encryption formula (ax + b) mod m
			Ciphertext += (char) ((((a * (Plaintext[i]-'A')) + b) % 26) + 'A');
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

//Driver Program
int main()
{
	string Ciphertext1 = "OFHSBJFHM HXZPU";
	string Ciphertext2 = "OFHSBJFHM HXZPU 1234?!+* asdf";

	//Calling Decryption and Encryption function
	cout << "Message is: " << setw(25) << Ciphertext1 << endl;
	cout << "Decrypted Message is: " << Decryption(Ciphertext1) << endl;
	cout << "Encrypted Message is: " << Encryption(Decryption(Ciphertext1)) << endl << endl;

	//Calling Advanced_Decryption and Advanced_Encryption function
	cout << "Message is: " << setw(48) << Ciphertext2 << endl;
	cout << "Advanced_Decrypted Message is: " << Advanced_Decryption(Ciphertext2) << endl;
	cout << "Advanced_Encrypted Message is: " << Advanced_Encryption(Advanced_Decryption(Ciphertext2)) << endl;

	return 0;
}