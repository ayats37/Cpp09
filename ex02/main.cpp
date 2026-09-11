#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		PmergeMe pmerge(argc, argv);
		pmerge.sort();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}