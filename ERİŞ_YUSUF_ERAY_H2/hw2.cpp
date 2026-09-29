#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



// custom stoi function to handle errors and comas
int my_stoi(string s){
    int num = 0;
    bool negative = false;
    size_t i = 0;
    if(s[0] == '-'){
        negative = true;
        i = 1;
    }
    for(; i < s.length(); i++){
        if(s[i] == ',' && i == s.length() - 1){
            break;
        }
        if(s[i] < '0' || s[i] > '9'){
            cerr<<"syntax error in number conversion!"<<endl;
            exit(1);
        }
        num = num *10 + (s[i] - '0');
    }
    if(negative){
        num = -num;
    }
    return num;
}


// operand class to hold operation and its operands
class operand{
    public:
        string operation,o1,o2;

        operand(string op, string op1, string op2) : operation(op), o1(op1), o2(op2) {}

};
// CPU class to simulate the CPU operations
class CPU{
    private:
        int reg[6];
        unsigned int memory[100];
        public:
        int programCounter;
        CPU(){
            for(int i = 0; i<6;i++) reg[i] = 0;
            for(int i = 0; i<100;i++) memory[i] = 0;
            programCounter = 0;
        }
        void printRegisters() {
            cout << "R0=" << reg[0] << " R1=" << reg[1] << " R2=" << reg[2]
                 << " R3=" << reg[3] << " R4=" << reg[4] << " R5=" << reg[5] << endl;
        }
        void printMemory() {
            for (int i = 0; i < 100; i++) {
                cout << "Memory" << i << "=" << memory[i]<<" "; 
                if( i % 10 == 0)
                    cout << endl;
            }
            cout << endl;
        }   
        // ADD instruction implementation
        void ADD(operand f) {
           // r r 
            //r num
            // r address
            if(f.o1[0] == 'R' && f.o2[0] == 'R'){
                reg[f.o1[1]-'0'] += reg[f.o2[1]-'0'];
            }
            else if(f.o1[0] == 'R' && f.o2[0] == '#'){
                f.o2 = f.o2.substr(1);
                reg[f.o1[1]-'0'] += memory[my_stoi(f.o2)-1];
            }
            else if(f.o1[0] == 'R' && f.o2.length() > 0){
                reg[f.o1[1]-'0'] += my_stoi(f.o2);
            }
            else{
                cerr<<"syntax error in ADD instruction!"<<endl;
                exit(1);
            }
        }
        // SUB instruction implementation
        void SUB(operand f){
            // r r 
            //r num
            // r address
            if(f.o1[0] == 'R' && f.o2[0] == 'R'){
                reg[f.o1[1]-'0'] -= reg[f.o2[1]-'0'];
            }
            else if(f.o1[0] == 'R' && f.o2[0] == '#'){
                f.o2 = f.o2.substr(1);
                reg[f.o1[1]-'0'] -= memory[my_stoi(f.o2)-1];
            }
            else if(f.o1[0] == 'R' && f.o2.length() > 0){
                reg[f.o1[1]-'0'] -= my_stoi(f.o2);
            }
            else{
                cerr<<"syntax error in SUB instruction!"<<endl;
                exit(1);
            }
        }
       // JMP instruction implementation
        void JMP(operand f){
            // reg #
            // reg num
            // num
            if(f.o1[0] == 'R'){
            
                if(f.o2[0] == '#'){
                    f.o2 = f.o2.substr(1);
                    if(reg[f.o1[1]-'0'] <= 0){
                        programCounter = my_stoi(f.o2) - 1;
                    }
                }
                else{
                    if(reg[f.o1[1]-'0'] <= 0){
                        programCounter = my_stoi(f.o2) - 1; //conditional jump
                    }
                }
            }
            else{
                programCounter = my_stoi(f.o1) - 1;
            }
            if(programCounter < 0 || programCounter > 500){
                cerr<<"jumping to invalid address!"<<endl;
                exit(1);
                // out of bounds
            }
            
       }
       // MOV instruction implementation 
       void MOV(operand f){
           
            // r r
            // r num
            // r address
            // address r
            // address num

            if(f.o1[0] == 'R' && f.o2[0] == 'R'){
                reg[f.o1[1]-'0'] = reg[f.o2[1]-'0'];
            }
            else if(f.o1[0] == 'R' && f.o2[0] == '#'){
                f.o2 = f.o2.substr(1);
                reg[f.o1[1]-'0'] = memory[my_stoi(f.o2)-1];
            }
            else if(f.o1[0] == 'R' && f.o2.length() > 0){
                reg[f.o1[1]-'0'] = my_stoi(f.o2);
            }
            else if(f.o1[0] == '#' && f.o2[0] == 'R'){
                f.o1 = f.o1.substr(1); 
                memory[my_stoi(f.o1)-1] = reg[f.o2[1]-'0'];
            }
            else if(f.o1[0] == '#' && f.o2.length() > 0){

                f.o1 = f.o1.substr(1);
                memory[my_stoi(f.o1)-1] = my_stoi(f.o2);
                
            }
            else{
                cerr<<"syntax error in MOV instruction!"<<endl;
                exit(1);
            }
        }
        
        // PRN instruction implementation
        void PRN(operand f){
            if(f.o1[0]=='R' && f.o2.empty()){
                cout<<reg[f.o1[1]-'0']<<endl;
            }
            else if(f.o1[0]=='#' && f.o2.empty()){
                f.o1 = f.o1.substr(1);
                cout<<memory[my_stoi(f.o1)-1]<<endl;
            }
            else if(f.o1.length() > 0 && f.o2.empty()){
                cout<<my_stoi(f.o1)<<endl;
            }
            else{
                cerr<<"syntax error in PRN instruction!"<<endl;
                exit(1);
            }       
        }
       // INP instruction implementation
        void INP(operand f){
            cin>>reg[f.o1[1]-'0'];
        }
        // HLT instruction implementation
        void HLT(operand f){
            cout<<"R0"<<" "<<reg[0]<<" "<<"R1"<<"="<<reg[1]<<" "<<"R2"<<"="<<reg[2]<<" "<<"R3"<<"="<<reg[3]<<" "<<"R4"<<"="<<reg[4]<<" "<<"R5"<<"="<<reg[5]<<endl;
            exit(0);
        }

        // Execute the given operand instruction
        void execute(operand f){
            if(f.operation == "ADD"){
                ADD(f);
                programCounter++;
            }
            else if(f.operation == "SUB"){
                SUB(f);
                programCounter++;
            }
            else if(f.operation == "JMP"){
                JMP(f);
            }
            else if(f.operation == "MOV"){
                MOV(f);
                programCounter++;
            }
            else if(f.operation == "PRN"){
                PRN(f);
                programCounter++;
            }
            else if(f.operation == "INP"){
                INP(f);
                programCounter++;
            }
            else if(f.operation == "HLT"){
                HLT(f);
            }
        
    

        }
    
};






// Function to check the validity of the input instruction
bool check_input(string op, string o1, string o2){
    if(op != "MOV" && op != "ADD" && op != "SUB" && op != "JMP" && op != "PRN" && op != "INP" && op != "HLT"){
        cout<<op<<endl;
        return false;
    }
    if(op == "HLT"){
        if(o1 != "" || o2 != ""){
            return false;
        }
        return true;
    }
    if(o1[0] == 'R'){
       
        if(o2.empty()){
            if(o1.length() != 2){
                return false;
            }
            if(o1[1] < '0' || o1[1] > '5'){
                return false;
            }
            return true;
        }
        else if(o2[0] == 'R'){
            if(o2.length() != 2){
                return false;
            }
            if(o1[1] == o2[1]){
                cout<<"syntax error: same register used!"<<endl;
                return false;
            }
            if(o1.length() != 3){
                return false;
            }
            if(o1[2] != ','){
                return false;
            }
            if(o1[1] < '0' || o1[1] > '5' || o2[1] < '0' || o2[1] > '5'){
                return false;
            }
            
        }
        else if(o2[0] == '#'){
            if(o1.length() != 3){
                return false;
            }
            if(o1[1] < '0' || o1[1] > '5'){
                return false;
            }
            if(o1[2] != ','){
                return false;
            }

            string num = o2.substr(1);
            if(num.empty()){
                return false;
            }
            if(my_stoi(num)<= 99 && my_stoi(num)>= 0){
            }
            else{
                return false;
            }
            
            
        }
        else if(my_stoi(o2)<= 999 && my_stoi(o2)>= -999){
            if(o1.length() != 3){
                return false;
            }
            if(o1[1] < '0' || o1[1] > '5'){
                return false;
            }
            if(o1[2] != ','){
                return false;
            }

            


        }
        
        else{
            return false;
        }
        return true;
    }
    else if(o1[0] == '#'){
        string mem = o1.substr(1);
        if(mem.empty()){
            return false;
        }
        if(op == "PRN"){
            if(o2 != ""){
                return false;
            }
            int addr = my_stoi(mem);
            if(addr <0 || addr > 99){
                return false;
            }
            return true;
        }
        int i = 0;
        while (o1[i] != ','){
            if(i>= o1.length()){
                return false;
            }
            i++;
        }

        string addr = mem.substr(0,i-1);
        if(my_stoi(addr)<= 99 && my_stoi(addr)>= 0){
        }
        else{
            return false;
        }

        if(o2[0] == 'R'){
            if(o2.length() != 2){
                return false;
            }
            if(o2[1] < '0' || o2[1] > '5'){
                return false;
            }
        }
        else if(o2[0] == '#'){
            return false;
        }
        else if(my_stoi(o2)<= 999 && my_stoi(o2)>= -999){}
        else{
            return false;
        }
     
    return true;
    }
    else if(my_stoi(o1)<= 500 && my_stoi(o1)>= 0){
        if(o2 != ""){
            return false;
        }
        return true;
    }
    else{
        return false;
    }
}
// Function to check if HLT instruction is present
bool halt_check(string lines[], int total_lines){
    for(int i =0; i<total_lines;i++){
        string code = lines[i].substr(0, lines[i].find(';'));
        stringstream ss(code);
        string operation;
        ss>>operation;
        if(operation == "HLT"){
            return true;
        }
    }
    return false;
}

int main(int argc,char*  argv[]){
    if(argc != 3){
        cerr<<"please provide input and output file names as command line arguments!"<<endl;
        return -1;
    }
    if(argv[1] == nullptr || argv[2] == nullptr){
        cerr<<"file name error!"<<endl;
        return -1;
    }
    // read input file
    ifstream yf;
    yf.open(argv[1]);
    string lines[500];
    int i = 0;
    while(getline(yf,lines[i])){
        if(i>500) {
            cerr<<"you can write max 500 line !!";
            return -1;
        }
        i++;

    }
    yf.close();
    if(!halt_check(lines, i)){
        cerr<<"no HLT instruction found!"<<endl;
        return -1;
    }
    // CPU simulation
    CPU cpu;
    int j = 0;
    string code, operation = "", o1 = "", o2 = "", o3 = "";

    while(j<i){ 
        code = lines[j].substr(0, lines[j].find(';'));  // remove comments
        stringstream ss(code);
        // parse operation and operands if exist
        if(ss >> operation){

        }
        else{
            cerr<<"where is  the operation in line "<<j+1<<" ?????"<<endl;
            return -1;
        }

        if(ss >> o1){
        }
        else{
            o1 = "";
        }
        if(ss>>o2){
        }
        else{
            o2 = "";
        }
        if(ss>>o3){
            cerr<<"syntax error in line "<<j+1<<endl;
            return -1;
        }
        if(!check_input(operation, o1, o2)){
            cerr<<"syntax error (check function) in line "<<j+1<<endl;
            return -1;
        }
        operand op(operation, o1, o2);

        int old = cpu.programCounter; // önce al
        cpu.execute(op);

        if (cpu.programCounter == old)
            cpu.programCounter++;

        j = cpu.programCounter;

        switch (my_stoi(argv[2])){
            case 0:
                break;
            case 1:
                cpu.printRegisters();
                break;
            case 2:
                cpu.printRegisters();
                cpu.printMemory();
                break;
            default:
                cerr<<"wrong debug option!"<<endl;
                return -1;
        }

    }

   
    


    return 0;
}