#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class hamming{
    public:
        string data;   
        int m , r = 0; // m - length of data, r - length of redundant bits.
        char* code;
        hamming(string data){
            this->data = data;

            reverse(data.begin(),data.end());
            m = data.size();
            
            int power = 1;
 
            //the number of redundant bits
            while(power < (m + r + 1)){
                r++;
                power*=2;
            }
    
            code = new char[m+r+1];
            int curr = 0;
 
            //initializing the msg with data bits
            for(int i = 1 ; i <= m+r ; i++){
                if(i & (i-1)){
                    code[i] = data[curr++]; 
                }
                else code[i] = 'n';
            }
            //set the redundant bits
            set_redundant_bits();
        }
        void print_code(){
            cout << "the data packet to be sent is :   ";
            for(int i = m+r ; i >= 1 ; i--){
                cout << code[i] << " ";
            }
            cout << endl;
        }

        void set_redundant_bits(){
            int bit = 0;
            
            for(int i = 1 ; i  <= m+r ; i*=2){
                int cnt = 0;
                for(int j = i+1 ; j<=m+r ; j++){
                    if(j & (1 << bit)){
                        if(code[j] == '1') cnt++; 
                    }
                }
                //set redundant bits
                if(cnt & 1) code[i] = '1';
                else code[i] = '0';

                bit++;
            }
            print_code();
        }
        void decoder(){
            string res = "";
            int bit = 0;
            
            for(int i = 1 ; i  <= m+r ; i*=2){
                int cnt = 0;
                for(int j = i+1 ; j<=m+r ; j++){
                    if(j & (1 << bit)){
                        if(code[j] == '1') cnt++;
                    }
                }
                if(cnt & 1){
                    if(code[i] == '1') res.push_back('0');
                    else res.push_back('1');
                }
                else{
                    if(code[i]=='0') res.push_back('0');
                    else res.push_back('1');
                }
                bit++;
            }
    
            if(res.find('1') != string::npos){
                int power = 1;
                int wrongbit = 0;
            
                for(int i = 0 ; i < res.size() ; i++){
                    if(res[i]=='1') wrongbit+=power;
                    power*=2;
                }
                cout << "bit number: " << wrongbit << " is wrong" << endl;
            }
            else{
                cout << "correct data" << endl;
            }
        }
};

void change_bit(hamming& h){
    h.code[2] = '1';
}

int main(){
    string data = "10110111011";
    hamming h(data);
   
    change_bit(h);
    h.decoder();
    return 0;
}
