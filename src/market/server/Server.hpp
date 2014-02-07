#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <iostream>
# include <utility>
# include <mutex>
# include <string.h>

# include <boost/lexical_cast.hpp>

std::vector<std::vector<std::pair<int, int> > >* stocks;
std::mutex mut;

int logmcpt;

std::ofstream logm;
std::ofstream logtc;
std::ofstream logti;
std::ofstream logmm;
std::ofstream logte;
std::ofstream logbi;

#endif
