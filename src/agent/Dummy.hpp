#ifndef DUMMY_HPP
# define DUMMY_HPP

# include <cstdlib>
# include <cstring>
# include <iostream>

# include <boost/asio.hpp>

# include "Agent.hpp"

class Dummy : public Agent
{
public:
  Dummy(std::string name) : Agent(name){};
  virtual ~Dummy(){};

public:
  virtual void run();
};

#endif
