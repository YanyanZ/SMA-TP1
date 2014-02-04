#ifndef ACTION_HPP
# define ACTION_HPP

class Action
{
public:
  const int id;
  const std::string name;

public:
  int value_buy;
  int value_sell;

public:
  Action(std::string n);

public:
  friend bool operator==(const Action a1, const Action a2);
  friend bool operator!=(const Action a1, const Action a2);
  friend std::ostream& operator<<(std::ostream& stream, const Action a);
};

#endif
