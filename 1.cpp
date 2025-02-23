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
    Human(int age, int height): age(age), height(height)
    {
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


class Student : public Human
{
protected:
    int group;
public:
    Student(): Human()
    {
        printf("Student() ");
        cout << this << " ";
        group = 1111;
        printf("%d %d %d\n", age, height, group);
    }
    Student(int age, int height, int group): Human(age, height)
    {
        this->group = group;
        printf("Student(int x, int y, int group)");
        cout << this << " ";
        printf("%d %d %d\n", age, height, group);
    }
    Student(const Student &other)
    {
        this->group = other.group;
        this->age = other.age;
        this->height = other.height;
        printf("Student(const Student &other) ");
        cout << this << " ";
        printf("%d %d %d\n", age, height, group);
    }
    ~Student()
    {
        printf("~Student()");
        cout << this << " ";
        printf("%d %d %d\n", age, height, group);
    }
    
};

int main()
{
    {
    Human a;
    Human b(15, 150);
    Human c(a);
    b.grow(1, 10);
    b.print();
    }
    cout << "=======================\n";

    {
    Human *d = new Human;
    Human *e = new Human(15, 150);
    Human *f = new Human(*d);

    delete d;
    delete e;
    delete f;
    
    }

    cout << "=======================\n";
    {
    Student g;
    Student h(16, 160, 355);
    Student i(g);

    Human *j = new Student(20, 200, 333);
    delete j;
    }
    

}