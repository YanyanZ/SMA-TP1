#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include <vector>

# include <boost/bind.hpp>
# include <boost/asio.hpp>
# include <boost/array.hpp>
# include <boost/noncopyable.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/enable_shared_from_this.hpp>

# include <market/server/Reply.hpp>
# include <market/server/Request.hpp>
# include <market/server/Request_handler.hpp>
# include <market/server/Request_parser.hpp>

namespace MarketServer
{
  class Connection: public boost::enable_shared_from_this<Connection>,
		    private boost::noncopyable
  {
  public:
    boost::asio::io_service::strand strand_;
    boost::asio::ip::tcp::socket socket_;
    Request_handler& request_handler_;
    boost::array<char, 8192> buffer_;
    Request request_;
    Request_parser request_parser_;
    Reply reply_;

  public:
    explicit Connection(boost::asio::io_service& io_service,
			Request_handler& handler);

  public:
    boost::asio::ip::tcp::socket& socket();
    void start();

  private:
    void handle_read(const boost::system::error_code& e,
		     std::size_t bytes_transferred);
    void handle_write(const boost::system::error_code& e);
  };

  typedef boost::shared_ptr<Connection> connection_ptr;
}

#endif
