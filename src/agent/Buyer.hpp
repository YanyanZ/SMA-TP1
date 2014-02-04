#ifndef BUYER_HPP
# define BUYER_HPP

# include <agent/Agent.hpp>

class Buyer : public Agent
{
public:
  Buyer(int i, std::string n, int t) : i (id), n (name), t (type){};
  virtual ~Buyer(){};

public:
  virtual int buy(Action a);
  virtual int sell(Action a);

public:
  virtual int talk(const int id, std::string message, const char* fmt, ...) = 0;
  virtual int talk(const name, std::string message, const char* fmt, ...) = 0;
  virtual int talk(const type, std::string message, const char* fmt, ...) = 0;

public:
  virtual friend std::ostream& operator<<(std::ostream& stream, const Agent a) = 0;
};
#endif
