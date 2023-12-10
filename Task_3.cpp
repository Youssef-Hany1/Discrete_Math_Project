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
            //encryption formula (ax + b) mod m
			Ciphertext += (char) ((((a * (Plaintext[i]-'A')) + b) % 26) + 'A');
		else
			Ciphertext += Plaintext[i];	 
	}
	return Ciphertext;
}

//Driver Program
int main()
{
	string Plaintext = "affine";
	
	//Calling Encryption function
	cout << "Encrypted Message is: " << Encryption(Plaintext) <<endl;

	return 0;
}