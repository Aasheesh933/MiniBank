#include <stdio.h>
#include <string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/time.h>
#include<unistd.h>


string finddate(void){
	
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d.%m.%Y", localtime(&t));
    return s;
}


string lower(string str){
	
	string lc;
	for (unsigned int i=0; i<str.length(); i++){
		if (str[i] >= 'A' and str[i] <= 'Z'){
			lc += char(int(str[i]) + 32);
		}
		else{
			lc += str[i];
		}
	}
	return lc;
}


string trim(string s){

	bool q = true;
	while(q){
		if(s[0] == ' ')
			s = s.substr(1, s.length());
		else
			q = false;
	}
	q = true;
	while(q){
		if(s[s.length()-1] == ' ')
			s = s.substr(0, (s.length()-1));
		else
			q = false;
	}
	return s;
}


int split(string s, string ele, string splitted[]){
	
    unsigned int pos = 0, c = 0, a = 0;
    string temp, t = s;
	for (unsigned int i=0; i<=s.length(); i++){
        pos = t.find(ele);
        if(pos == 4294967295){
            break;
		}
        t = t.substr(pos+1, t.length()-pos);
        c++;
    }
    for(unsigned int i=0; i<=c; i++){
        pos = s.find(ele);
        temp = s.substr(0,pos);
        splitted[i] = temp;
        s = s.substr(pos+1, s.length()-pos);
		a = i;
    }
	splitted[a++] = s;
	return c+1;
}


string replace(string s, string ele, string rep){

    unsigned int pos = 0, c = 0;
    string temp, spt, t = s;
    for (unsigned int i=0; i<t.length(); i++){
        pos = t.find(ele);
        if(pos == 4294967295){
            break;
		}
        t = t.substr(pos+1, t.length()-pos);
        c++;
    }
    for(unsigned int i=0; i<c; i++){
        pos = s.find(ele);
        temp = s.substr(0,pos);
        spt += temp + rep;
        s = s.substr(pos+1, s.length()-pos);
    }
    spt += s;
    return spt;
}


char enshift(char ch, string u, unsigned short shift){

	short ind;
	char shifted;
	int newshift;
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	ind = alpha.find(ch);
	if (shift >= (alpha.length() - ind)){
		newshift = shift - (alpha.length() - ind);
		shifted = alpha[newshift];
	}
	else{
		shifted = alpha[ind + shift];
	}
	return shifted;
}


char deshift(char ch, string u, short shift){

	short ind;
	char shifted;
	int newshift, tempshift;
	string temp, alpha = "abcdefghijklmnopqrstuvwxyz";
	ind = alpha.find(ch);
	temp = alpha.substr(0,ind+1);
	tempshift = temp.length();
	if (shift >= tempshift){
		newshift = shift - tempshift;
		shifted = alpha[25-newshift];
	}
	else{
		shifted = alpha[ind - shift];
	}
	return shifted;
}


void encrypt(string u,string p, string encrypted[]){
	
	unsigned int shift;
	string uencrypt, pencrypt, alpha = "abcdefghijklmnopqrstuvwxyz";
	char s;
	for (unsigned int i=0; i<p.length(); i++){
		if (p[i]>='1' && p[i]<='9'){
			shift = p[i];
			shift -= 48;
			break;
		}
		else if (p[i] == '0'){
			shift = (int(p[i-1]) - int('0')) % 10;
		}
	}
	for (unsigned int i=0; i<u.length(); i++){
		for (int j=0; j<26; j++){
			if (alpha.find(u[i]) != string::npos){
				cout<<"user: "<<alpha.find(u[i])<<endl;
				s = enshift(u[i], u, shift);
				uencrypt += s;
				break;
			}
			else{
				uencrypt += char(int(u[i]) + shift);
				break;
			}
		}
	}
	for (unsigned int i=0; i<p.length(); i++){
		for (int j=0; j<26; j++){
			if (alpha.find(p[i]) != string::npos){
				cout<<"Pass: "<<alpha.find(p[i])<<endl;
				s = enshift(p[i], p, shift);
				pencrypt += s;
				break;
			}
			else if (p[i] != char(shift + 48)){
				if (p[i] == '0'){
					pencrypt += p[i];
					break;
				}
				else{
					pencrypt += char(int(p[i]) + shift);
					break;
				}
			}
			else{
				pencrypt += p[i];
				break;
			}
		}
	}
	encrypted[0] = uencrypt;
	encrypted[1] = pencrypt;
}


void decrypt(string u,string p, string decrypted[]){
	
	unsigned int shift;
	string udecrypt, pdecrypt, alpha = "abcdefghijklmnopqrstuvwxyz";
	char s;
	for (unsigned int i=0; i<p.length(); i++){
		if (p[i]>='1' && p[i]<='9'){
			shift = p[i];
			shift -= 48;
			break;
		}
		else if (p[i] == '0'){
			shift = (int(p[i-1]) - int('0')) % 10;
		}
	}
	for (unsigned int i=0; i<u.length(); i++){
		for (int j=0; j<26; j++){
			if (alpha.find(u[i]) != string::npos){
				s = deshift(u[i], u, shift);
				udecrypt += s;
				break;
			}
			else{
				udecrypt += char(int(u[i]) - shift);
				break;
			}
		}
	}
	for (unsigned int i=0; i<p.length(); i++){
		for (int j=0; j<26; j++){
			if (alpha.find(p[i]) != string::npos){
				s = deshift(p[i], p, shift);
				pdecrypt += s;
				break;
			}
			else if (p[i] != char(shift + 48)){
				if (p[i] == '0'){
					pdecrypt += p[i];
					break;
				}
				else{
					pdecrypt += char(int(p[i]) - shift);
					break;
				}
			}
			else{
				pdecrypt += p[i];
				break;
			}
		}
	}
	decrypted[0] = udecrypt;
	decrypted[1] = pdecrypt;
}