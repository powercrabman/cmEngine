#include <iostream>

struct Base {};
struct Child : Base {};

void sex(Base a)
{

}

int main()
{
	Child a = {};
	sex(a);
}