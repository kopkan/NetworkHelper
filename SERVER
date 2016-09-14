#include <thread>
#include <list>
#include <boost\thread.hpp>
#include "..\..\..\Common\Network\Network\Network.h"


using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;




template<typename T>
class List
{
public:
	void push(const T& val)
	{
		boost::lock_guard<boost::mutex> l(m_);
		list_.push_back(val);
	}

	void remove(const T& val)
	{
		boost::lock_guard<boost::mutex> l(m_);
		for (list<T>::iterator i = list_.begin(); i != list_.end(); ++i)
		{
			if (val == *i)
			{
				list_.erase(i);
				break;
			}
		}
	}

	void browse(function<bool(T)> func)
	{
		boost::lock_guard<boost::mutex> l(m_);
		for (list<T>::iterator i = list_.begin(); i != list_.end(); ++i)
		{
			if (func(*i))
			{
				auto old = i;
				i++;
				list_.erase(old);
				if (i == list_.end())
				{
					break;
				}
			}
		}
	}

	void erase_(typename list<T>::iterator iter)
	{
		list_.erase(iter);
	}

private:
	list<T> list_;
	boost::mutex m_;
};

List<weak_ptr<Client>> clientList;




void acceptFunc(tcp::socket socket)
{
	cout << "new client" << endl;
	shared_ptr<Client> client = make_shared<Client>(move(socket));

	weak_ptr<Client> weak_client = client;
	clientList.push(client);


	client->onClose([]()
	{
		cout << "close" << endl;
	});

	client->onRecive([weak_client](Buffer<char> buff)
	{
		cout << "recv" << endl;
		weak_client.lock()->send({"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 3\n\n123"});
		weak_client.lock()->close();
	});


	client->startRecive();
}




void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	shared_ptr<io_service> io = make_shared<io_service>();

	shared_ptr<Acceptor> acceptor = make_shared<Acceptor>(*io);
	acceptor->onAccept(acceptFunc);
	acceptor->listen({80});


	thread workThread([io]()
	{
		io->run();
	});



	bool cleanerThreadWork = true;
	thread cleanerThread([&cleanerThreadWork]()
	{
		while (cleanerThreadWork)
		{
			clientList.browse([](weak_ptr<Client> iter)->bool
			{
				shared_ptr<Client> cl = iter.lock();
				if (cl.use_count()==0)
				{
					return true;
				}

				if (clock() - cl->getlastMessageTime() > 10000)
				{
					cl->close();
				}
				return false;
			});
			Sleep(100);
		}


		clientList.browse([](weak_ptr<Client> iter)->bool
		{
			shared_ptr<Client> cl = iter.lock();
			if (cl.use_count() == 0)
			{
				return true;
			}

			cl->close();
			return false;
		});

	});

	PAUSE
	acceptor->close();

	cleanerThreadWork = false;
	cleanerThread.join();

	workThread.join();

	cout << "ALL CLOSE"<< endl;
	PAUSE

	system("pause");
}
