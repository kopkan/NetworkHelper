#pragma once
#include <iostream>
#include <boost/asio.hpp>

class Endpoint
{
public:
	Endpoint();
	Endpoint(std::string name, unsigned short port);
	Endpoint(const Endpoint& ep);
	void setEndpoint(std::string name, unsigned short port);
	std::string getName() const;
	std::string getStringIp() const;
	unsigned short getPort() const;
	void clear();
	Endpoint& operator=(Endpoint& v);
	boost::asio::ip::tcp::endpoint toBoostTcpEndpoint();
	boost::asio::ip::udp::endpoint toBoostUdpEndpoint();

private:
	std::string name_;
	unsigned short port_;

};