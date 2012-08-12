#include <winsock2.h>
#include <iostream>
#include <string>
#include <Server\Server.h>

#define _MAX_HOST_LENGTH_ 100

using namespace std;

namespace Network
{

	Server::Server(int port) : m_port(port), isRunning(false)
	{}

	int Server::Init()
	{
		in_addr address;
		hostent *host;
		char tempChar[_MAX_HOST_LENGTH_];
		std::string hostName;
		WSADATA	wsaData;

		if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 )
			return 1;

		if( gethostname(tempChar, _MAX_HOST_LENGTH_ ) == SOCKET_ERROR )
			return 1;
		hostName = tempChar;

		if( (host = gethostbyname( hostName.c_str() ) ) == NULL)
			return 1;

		memcpy( &address.s_addr, host->h_addr_list[0], sizeof( address.s_addr ) );

		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_port = htons( m_port );
		ServerAddr.sin_addr.s_addr = inet_addr( inet_ntoa( address ) );
		return 0;
	}

	int Server::Start (){
		SOCKADDR_IN                 ClientAddr;
		int                         ClientAddrLen;
		HANDLE                      hProcessThread;
		SOCKET                      NewConnection;
		struct thread_param         p;

		if( ( m_ListeningSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ) ) == INVALID_SOCKET ){
			WSACleanup();
			return 1;
		}

		if( bind( m_ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR ){
			closesocket( m_ListeningSocket );
			WSACleanup();
			return 1;
		}

		if( listen( m_ListeningSocket, 5 ) == SOCKET_ERROR ){
			closesocket( m_ListeningSocket );
			WSACleanup();
			return 1;
		}

		isRunning = true;
		ClientAddrLen = sizeof( ClientAddr );

		while(isRunning){

			if((NewConnection = accept( m_ListeningSocket, (SOCKADDR *) &ClientAddr, &ClientAddrLen)) == INVALID_SOCKET){
				closesocket( m_ListeningSocket );
				WSACleanup();
				return 1;
			}

			p.ser = this;
			p.soc = NewConnection;

			hProcessThread = CreateThread(NULL, 0,&Server::ThreadLauncher, &p,0,NULL);
		}

		return 0;
	}

	int Server::Pause (){
		isRunning = false;
		closesocket( m_ListeningSocket );
		return 0;
	}

	DWORD Server::ClientThread(SOCKET soc){

		return 0;
	}
}
