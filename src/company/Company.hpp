#ifndef COMPANY_HPP
# define COMPANY_HPP

class Company
{
public:
  const int id;
  const std::string name;
  const int sector;

public:
  int nb_actions;
  int nb_actions_on_market;
  int nb_actions_sold;

public:
  std::vector<Action> actions;
};

#endif
