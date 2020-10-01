/**
 * Тумаков М8О-206Б-19
 * Создать класс BitString для работы с 96-битовыми строками. Битовая строка должна быть представлена двумя полями: 
 * старшая часть unsigned long long, младшая часть unsigned int. Должны быть реализованы все традиционные операции 
 * для работы с битами: and, or, xor, not. Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное 
 * количество битов. Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству 
 * единичных битов. Реализовать операцию проверки включения.
 */

#include <iostream>
#include <string>
#include <bitset>

using namespace std;
typedef unsigned long long ull;
typedef unsigned int ui;

class bit_str
{
    public:
    //конструктор класса по умолчанию;
    bit_str(){
        up=0;
        down=0;
    }
    //конструктор класса;
    bit_str(ull a, ui b){
        up=a;
        down=b;
    }
    //получить значение старшей строки(64бит)
    ull GetUp(){
        return up;
    }
    //получить значение младшей строки(32бит)  
    ui GetDown(){
        return down;
    }
    //установить значение строки
    void Set(ull up, ui down) {
        this->up = up;
        this->down = down;
    }
    //перегрузка оператора & (И)
    bit_str operator&(bit_str b){
        bit_str c;
        c.up = up & b.up;
        c.down = down & b.down;
        return c;
    }
    //перегрузка оператора &= (И)
    bit_str operator&=(bit_str b){
        up = up & b.up;
        down = down & b.down;
        return *this;
    }
    //перегрузка оператора | (ИЛИ)
    bit_str operator|(bit_str b){
        bit_str c;
        c.up = up | b.up;
        c.down = down | b.down;
        return c;
    }
    //перегрузка оператора |= (ИЛИ)
    bit_str operator|=(bit_str b){
        up = up | b.up;
        down = down | b.down;
        return *this;
    }
    //перегрузка оператора ^
    bit_str operator^(bit_str b){
        bit_str c;
        c.up = up ^ b.up;
        c.down = down ^ b.down;
        return c;
    }
    //перегрузка оператора ^=
    bit_str operator^=(bit_str b){
        up = up ^ b.up;
        down = down ^ b.down;
        return *this;
    }
    //перегрузка оператора ~ (НЕ)
    bit_str operator~(){
        up = ~up;
        down = ~down;
        return *this;
    }
    //перегрузка оператора сдвига <<
    bit_str operator<<(const int& num) {
        ui downL;
        for (int i = 0; i < num; i++) {
            downL= (down & (1<<31)) >> 31;
            up = (up<<1) | downL;
            down = ((down)<<1);
        }
        return *this;
    }
    //перегрузка оператора сдвига <<=
    bit_str operator<<=(const int& num) {
        return (*this=*this<<num);
    }
    //перегрузка оператора сдвига >>
    bit_str operator>>(const int& num){
        ui up1;
        for (int i = 0; i < num; i++) {
            up1= up & 1;
            up = ((up)>>1);
            down = ((down)>>1) | (up1<<31);
        } 
        return *this;
    }
    //перегрузка оператора сдвига >>=
    bit_str operator>>=(const int& num){
        return (*this=*this>>num);
    }
    //перегрузка оператора сравнения >
    bool operator>(const bit_str& b){
        if(up > b.up){
            return true;
        }
        else if(up < b.up){
            return false;
        }
        else if(down > b.down){
            return true;
        } 
        else {
            return false;
        }
    }
    //перегрузка оператора сравнения <
    bool operator<(const bit_str& b){
        if(up < b.up){
            return true;
        }
        else if(up > b.up){
            return false;
        }
        else if(down < b.down){
            return true;
        } 
        else {
            return false;
        }
    }
    //перегрузка оператора сравнения >=
    bool operator>=(const bit_str& b){
        if(up > b.up){
            return true;
        }
        else if(up < b.up){
            return false;
        }
        else if(down > b.down){
            return true;
        } 
        else if(down < b.down){
            return false;
        }
        else{
            return true;
        }
    }
    //перегрузка оператора сравнения <=
    bool operator<=(const bit_str& b){
        if(up < b.up){
            return true;
        }
        else if(up > b.up){
            return false;
        }
        else if(down < b.down){
            return true;
        } 
        else if(down > b.down){
            return false;
        }
        else{
            return true;
        }
    }
    //перегрузка оператора сравнения ==
    bool operator==(const bit_str& b){
        if((up == b.up) && (down == b.down)){
            return true;
        }
        else{
            return false;
        }
    }
    //вывод строки как 2 числа(ull и ui)
    void Print(){
        cout << "Up: "<< up << "\tDown: " << down << endl;
    }
    //побитовый вывод строки
    void Print_bit() {
        bitset<64> upB(up);
        bitset<32> downB(down);
        cout<<upB<<" | "<<downB<<endl; 
    }
    //подсчет количество единичных битов
     int count_1(){
        bitset<64> upB(up);
        bitset<32> downB(down);
        int res = upB.count() + downB.count();
        return res;
    } 
    //проверка включения через единичные биты
    bool check_inclusion(ull a){
        ull temp=a;
        bit_str str;
        str.up=up;
        str.down=down;
        if((str.down == 0 || str.up == 0) && temp == 0){
            return true;
        }
        for(int i = 0; i<32; ++i) {
            if(temp==0) {
                return true;
            }
            if((temp & 1) == (str.down & 1)) {
                temp=temp>>1;
                //(str.down)<<1;
            } else {
                temp=a;
                //(str.down)<<1;
            }
            str.down=(str.down)>>1;
        }

        while(str.up!=0) {
            if(temp==0) {
                return true;
            } else if((temp & 1) == (str.up & 1)) {
                temp=temp>>1;
                //(str.up)<<1;
            } else {
                temp=a;
                //(str.up)<<1;
            }
            (str.up)=(str.up)>>1;
        }

        return false;
    }

    private:
    ull up;   //unsigned long long старшая часть строки
    ui down;  //unsigned int младшая часть строки

};

int main() {
    ull up, num;
    ui down;
    cout<<"Enter strings a values"<<endl;
    cin >> up >> down;
    bit_str a(up, down),b;
    //ввод строк
    cout<<"Enter strings b values"<<endl;
    cin >> up >> down;
    b.Set(up, down);
    //вывод строки а
    cout<<"String a:"<< endl;
    a.Print();
    a.Print_bit();
    //вывод количества единичных битов в а
    cout<<"count_a: "<< a.count_1() <<endl;
    //вывод строки b
    cout<<"String b:"<< endl;
    b.Print();
    b.Print_bit();
    //проверка оперторов сравнения
    if(a > b){
        cout<<"a more then b"<<endl;
    }
    else if(a<b) {
        cout<<"a less then b"<<endl;
    }
    else if(a == b){
        cout << "a equal b" << endl;
    }
    //проверка включения числа num
    cout<<"Enter num"<<endl;
    cin >> num;
    if(a.check_inclusion(num)) {
        cout<<"There is inclusion"<<endl;
    }
    else {
        cout<<"There is no inclusion"<<endl;
    }
    //проверка операции &
    a=a&b;
    cout<<"a & b = ";
    a.Print_bit();
    //проверка операции |
    cout<<"a | b = ";
    b |= a;
    b.Print_bit();
    //проверка операции ~
    cout<<"~b = ";
    b=~b;
    b.Print_bit(); 

    //проверка сдвигов
    cout<<"Shift left on ... ";
    cin >> down;
    a<<=down;
    b=b<<down;
    a.Print_bit(); 
    b.Print_bit(); 
    cout<<"Shift right on ... ";
    cin >> down;
    a>>=down;
    b=b>>down;
    a.Print_bit(); 
    b.Print_bit();
    return 0;
}