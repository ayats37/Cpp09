/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:00:51 by taya              #+#    #+#             */
/*   Updated: 2026/04/12 13:25:48 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static size_t jacobsthal(size_t n){
  if (n == 0) return 0;
  if (n == 1) return 1;
  size_t a = 0, b = 1;
  for (size_t i = 2; i <= n; i++){
    size_t c = b + 2 * a;
    a = b;
    b = c;
  }
  return b;
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;

    std::vector<int> mainchain;
    std::vector<int> pending;

    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = hasStraggler ? arr.back() : 0;

    size_t i = 0;
    for (; i + 1 < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);

        mainchain.push_back(arr[i + 1]);
        pending.push_back(arr[i]);
    }
    if (hasStraggler)
        pending.push_back(straggler);
    mergeInsertVector(mainchain);
    std::vector<bool> inserted(pending.size(), false);
    size_t k = 1;
    while (true)
    {
      size_t start = jacobsthal(k);
      size_t end = jacobsthal(k + 1);

      if (start >= pending.size())
        break;
      if (end > pending.size())
        end = pending.size();
      for (size_t idx = end; idx > start; )
      {
        --idx;
        if (!inserted[idx])
        {
          std::vector<int>::iterator pos =
          std::lower_bound(mainchain.begin(), mainchain.end(), pending[idx]);
          mainchain.insert(pos, pending[idx]);
          inserted[idx] = true;
        }
      }
      k++;
    }
  for (size_t idx = 0; idx < pending.size(); idx++)
  {
    if (!inserted[idx])
    {
      std::vector<int>::iterator pos =
      std::lower_bound(mainchain.begin(), mainchain.end(), pending[idx]);
      mainchain.insert(pos, pending[idx]);
    }
  }
  arr = mainchain;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr)
{
  if (arr.size() <= 1)
    return;
  std::deque<int> mainChain;
  std::deque<int> pending;
  bool hasStraggler = (arr.size() % 2 != 0);
  int straggler = hasStraggler ? arr.back() : 0;

  size_t i = 0;
  for (; i + 1 < arr.size(); i += 2)
  {
    if (arr[i] > arr[i + 1])
    std::swap(arr[i], arr[i + 1]);
    mainChain.push_back(arr[i + 1]);
    pending.push_back(arr[i]);
  }
  if (hasStraggler)
    pending.push_back(straggler);
  mergeInsertDeque(mainChain);
  std::vector<bool> inserted(pending.size(), false);
  size_t k = 1;
  while (true)
  {
    size_t start = jacobsthal(k);
    size_t end = jacobsthal(k + 1);
    if (start >= pending.size())
      break;
    if (end > pending.size())
      end = pending.size();
    for (size_t idx = end; idx > start; )
    {
      --idx;
      if (!inserted[idx])
      {
        std::deque<int>::iterator pos =
        std::lower_bound(mainChain.begin(), mainChain.end(), pending[idx]);
        mainChain.insert(pos, pending[idx]);
        inserted[idx] = true;
            }
      }
      k++;
  }
  for (size_t idx = 0; idx < pending.size(); idx++)
  {
    if (!inserted[idx])
    {
      std::deque<int>::iterator pos =
      std::lower_bound(mainChain.begin(), mainChain.end(), pending[idx]);
      mainChain.insert(pos, pending[idx]);
    }
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





