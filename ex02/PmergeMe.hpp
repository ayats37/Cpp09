#pragma once

#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <climits>
#include <algorithm>


class PmergeMe{

  private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    bool isValidNumber(const std::string& s);
    void fillContainers(char **argv);
    void mergeInsertVector(std::vector<int>& arr);
    void mergeInsertDeque(std::deque<int>& arr);

  public:
    PmergeMe();
    PmergeMe(char **argv);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortAndDisplay();

};
