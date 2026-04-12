/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:00:53 by taya              #+#    #+#             */
/*   Updated: 2026/04/10 16:00:54 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
