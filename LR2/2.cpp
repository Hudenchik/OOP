#include <iostream>

using namespace std;

class Human
{
protected:
    int age;
    int height;
public:
    Human()
    {
        age = 19;
        height = 160;
        printf("Human() ");
        cout << this << " ";
        printf("%d %d\n", age, height);
    }
    Human(int age, int height)
    {
        this->age = age;
        this->height = height;
        printf("Human(int age, int height) ");
        cout << this << " ";
        printf("%d %d\n", age, height);
    }
    Human(const Human &other)
    {
        this->age = other.age;
        this->height = other.height;
        printf("Human(const Human &other)");
        cout << this << " ";
        printf("%d %d\n", age, height);
    }

    ~Human()
    {
        printf("~Human() ");
        cout << this << " ";
        printf("%d %d\n", age, height);
    }
    void grow(int dx, int dy)
    {
        age = age + dx;
        height = height + dy;
        printf("move(int dx, int dy)\n");
    }
    void print();
    
};

void Human::print()
{
    printf("Print() ");
    printf("age: %d, height: %d\n", age, height);
}

class Duet
{
protected:
    Human *h1;
    Human *h2;
public:
    Duet()
    {
        h1 = new Human;
        h2 = new Human;
        printf("Duet() ");
        cout << this << endl;
    }
    Duet(const Duet &other)
    {
        this->h2 = new Human(*(other.h2));
        this->h1 = new Human(*(other.h1));
        printf("Duet(const Duet &other) ");
        cout << this << endl;
    }
    ~Duet()
    {
        delete h1;
        delete h2;
        printf("~Duet() ");
        cout << this << " ";
    }
};

class Duet2
{
protected:
    Human h3;
    Human h4;
public:
    Duet2()
    {
        printf("Duet2() ");
        cout << this << endl;
    }
    Duet2(const Duet2 &other):h3(other.h3), 
    {
        printf("Duet2(const Duet2 &other) ");
        h3 = other.h3;
        h4 = other.h4;
        cout << this << endl;
    }
    ~Duet2()
    {
        printf("~Duet2() ");
        cout << this <<endl;
    }
};
int main()
{
    Duet2 a;
    Duet2 b(a);
}