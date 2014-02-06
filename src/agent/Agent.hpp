#ifndef AGENT_HPP
# define AGENT_HPP

# define max_length 1024

class Agent
{
public:
  const std::string name;

public:
  Agent(std::string n) : name (n){};
  virtual ~Agent(){};

public:
  virtual void run() = 0;
};

#endif
