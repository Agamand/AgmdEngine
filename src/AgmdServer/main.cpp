

#include <AgmdNetwork\Server\Server.h>
#include <AgmdNetwork\Opcode\OpcodeMgr.h>
#include <AgmdNetwork\Packet\Packet.h>

using namespace AgmdNetwork;
Server* server = NULL;
enum Opcode
{
    MSG_NULL_ACTION = 0x0,
    CMSG_SEND_MESSAGE = 0x1,
    SMSG_SEND_MESSAGE = 0x2
};




class OpServerMgr : public OpcodeMgr<OpServerMgr>
{

public:
    void BuildMessagePacket(std::string message, Packet& packet)
    {
        packet.SetOpcode(SMSG_SEND_MESSAGE);
        packet << message;
    }
    
    void HandleMessage(Packet& packet)
    {

    }

    void Handle_NULL(Packet& packet) {}
};

OpcodeHandler<OpServerMgr> _opcode[] = 
{
    {"MSG_NULL_ACTION",&OpServerMgr::Handle_NULL},
    {"CMSG_SEND_MESSAGE",&OpServerMgr::HandleMessage},
    {"SMSG_SEND_MESSAGE",&OpServerMgr::Handle_NULL},
};

class AgmdServer : public Server
{
public:
    AgmdServer(int port) :
    Server(port)
    {}

    virtual void RecvPacket(Packet& packet)
    {
        OpServerMgr::Instance().RecvPacket(packet);
    }
};

static DWORD WINAPI StartServer(void * p)
{
    AgmdServer* s = (AgmdServer*)p;
    s->Start();
    return 0;
}

int main(int argc, char** argv)
{
    server = new AgmdServer(4015);

    server->Init();

    OpServerMgr::Instance().SetReader(_opcode);
    HANDLE processThread = CreateThread(NULL, 0,&StartServer, server,0,NULL);
    
    
    
    while(1)
    {
        Packet message;
        OpServerMgr::Instance().BuildMessagePacket("lol\n",message);
        server->SendPacket(message);
        printf("Envoie message\n");
        Sleep(2000);
    }


    return 0;
}