#pragma once

#include <boost\asio.hpp>
#include <memory>
#include <iostream>
#include <atomic>
#include "Buffer.h"
#include "Endpoint.h"

class Client
	: public std::enable_shared_from_this<Client>
{
public:
	Client(boost::asio::io_service& io);
	Client(boost::asio::ip::tcp::socket socket);
	~Client();
	time_t getlastMessageTime();
	void connect(Endpoint endpoint);
	void startRecive();
	int close();
	void onRecive(std::function<void(Buffer<char>)> recvFunc);
	void onClose(std::function<void()> closeFunc);
	void onConnect(std::function<void()> connectFunc);
	void send(Buffer<char> message);

private:
	void recive_();

	boost::asio::ip::tcp::socket socket_;
	std::atomic<time_t> lastRecvMessageTime_ = 0;
	Buffer<char> recvBuff_;

	std::function<void()> connectFunc_ = nullptr;
	std::function<void()> closeFunc_ = nullptr;
	std::function<void(Buffer<char>)> recvFunc_ = nullptr;
};

