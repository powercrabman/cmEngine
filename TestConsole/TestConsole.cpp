#include <iostream>

int main()
{
#if __cplusplus >= 201703L
	std::cout << "C++17 or later enabled!" << std::endl;
#else
	std::cout << "C++17 not enabled!" << std::endl;
#endif

    return 0;
}
