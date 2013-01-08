#ifndef SERVER_H 
#define SERVER_H 

#include <thread>
#include <WinSock2.h>
#include <vector>

namespace AgmdNetwork
{
    typedef std::vector<SOCKET> VSOCKET;

    class Packet;

    class Server
    {
        public:      
            struct thread_param{
                   Server* ser;
                   SOCKET soc;
            };  

            /*struct PacketHeader
            {
                uint32 size;
                uint16 opcode;
            };*/

            Server(int port);
            int Init();
            int Start();  
            int Pause();
            bool isStarted() {return isRunning;}
            void SendPacket(Packet& packet);
            virtual void RecvPacket(Packet& packet) = 0;

            void RemoveClient(SOCKET sock);
            static DWORD WINAPI ThreadLauncher(void *p)
            {
                thread_param *Obj = reinterpret_cast<thread_param*>(p);               
                Server *s = Obj->ser;                          
                return s->ClientThread(Obj->soc);       
            }
        private: 
            int           m_port;
            SOCKET          m_ListeningSocket;
            bool          isRunning;  
            SOCKADDR_IN   ServerAddr;   
            DWORD         ClientThread(SOCKET);
            VSOCKET          m_clientSocket;
    }; 
}



#endif //SERVER_H
