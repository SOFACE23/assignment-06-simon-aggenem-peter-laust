//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

//Get the current date and time.
std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;

  //get the current time as a time_t object represented as unix epoch time
  time_t now = time(0);

  //Convert to readable format and return
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    //Allocate the socket with ipv4 and on port 13 commonly used for daytime services.
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      //Open socket
      tcp::socket socket(io_context);

      //accepts a new connection on the socket if it finds it.
      acceptor.accept(socket);

      //Read the time of day
      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;

      //Write to the socket. This is the data sent to the client.
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}