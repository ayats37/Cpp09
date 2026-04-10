/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:40 by taya              #+#    #+#             */
/*   Updated: 2026/04/10 12:18:17 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool isvalidate_date(const std::string &date){
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
// fill_map:
// 👉 just loads CSV into map
// read data.csv (infile)
// store in map<string, float>
std::map<std::string, float>& fill_map(std::map<std::string, float>& map, std::ifstream &infile){
  std::string line;
  std::getline(infile, line); // here we skip the header
  while (std::getline(infile, line))
  {
    std::stringstream ss(line);
    std::string date, value;
    if (!std::getline(ss, date, ',') || !std::getline(ss, value)) continue;
    map[date] = std::atof(value.c_str());
  }
  return map;
}
// Find the exchange rate for a given date
// If exact date doesn’t exist → use closest previous date
float get_rate(std::map<std::string, float> &map, const std::string &date){
  std::map<std::string, float>::iterator it = map.lower_bound(date);
  if (it != map.end() && it->first == date)
    return it->second;
  if (it == map.begin() && it->first != date)
    return -1;
  if (it == map.end() || it->first != date)
    --it;
  return it->second;
}
// read input.txt
// validate
// find rate
// print result

void  calculator(std::map<std::string, float>& map, std::ifstream &infile){
  std::string line;
  std::getline(infile, line);
  while(std::getline(infile, line))
  {
    std::stringstream ss(line);
    std::string date, valueStr;
    if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr)){
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }
    // if (!date.empty())
    //   date.erase(date.find_last_not_of(" ") + 1);

    // if (!valueStr.empty())
    //   valueStr.erase(0, valueStr.find_first_not_of(" "));

    // if (date.empty() || valueStr.empty()){
    //   std::cerr << "Error: bad input => " << line << std::endl;
    //   continue;
    // }
    // if (!isvalidate_date(date)){
    //   std::cerr << "Error: bad input => " << line << std::endl;
    //   continue;
    // }
    // float value = std::atof(valueStr.c_str());
    if (!date.empty())
    {
      size_t pos = date.find_last_not_of(" ");
      if (pos != std::string::npos)
        date.erase(pos + 1);
    }
    if (!valueStr.empty())
        valueStr.erase(0, valueStr.find_first_not_of(" "));

    if (date.empty() || valueStr.empty())
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        continue;
    }
    char *end;
    float value = std::strtof(valueStr.c_str(), &end);
    if (*end != '\0')
    {
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
    float rate = get_rate(map, date);
    if (rate < 0){
      std::cerr << "Error: no valid date." << std::endl;
      continue;
    }
    std::cout << date << " => " << value << " = " << value * rate << std::endl;
  }
}
