#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]){
    // Checking: Is the number of command-line arguments correct?
    if(argc != 3){
        cerr<<"wrong input while executation"<<endl;
        return -1;
    }

    // Initializing all registers to zero
    int reg[6];
    for(int i = 0; i<6;i++) reg[i] = 0;

    string operation, haltcheck;
    int jumpflag = -1;
    string line, code, r1, r2 , r3;

    // Opening the input file
    ifstream yf;
    yf.open(argv[1]);
    if(!yf.is_open()){
        cerr<<"file can not open"<<endl;
        return -1;
    }

    // Reading each line from the file
    while(getline(yf,line)){    
        // If there is a jump operation, jumping to the specified line
        if(jumpflag != -1){
            yf.clear();
            yf.seekg(0, ios::beg);
            for(int i = 0; i<jumpflag;i++){
               if( !(getline(yf,line))){
                     cerr<<"jump error"<<endl;
                     return -1;
               }
            }
            jumpflag = -1; 
        } 

        // Separating the code from comments in the line
        code = line.substr(0,line.find(';'));
        stringstream ss(code);
        ss>>operation;

        // Processing the MOV operation
        if(operation == "MOV"){
            ss>>r1>>r2;
            if(r2[0] == 'R'){
                // Moving the value from one register to another
                reg[r1[1]-'0'] = reg[r2[1]-'0'];
                // Checking format and register validity
                if(r1[0] != 'R' || r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r2[1]<'0' || r2[1]>'5' || r1.length()>3 || r2.length()>3 || ss>>r3){
                    cerr<<"wrong format or register"<<endl;
                    return -1;  
                }
            }
            else{
                // Assigning a constant value to a register
                reg[r1[1]-'0'] = stoi(r2);
                // Checking format and value validity
                if(r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r1.length()>3 || stoi(r2)<-9999 || stoi(r2)>9999 || ss>>r3){
                    cerr<<"wrong format, register, or value"<<endl;
                    return -1;  
                }
            }
        }
        // Processing the ADD operation
        else if(operation == "ADD"){
            ss>>r1>>r2;
            if(r2[0]=='R'){
                // Adding the values of two registers
                reg[r1[1]-'0'] = reg[r1[1]-'0'] + reg[r2[1]-'0'];
                // Checking format and register validity
                if(r1[0] != 'R' || r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r2[1]<'0' || r2[1]>'5' || r1.length()>3 || r2.length()>3 || ss>>r3){
                    cerr<<"wrong format or register"<<endl;
                    return -1;  
                }
            }
            else{
                // Adding a constant value to a register
                reg[r1[1]-'0'] = reg[r1[1]-'0'] + stoi(r2);
                // Checking format and value validity
                if(r1[0] != 'R' || r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r1.length()>3 || stoi(r2)<-9999 || stoi(r2)>9999 || ss>>r3){
                    cerr<<"wrong format, register, or value"<<endl;
                    return -1;  
                }
            }
        }
        // Processing the SUB operation
        else if(operation == "SUB" ){
            ss>>r1>>r2;
            if(r2[0]=='R'){
                // Subtracting the value of one register from another
                reg[r1[1]-'0'] = reg[r1[1]-'0'] - reg[r2[1]-'0'];
                // Checking format and register validity
                if(r1[0] != 'R' || r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r2[1]<'0' || r2[1]>'5' || r1.length()>3 || r2.length()>3 || ss>>r3){
                    cerr<<"wrong format or register"<<endl;
                    return -1;  
                }
            }
            else{
                // Subtracting a constant value from a register
                reg[r1[1]-'0'] = reg[r1[1]-'0'] - stoi(r2);
                // Checking format and value validity
                if(r1[0] != 'R' || r1[1]<'0' || r1[1]>'5' || r1.length()>3 || stoi(r2)<-9999 || stoi(r2)>9999 || ss>>r3){
                    cerr<<"wrong format, register, or value"<<endl;
                    return -1; 
                }
            }
        }
        // Processing the JMP operation
        else if(operation == "JMP"){
            ss>>r1;
            if(r1[0]=='R'){
                ss>>r2;
                // If the register value is zero, jumping to the specified line
                if(reg[r1[1]-'0']== 0){
                    jumpflag = stoi(r2);
                }
                // Checking format and value validity
                if(r1[2] != ',' || r1[1]<'0' || r1[1]>'5' || r1.length()>3 || stoi(r2)<-9999 || stoi(r2)>9999 || ss>>r3){
                    cerr<<"wrong format, register, or value"<<endl;
                    return -1;  
                }
            }
            else{
                // Jumping to the specified line
                jumpflag = stoi(r1);
                // Checking value validity
                if(stoi(r1)<-9999 || stoi(r1)>9999 || ss>>r2){
                    cerr<<"wrong value or format"<<endl;
                    return -1;  
                }
            }
        }
        // Processing the HLT operation
        else if(operation == "HLT"){
            // Printing the values of all registers and terminating the program
            cout<<"R0"<<" "<<reg[0]<<" "<<"R1"<<"="<<reg[1]<<" "<<"R2"<<"="<<reg[2]<<" "<<"R3"<<"="<<reg[3]<<" "<<"R4"<<"="<<reg[4]<<" "<<"R5"<<"="<<reg[5]<<endl;
            break;
        }   
        // Processing the PRN operation
        else if(operation == "PRN"){
            ss>>r1;
            if(r1[0]=='R'){
                // Printing the value of a register
                if(r1[1]<'0' || r1[1]>'5' || r1.length()>3 || ss>>r2){
                    cerr<<"wrong register or format"<<endl;
                    return -1;
                }
                cout<<reg[r1[1]-'0']<<endl;
            }
            else{
                // Printing a constant value
                cout<<stoi(r1)<<endl;
                if(stoi(r1)<-9999 || stoi(r1)>9999 || ss>>r2){
                    cerr<<"wrong value or format"<<endl;
                    return -1;  
                }
            }
        }
        // Processing the INP operation
        else if(operation == "İNP"){
            ss>>r1;
            // Taking input from the user and storing it in a register
            cin>>reg[r1[1]-'0'];
            // Checking format and register validity
            if(r1[0] != 'R' || r1[1]<'0' || r1[1]>'5' || ss>>r2){
                cerr<<"wrong format or register"<<endl;
                return -1;  
            }
        }
        // If an unknown operation is encountered, throwing an error
        else{
            cerr<<"op can not found";
            return -1;
        }

        // If debug mode is enabled, printing the operation and register states
        if(stoi(argv[2])==1){
            cout<<operation<<" "<<r1<<" "<<r2<<" "<<reg[0]<<" "<<reg[1]<<" "<<reg[2]<<" "<<reg[3]<<" "<<reg[4]<<" "<<reg[5]<<endl;
        }
    }
    
    // Closing the file
    yf.close();
    return 0;
}