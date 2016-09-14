#include <iostream>
#include <cstring>
#include <bitset>

using namespace std;

static const string strNull = "<0>";

static const string strPad = "=";

static const string strBase64Chars = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";


class Base64wn 
{
	public:
		Base64wn();		
		void setEncoded(string vStr);
		void setDecoded(string vStr);
		string getEncoded();
		string getDecoded();	
		string getBinary();	
	
	private:
		string strEncoded;
		string strDecoded;
		string strBinary;
		bool isNull(int vPos);
};


Base64wn::Base64wn(){
	strEncoded = "";
	strDecoded = "";	
	strBinary  = "";
}


void Base64wn::setEncoded(string vStr) {
	strEncoded = vStr;
}


void Base64wn::setDecoded(string vStr) {
	strDecoded = vStr;
	
	//strEncoded.reserve(((vStr.size()/3) + (vStr.size() % 3 > 0)) * 4);

	const char* cStr = vStr.data();

	for (int i = 0; i < strlen(cStr); i++) {

        if (!isNull(i)) {
		    bitset<8> b(cStr[i]);
            strBinary = strBinary + b.to_string();
        } else {
            strBinary = strBinary + "00000000";
            i = i + (strNull.length()-1);    
        }
        //cout << cStr << " " << strlen(cStr) << " " << i << "\n";
	}

    string tmpArray[] = "";

    for (int i = 0; i < (strBinary.length()/6); i++) {
        tmpArray[i] = strBinary.substr((i*6),6);
    }

    for (int i = 0; i < sizeof(tmpArray); i++) {
        cout << tmpArray[i];
    }


}


string Base64wn::getEncoded() {
	return strEncoded;
}


string Base64wn::getDecoded() {
	return strDecoded;
}


string Base64wn::getBinary() {
	return strBinary;
}

bool Base64wn::isNull (int vPos) {
	if (strDecoded.length() < (strNull.length()+vPos)){
		return false;
        } else {
        	if (strcmp(strDecoded.substr(vPos,strNull.length()).data(),strNull.data()) != 0) {
        		return false;
        	} else {
        	        return true;
                }
        }
}



bool isNull (string vStr, int vPos) {	
	//Return <> 0 if vStr is not equal to strNull 
	//Return 0 if vStr is equal to strNull
	
	//char vChar = vStr.data();

	if (vStr.length()  < (strNull.length()+vPos)){

		return false;

	} else {

		if (strcmp(vStr.substr(vPos,strNull.length()).data(),strNull.data()) != 0) {

			return false;

		} else {
	
			return true;
		
		}

	}	
}

int main () {
	
	Base64wn b64;	
	b64.setDecoded("h<0>a");

    cout << b64.getBinary() << "\n";

	return 0;
}
