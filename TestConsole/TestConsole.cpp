#include <iostream>
#include <array>

int main()
{
	std::array<std::unique_ptr<char>, 10> m = {};

	if (m[0])
	{
		std::cout << "Yes" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}
}