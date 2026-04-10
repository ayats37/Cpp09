/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:08:38 by taya              #+#    #+#             */
/*   Updated: 2026/04/10 12:08:39 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>


bool isvalidate_date(const std::string &date);

std::map<std::string, float>& fill_map(std::map<std::string, float>& map, std::ifstream &infile);

float get_rate(std::map<std::string, float> &map, const std::string &date);

void calculator(std::map<std::string, float>& map, std::ifstream &infile);
