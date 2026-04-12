/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:00:48 by taya              #+#    #+#             */
/*   Updated: 2026/04/10 16:00:49 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv){
  if (argc < 2){
    std::cerr << "Error" << std::endl;
    return 1;
  }
  PmergeMe sorter(argv);
  sorter.sortAndDisplay();
  return 0;
}