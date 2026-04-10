/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:43 by taya              #+#    #+#             */
/*   Updated: 2026/04/10 12:08:44 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
  if (argc != 2){
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open()){
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  std::ifstream dataFile("data.csv");
  if (!dataFile.is_open()){
    std::cerr << "Error: could not open database." << std::endl;
    return 1;
  }
  std::map<std::string , float> database;
  fill_map(database, dataFile);
  calculator(database, inputFile);
  return 0;
}