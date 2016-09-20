
#include <iostream>
#include <Client\Client.h>
#include <Packet\Packet.h>

#define _MAX_HOST_LENGTH_ 100
#define _MAX_SIZE 4096 // 4096 bytes

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
        buffer <<(a_uint16) packet.size();
        buffer << packet.GetOpcode();
        buffer.append(packet.contents(),packet.size());

        if(send(m_ListeningSocket,(const a_int8*)buffer.contents(),buffer.size(), 0) == SOCKET_ERROR)
            printf("SOCKET ERROR ! \n");
    }

    DWORD Client::ClientThread(){

        ServerPacketHeader _header;
        a_uint16 size = 0;
        a_uint16 opcode = 0;
        a_uint8 buffer[_MAX_SIZE];
        a_int32 error = 0;
        while((error = recv(m_ListeningSocket,(a_int8*)&_header,sizeof(ServerPacketHeader),MSG_WAITALL)) == sizeof(ServerPacketHeader))
        {
            Packet packet;
            recv(m_ListeningSocket,(a_int8*)&size,sizeof(a_uint8),MSG_WAITALL);

            if(size < SIZE_OPCODE)
                continue;

            recv(m_ListeningSocket,(a_int8*)&opcode,SIZE_OPCODE,MSG_WAITALL);

            size -=SIZE_OPCODE;
            a_uint32 maxitr = size/_MAX_SIZE;
            
            for(a_uint32 i = 0; i < maxitr; i++)
            {
                recv(m_ListeningSocket,(a_int8*)buffer,_MAX_SIZE,MSG_WAITALL);
                packet.append(buffer, _MAX_SIZE);
            }

            recv(m_ListeningSocket,(a_int8*)buffer,size%_MAX_SIZE,MSG_WAITALL);
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