#ifndef AGENT_HPP
# define AGENT_HPP

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <vector>
# include <fstream>
# include <algorithm>
# include <cmath>

# include <boost/asio.hpp>
# include <boost/lexical_cast.hpp>
# include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

enum {max_length = 1024};

class Agent
{
public:
  enum {HAPPY, SAD, CRAZY}; // STATE
  enum {STOCK, SELL, BUY, STANDBY, RANDOM};

public:
  const std::vector<std::string> cpy =
  {"TC", "TI", "MM", "TE", "BI"};

public:
  const std::string name;

protected:
  std::vector<int> actions_own;
  int wallet;

protected:
  int happy;
  int crazy;

protected:
  int status;
  int objectif;

public:
  Agent(std::string n, std::vector<int> start, int money);
  virtual ~Agent(void);

protected:
  int min(std::vector<int> v);
  int max(std::vector<int> v);

protected:
  int getCotation(std::string cn, tcp::socket* s);
  int getQuantity(std::string cn, tcp::socket* s);
  std::string sell(std::string cn, int quantity, tcp::socket* s);
  std::string buy(std::string cn, int quantity, tcp::socket* s);

public:
  virtual void run() = 0;
};

#endif
