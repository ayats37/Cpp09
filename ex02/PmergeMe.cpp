#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(char **argv){
  fillContainers(argv);
}
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other){
  *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other){
  if (this != &other) {
    _vec = other._vec;
    _deq = other._deq;
  }
  return *this;
}

bool PmergeMe::isValidNumber(const std::string& s){
  if (s.empty()) return false;
  for (size_t i = 0; i < s.size(); i++)
  {
    if (!std::isdigit(s[i]))
      return false;
  }
  return true;
}

void PmergeMe::fillContainers(char **argv){
  for (size_t i = 1; argv[i]; i++){
    std::string s(argv[i]);
    if (!isValidNumber(s))
      throw std::runtime_error("Error");
    long val = std::atol(s.c_str());
    if (val < 0 || val > INT_MAX)
      throw std::runtime_error("Error");
    _vec.push_back(val);
    _deq.push_back(val);
  }
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr){
  if (arr.size() <= 1) return;
  std::vector<int> mainchain;
  std::vector<int> pending;
  //pair element
  size_t i = 0;
  for (; i + 1 < arr.size(); i+=2){
    if (arr[i] > arr[i + 1])
      std::swap(arr[i], arr[i + 1]);
    mainchain.push_back(arr[i + 1]);
    pending.push_back(arr[i]);
  }
  if (i < arr.size())
    mainchain.push_back(arr[i]);
  //recursive sort
  mergeInsertVector(mainchain);
  // insert pending using binary insert
  for (size_t j = 0; j < pending.size(); j++){
    std::vector<int>::iterator pos = std::lower_bound(mainchain.begin(), mainchain.end(), pending[j]);
    mainchain.insert(pos, pending[j]);
  }

  arr = mainchain;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr) {
  if (arr.size() <= 1) return;
  std::deque<int> mainChain;
  std::deque<int> pending;
  size_t i = 0;
  for (; i + 1 < arr.size(); i += 2) {
    if (arr[i] > arr[i + 1])
      std::swap(arr[i], arr[i + 1]);
    mainChain.push_back(arr[i + 1]);
    pending.push_back(arr[i]);
  }
  if (i < arr.size())
    mainChain.push_back(arr[i]);
  mergeInsertDeque(mainChain);
  for (size_t j = 0; j < pending.size(); j++) {
    std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pending[j]);
    mainChain.insert(pos, pending[j]);
  }
  arr = mainChain;
}

void PmergeMe::sortAndDisplay(){
  std::cout << "Before: ";
  for (size_t i = 0; i < _vec.size(); i++)
    std::cout << _vec[i] << " ";
  std::cout << std::endl;

  // VECTOR timing
  clock_t start = clock();
  mergeInsertVector(_vec);
  clock_t end = clock();
  double vecTime = (double)(end - start) * 1000000 / CLOCKS_PER_SEC;
  // Deque timing
  start = clock();
  mergeInsertDeque(_deq);
  end = clock();
  double deqTime = (double)(end - start) * 1000000 / CLOCKS_PER_SEC;

  std::cout << "After: ";
  for (size_t i = 0; i < _vec.size(); i++)
    std::cout << _vec[i] << " ";
  std::cout << std::endl;
  std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : "
      << vecTime << " us" << std::endl;

  std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : "
      << deqTime << " us" << std::endl;

}





