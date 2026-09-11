#pragma once


# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <cstdlib>
# include <climits>
# include <ctime>
# include <stdexcept>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(int argc, char **argv);
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void sort();

	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;

		static bool isNumber(const std::string &str);
		static int parseNumber(const std::string &str);

		static void mergeInsertVector(std::vector<int> &container);
		static void mergeInsertDeque(std::deque<int> &container);

		static void insertVector(std::vector<int> &container, int value);
		static void insertDeque(std::deque<int> &container, int value);

		static void printVector(const std::vector<int> &container);
};
