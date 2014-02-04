#ifndef MARKET_HPP
# define MARKET_HPP

# include <iostream>

class Market
{
public:
  const int id;
  const std::string name;

public:
  std::vector<std::vector<Company> > stocks;
  std::vector<Agent> controller;
};

#endif
