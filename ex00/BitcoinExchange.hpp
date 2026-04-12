/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:38 by taya              #+#    #+#             */
/*   Updated: 2026/04/12 14:58:42 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

class BitcoinExchange {
  private:
    std::map<std::string, float> _database;

    bool        isValidDate(const std::string& date) const;
    bool        isValidValue(const std::string& valueStr, float& value) const;
    float       getRate(const std::string& date) const;
    void        loadDatabase(const std::string& filename);

  public:
    BitcoinExchange();
    BitcoinExchange(const std::string& dbFile);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void calculate(const std::string& inputFile) const;
};
