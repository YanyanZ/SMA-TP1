# include <iostream>
# include <thread>

# include <boost/thread.hpp>
# include <boost/bind.hpp>

# include <agent/Agent.hpp>
# include <agent/Dummy.hpp>

# include <threadpool.hpp>

int main(int argc, char* argv[])
{
  int nb_thread = 4; //boost::thread::hardware_concurrency();
  boost::threadpool::prio_pool worker_pool (nb_thread - 1);

  if (nb_thread <= 1)
  {
    std::cerr << "-> Error, not enough thread : " << nb_thread << std::endl;
    return -1;
  }

  std::cout << "> You have " << nb_thread << " threads" << std::endl;;
  std::cout << " > Will launch " << nb_thread - 1 << " agents" << std::endl;
  std::cout << std::endl;
  std::cout << "############################################" << std::endl;
  std::cout << "> Init simulation" << std::endl;
  std::cout << "> Create agents" << std::endl;
  for (int i = 0; i < nb_thread; i++)
  {
    Dummy agent = Dummy("Bob");
    worker_pool.schedule (boost::threadpool::prio_task_func (1, boost::bind(&Dummy::run, agent)));
    std::cout << " > Bob at work" << std::endl;
  }
  worker_pool.wait();

  std::cout << "> Launch web UI" << std::endl;
  system("firefox src/market/market_site/index.html");

  return 0;
}
