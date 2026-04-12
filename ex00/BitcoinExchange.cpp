/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:40 by taya              #+#    #+#             */
/*   Updated: 2026/04/12 14:56:12 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile) {
  loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
  *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  if (this != &other)
    _database = other._database;
  return *this;
}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename){
  std::ifstream infile(filename.c_str());
    if (!infile.is_open())
        throw std::runtime_error("Error: could not open database.");
    std::string line;
    std::getline(infile, line);
    while (std::getline(infile, line)) {
      std::stringstream ss(line);
      std::string date, value;
      if (!std::getline(ss, date, ',') || !std::getline(ss, value)) continue;
      _database[date] = std::atof(value.c_str());
    }
}
bool BitcoinExchange::isValidDate(const std::string &date) const {
  if(date.length() != 10 || date[4] != '-' || date[7] != '-') return false;

  for (size_t i = 0; i < date.length(); i++){
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i]))
      return false;}
      
  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());

  if (month < 1 || month > 12 || day < 1) return false;
  if (month == 4 || month == 6 || month == 9 || month == 11) return (day <= 30);
  if (month == 2){
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    return (day <= (leap ? 29 : 28));
  }
  return (day <= 31);
}
bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const {
  char* end;
  value = std::strtof(valueStr.c_str(), &end);
  return (*end == '\0');
}

float BitcoinExchange::getRate(const std::string& date) const{
  std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
  if (it != _database.end() && it->first == date)
    return it->second;
  if (it == _database.begin())
    return -1;
  --it;
  return it->second;
}

void BitcoinExchange::calculate(const std::string& inputFile) const{
  std::ifstream infile(inputFile.c_str());
    if (!infile.is_open())
      throw std::runtime_error("Error: could not open file.");
    std::string line;
    std::getline(infile, line); // skip header
    while (std::getline(infile, line)) {
      std::stringstream ss(line);
      std::string date, valueStr;
      if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        continue;
    }
    size_t pos = date.find_last_not_of(" ");
    if (pos != std::string::npos) date.erase(pos + 1);
    valueStr.erase(0, valueStr.find_first_not_of(" "));

    if (date.empty() || valueStr.empty() || !isValidDate(date))
    {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }
    float value;
    if (!isValidValue(valueStr, value)) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }
    if (value < 0){
      std::cerr << "Error: not a positive number." << std::endl;
      continue;
    }
    if (value > 1000){
      std::cerr << "Error: too large a number." << std::endl;
      continue;
    }
    float rate = getRate(date);
    if (rate < 0){
      std::cerr << "Error: no valid date." << std::endl;
      continue;
    }
    std::cout << date << " => " << value << " = " << value * rate << std::endl;
  }
}
