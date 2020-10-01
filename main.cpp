#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class BigNum {
//const int n = 20; //длина числа
public:
    const int sys_in = 4;
    const int n = 20; //длина числа
    unsigned int *num; //массив для хранения числа
    int numSys; //степень двойки системы счиисления (1 или 16 или 32)
    
    BigNum(unsigned int NumSys){ //инициализация нуля заданного размера для операций с заданной системой счисления
        numSys = NumSys;
        num = new unsigned int[n];
        for(int i=0; i<n; i++) {
            num[i] = 0;
        }

    }
    BigNum(unsigned int NumSys, string strNum){
        numSys = NumSys;
        num = new unsigned int[n];
        
        while (strNum.size()%(NumSys/sys_in)!=0){
          strNum = "0" + strNum;
        }
        //cout << "strNum" << strNum << endl;
        int temp = NumSys/sys_in; //cout << "temp=" << temp << endl;
        int len = strNum.size(); //cout << "len=" << len << endl;
        //cout << "len/temp=" << len/temp << endl; 
        
        for (int i = 0; i < len/temp; i++){
          //cout << "проход массива номер" << i+1 << endl;
          string temp2 = strNum.substr(strNum.size()-temp); //последние 4 цифры числа(если переводим из 2^4 в 2^16)
          //cout << "temp2=" << temp2 << endl;
          strNum.erase(strNum.size()-temp);
          num[i] = stoul(temp2, nullptr, 16);
        }
    }
    void coef(){
        for(int i=n-1; i>=0; i--) {
            if (num[i] != 0) cout<<num[i]<<" ";
        }
        cout<<endl;
    }

};

BigNum operator+(BigNum a, BigNum b) { 
    unsigned int carry = 0, temp;
    BigNum c = BigNum(a.numSys);

    for (int i = 0; i<c.n; i++) {
        temp = a.num[i] + b.num[i] + carry;
        c.num[i] = temp & ((int)pow(2, 16)-1); 
        carry = temp >> c.numSys; 
    }

    return c;

}
/*unsigned long hex2dec(string hex){
      unsigned long result = 0;
      for (int i=0; i<hex.length(); i++) {
          if (hex[i]>=48 && hex[i]<=57){
              result += (hex[i]-48)*pow(16,hex.length()-i-1);
              } else if (hex[i]>=65 && hex[i]<=70) {
              result += (hex[i]-55)*pow(16,hex.length( )-i-1);
              } else if (hex[i]>=97 && hex[i]<=102) {
              result += (hex[i]-87)*pow(16,hex.length()-i-1);
              }
          }
    return result;
}*/


int main() {
  //вводные данные
  int pow_2 = 16;
  string num1_hex = "3340E61CE70224FE109AA852D618FFBA53E9779C33B7782F73E55944AF6D54B75B7B537E2C57ADC8534A38433960F92DAF604D4F45FCD205280C63684FD3A711";
  string num2_hex = "27827BFFDE45CAF30918B836BC7AA7C9F99D26EE84C05CF3F5293B238038BA56B17057DF63B76ED964142BACA61A44E7EC562B371722A383D3F814C67D563E2E";
  

   //cout << stoul(num1_hex, nullptr, 16) << "+" << stoul(num2_hex, nullptr, 16) << "=" << stoul(num1_hex, nullptr, 16)+stoul(num2_hex, nullptr, 16) << endl; 

  BigNum a = BigNum(pow_2, num1_hex);
  BigNum b = BigNum(pow_2, num2_hex);

  BigNum c = a+b; 
  

  a.coef();
  b.coef();
  c.coef();

  return 0;
}
