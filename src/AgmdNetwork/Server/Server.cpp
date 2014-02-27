#include <iostream>
#include <string>
#include <Server\Server.h>
#include <Packet\Packet.h>

#define _MAX_HOST_LENGTH_ 100
#define _MAX_SIZE 4096 // 4096 octet

using namespace std;

namespace AgmdNetwork
{

    Server::Server(int port) :
    m_port(port), 
    isRunning(false)
    {}

    int Server::Init()
    {
        WSADATA    wsaData;

        if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 )
            return 1;


        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons( m_port );
        ServerAddr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");

        return 0;
    }

    int Server::Start (){
        SOCKADDR_IN                 ClientAddr;
        int                         ClientAddrLen;
        HANDLE                      hProcessThread;
        SOCKET                      NewConnection;
        struct thread_param         p;

        if( ( m_ListeningSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET ){
            WSACleanup();
            return 1;
        }

        /*if( bind( m_ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR ){
            closesocket( m_ListeningSocket );
            WSACleanup();
            return 1;
        }*/

        if( listen( m_ListeningSocket, 5 ) == SOCKET_ERROR ){
            closesocket( m_ListeningSocket );
            WSACleanup();
            return 1;
        }

        isRunning = true;
        ClientAddrLen = sizeof( ClientAddr );

        while(isRunning){

            if((NewConnection = accept( m_ListeningSocket, (SOCKADDR *) &ClientAddr, &ClientAddrLen)) == INVALID_SOCKET){
                printf("Connexion incorrect ! \n");
                closesocket( m_ListeningSocket );
                WSACleanup();
                return 1;
            }

            printf("Connexion reussi ! \n");
            p.ser = this;
            p.soc = NewConnection;

            m_clientSocket.push_back(NewConnection);

            hProcessThread = CreateThread(NULL, 0,&Server::ThreadLauncher, &p,0,NULL);
        }

        return 0;
    }

    int Server::Pause ()
    {
        isRunning = false;
        closesocket( m_ListeningSocket );
        return 0;
    }

    void Server::SendPacket(Packet& packet)
    {
        ByteBuffer buffer;
        buffer << (packet.size() + 2);
        buffer << packet.GetOpcode();
        buffer.append(packet.contents(),packet.size());
        printf("Send packet to %d clients\n",m_clientSocket.size());
        for(a_uint32 i = 0; i < m_clientSocket.size(); i++)
        {
            a_int32 error = 0;
            send(m_clientSocket[i],(a_int8*)buffer.contents(),buffer.size(), 0);
            if(error < 0)
                printf("Error on send packet to socket %d\n",m_clientSocket[i]);
            else printf("Send packet to socket %d\n",m_clientSocket[i]);
        }
    }

    void Server::RemoveClient(SOCKET sock)
    {
        for(a_uint32 i = 0; i < m_clientSocket.size(); i++)
        {
            if(m_clientSocket[i] == sock)
            {
                m_clientSocket.erase(m_clientSocket.begin()+i);
                break;
            }
        }
    }

    DWORD Server::ClientThread(SOCKET soc){

        a_uint32 size;
        a_uint16 opcode;
        Packet packet;
        a_uint8 buffer[_MAX_SIZE];
        while(recv(soc,(a_int8*)&size,sizeof(a_uint32),MSG_WAITALL) == sizeof(a_uint32))
        {
            
            if(size < SIZE_OPCODE)
                continue;

            recv(soc,(a_int8*)&opcode,SIZE_OPCODE,MSG_WAITALL);

            size -= SIZE_OPCODE;
            a_uint32 maxitr = size/_MAX_SIZE;

            for(a_uint32 i = 0; i < maxitr; i++)
            {
                recv(soc,(a_int8*)buffer,_MAX_SIZE,MSG_WAITALL);
                packet.append(buffer, _MAX_SIZE);
            }

            recv(soc,(a_int8*)buffer,size%_MAX_SIZE,MSG_WAITALL);
            packet.SetOpcode(opcode);
            packet.append(buffer, size%_MAX_SIZE);

            RecvPacket(packet);
        }

        printf("Close socket %d\n", socket);
        RemoveClient(soc);
        closesocket(soc);

        return 0;
    }
}
