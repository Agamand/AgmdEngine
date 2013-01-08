#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <WinSock2.h>

namespace AgmdNetwork
{
	class Packet;

	class Client
	{
		public:  
			struct thread_param{
				   Client* clt;
				   SOCKET soc;
			};

			Client(std::string address, int port);
			int Init();
			int Start();  
			int Pause();
			bool isStarted() {return isRunning;}
			void SendPacket(Packet& packet);
            void Reconnect();
			virtual void RecvPacket(Packet& packet) = 0;
			static DWORD WINAPI ThreadLauncher(void *p)
			{
				thread_param *Obj = reinterpret_cast<thread_param*>(p);               
				Client *s = Obj->clt;
				SOCKET socket = Obj->soc;
				delete p;                       
				return s->ClientThread();       
			}
    protected: 
			int           m_port;
			std::string   m_address;
			SOCKET	      m_ListeningSocket;
			bool          isRunning;  
			SOCKADDR_IN   ServerAddr;   
			DWORD         ClientThread();
			SOCKET        m_serverSocket;
	}; 
}



#endif //CLIENT_H