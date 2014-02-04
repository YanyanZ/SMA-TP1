#ifndef AGENT_HPP
# define AGENT_HPP

# include <iostream>
# include <cstdarg>

# include <state/State.hpp>
# include <wallet/Wallet.hpp>

class Agent
{
public:
  enum {BUYER, SELLER, PASSIF};

public:
  const int id;
  const std::string name;
  const int type;

private:
  State state;
  Wallet wallet;

public:
  Agent(int i, std::string n, int t) : i (id), n (name), t (type){};
  virtual ~Agent(){};

public:
  virtual int buy(Action a) = 0;
  virtual int sell(Action a) = 0;

public:
  virtual int talk(const int id, std::string message, const char* fmt, ...) = 0;
  virtual int talk(const name, std::string message, const char* fmt, ...) = 0;
  virtual int talk(const type, std::string message, const char* fmt, ...) = 0;

public:
  virtual friend std::ostream& operator<<(std::ostream& stream, const Agent a) = 0;
};

#endif
