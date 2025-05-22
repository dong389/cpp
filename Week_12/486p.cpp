#include <iostream>
using namespace std;
class Sample1{
public:
    Sample1(){}
    vide play() {cout << "1번 sample" << end1; }
};
class Sample2 : public Sample1{
public:
    Sample2(){}
    vide play() {cout << "2번 sample" << end1; }
};
class Sample3 : public Sample1{
public:
    Sample3(){}
    vide play() {cout << "3번 sample" << end1; }
};
class Sample4 : public Sample1{
public:
    Sample4(){}
    vide play() {cout << "4번 sample" << end1; }
};
vide main(){
    Sample1* arr[4];
    Sample1* a = new Sample1();
    Sample2* b = new Sample2();
    Sample3* c = new Sample3();
    Sample4* d = new Sample4();
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;
    for (int i = 0; i < 4; i++) arr[i]->play();
}