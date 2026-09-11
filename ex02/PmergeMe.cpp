#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(int argc, char **argv)
{
	int	i;

	if (argc < 2)
		throw std::runtime_error("Error");

	i = 1;
	while (i < argc)
	{
		if (!isNumber(argv[i]))
			throw std::runtime_error("Error");

		this->_vec.push_back(parseNumber(argv[i]));
		this->_deq.push_back(parseNumber(argv[i]));
		i++;
	}
}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deq(other._deq)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::isNumber(const std::string &str)
{
	size_t i;

	if (str.empty())
		return (false);

	i = 0;
	while (i < str.size())
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}

	return (true);
}

int PmergeMe::parseNumber(const std::string &str)
{
	long	value;

	value = std::strtol(str.c_str(), NULL, 10);

	if (value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");

	return (static_cast<int>(value));
}

void PmergeMe::insertVector(std::vector<int> &container, int value)
{
	std::vector<int>::iterator it;

	it = container.begin();

	while (it != container.end() && *it < value)
		++it;

	container.insert(it, value);
}

void PmergeMe::insertDeque(std::deque<int> &container, int value)
{
	std::deque<int>::iterator it;

	it = container.begin();

	while (it != container.end() && *it < value)
		++it;

	container.insert(it, value);
}

void PmergeMe::mergeInsertVector(std::vector<int> &container)
{
	std::vector<int>	main;
	std::vector<int>	pending;
	int					odd;
	bool				hasOdd;
	size_t				i;

	if (container.size() <= 1)
		return;

	hasOdd = false;
	odd = 0;
	i = 0;

	while (i + 1 < container.size())
	{
		if (container[i] < container[i + 1])
		{
			main.push_back(container[i + 1]);
			pending.push_back(container[i]);
		}
		else
		{
			main.push_back(container[i]);
			pending.push_back(container[i + 1]);
		}
		i += 2;
	}

	if (i < container.size())
	{
		odd = container[i];
		hasOdd = true;
	}

	mergeInsertVector(main);

	insertVector(main, pending[0]);

	i = 1;
	while (i < pending.size())
	{
		insertVector(main, pending[i]);
		i++;
	}

	if (hasOdd)
		insertVector(main, odd);

	container = main;
}

void PmergeMe::mergeInsertDeque(std::deque<int> &container)
{
	std::deque<int>	main;
	std::deque<int>	pending;
	int				odd;
	bool			hasOdd;
	size_t			i;

	if (container.size() <= 1)
		return;

	hasOdd = false;
	odd = 0;
	i = 0;

	while (i + 1 < container.size())
	{
		if (container[i] < container[i + 1])
		{
			main.push_back(container[i + 1]);
			pending.push_back(container[i]);
		}
		else
		{
			main.push_back(container[i]);
			pending.push_back(container[i + 1]);
		}
		i += 2;
	}

	if (i < container.size())
	{
		odd = container[i];
		hasOdd = true;
	}

	mergeInsertDeque(main);

	insertDeque(main, pending[0]);

	i = 1;
	while (i < pending.size())
	{
		insertDeque(main, pending[i]);
		i++;
	}

	if (hasOdd)
		insertDeque(main, odd);

	container = main;
}

void PmergeMe::printVector(const std::vector<int> &container)
{
	std::vector<int>::const_iterator it;

	it = container.begin();
	while (it != container.end())
	{
		std::cout << *it;
		++it;

		if (it != container.end())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sort()
{
	clock_t	start;
	clock_t	end;
	double	vectorTime;
	double	dequeTime;

	std::cout << "Before: ";
	printVector(this->_vec);

	start = clock();
	mergeInsertVector(this->_vec);
	end = clock();

	vectorTime = static_cast<double>(end - start)
		/ CLOCKS_PER_SEC * 1000000.0;

	start = clock();
	mergeInsertDeque(this->_deq);
	end = clock();

	dequeTime = static_cast<double>(end - start)
		/ CLOCKS_PER_SEC * 1000000.0;

	std::cout << "After: ";
	printVector(this->_vec);

	std::cout << "Time to process a range of "
		<< this->_vec.size()
		<< " elements with std::vector : "
		<< vectorTime << " us" << std::endl;

	std::cout << "Time to process a range of "
		<< this->_deq.size()
		<< " elements with std::deque : "
		<< dequeTime << " us" << std::endl;
}