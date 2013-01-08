
#include <iostream>
#include <Client\Client.h>
#include <Packet\Packet.h>

#define _MAX_HOST_LENGTH_ 100
#define _MAX_SIZE 4096 // 4096 octet

using namespace std;


namespace AgmdNetwork
{

    Client::Client(string address, int port) :
    m_address(address),
    m_port(port), 
    isRunning(false)
    {}

    int Client::Init()
    {
        WSADATA    wsaData;
        if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 )
            return 1;

        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons( m_port );
        ServerAddr.sin_addr.S_un.S_addr = inet_addr(m_address.c_str());
        return 0;
    }

    int Client::Start (){
        HANDLE                      hProcessThread;
        thread_param         *p;

        if( ( m_ListeningSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET ){
            WSACleanup();
            return 1;
        }

        if( connect( m_ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR ){
            closesocket( m_ListeningSocket );
            WSACleanup();
            return 1;
        }
        p = new thread_param();
        p->clt = this;
        p->soc =  m_ListeningSocket;
        hProcessThread = CreateThread(NULL, 0,&Client::ThreadLauncher, p,0,NULL);

        return 0;
    }

    int Client::Pause (){
        isRunning = false;
        closesocket( m_ListeningSocket );
        return 0;
    }

    void Client::SendPacket(Packet& packet)
    {
        ByteBuffer buffer;
        buffer <<(uint8)0;
        buffer <<(uint8) packet.size();
        buffer << packet.GetOpcode();
        buffer <<(uint16)0;
        buffer.append(packet.contents(),packet.size());

        if(send(m_ListeningSocket,(const int8*)buffer.contents(),buffer.size(), 0) == SOCKET_ERROR)
            printf("SOCKET ERROR ! \n");
    }

    DWORD Client::ClientThread(){

        uint8 firstSizeByte;
        uint16 size = 0;
        uint16 opcode = 0;
        uint8 buffer[_MAX_SIZE];
        int32 error = 0;
        while((error = recv(m_ListeningSocket,(int8*)&firstSizeByte,sizeof(firstSizeByte),MSG_WAITALL)) == sizeof(firstSizeByte))
        {
            Packet packet;
            recv(m_ListeningSocket,(int8*)&size,sizeof(uint8),MSG_WAITALL);

            if(size < SIZE_OPCODE)
                continue;

            recv(m_ListeningSocket,(int8*)&opcode,SIZE_OPCODE,MSG_WAITALL);

            size -=SIZE_OPCODE;
            uint32 maxitr = size/_MAX_SIZE;
            
            for(uint32 i = 0; i < maxitr; i++)
            {
                recv(m_ListeningSocket,(int8*)buffer,_MAX_SIZE,MSG_WAITALL);
                packet.append(buffer, _MAX_SIZE);
            }

            recv(m_ListeningSocket,(int8*)buffer,size%_MAX_SIZE,MSG_WAITALL);
            packet.SetOpcode(opcode);
            packet.append(buffer, size%_MAX_SIZE);

            RecvPacket(packet);
        }
        return 0;
    }

    void Client::Reconnect()
    {
        if( ( m_ListeningSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET ){
            WSACleanup();
            return;
        }

        if( connect( m_ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof( ServerAddr ) ) == SOCKET_ERROR ){
            closesocket( m_ListeningSocket );
            WSACleanup();
            return;
        }

        //ClientThread(m_ListeningSocket);
    }
}