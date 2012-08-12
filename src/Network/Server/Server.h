#ifndef SERVER_H 
#define SERVER_H 

#include <winsock2.h>

namespace Network
{
	class Server;

	struct thread_param{
		   Server* ser;
		   SOCKET soc;
	};

	class Server
	{
		private: 
			int           m_port;
			SOCKET	      m_ListeningSocket;
			bool          isRunning;  
			SOCKADDR_IN   ServerAddr;   
			DWORD         ClientThread(SOCKET);  
		public:                                        
			Server(int port);
			int Init();
			int Start();  
			int Pause();
			static DWORD WINAPI ThreadLauncher(void *p)
			{
				thread_param *Obj = reinterpret_cast<thread_param*>(p);               
				Server *s = Obj->ser;                          
				return s->ClientThread(Obj->soc);       
			}
	}; 
}



#endif //SERVER_H
