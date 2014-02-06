#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <iostream>
# include <utility>
# include <mutex>
# include <string.h>

# include <boost/lexical_cast.hpp>

std::vector<std::vector<std::pair<int, int> > > stocks;
std::vector<std::string> logAction;
std::mutex mut;

#endif
