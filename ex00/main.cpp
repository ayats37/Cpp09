/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:43 by taya              #+#    #+#             */
/*   Updated: 2026/04/12 14:54:20 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  try {
    BitcoinExchange btc("data.csv");
    btc.calculate(argv[1]);
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}