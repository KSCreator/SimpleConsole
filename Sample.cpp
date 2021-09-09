#include <iostream>

int main(int argc, char **argv)
{
	std::cout << "argument count : " << argc << std::endl;
	for(int i = 0; i < argc; ++i)
		std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
}
