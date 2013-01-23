#ifndef PACKET_H
#define PACKET_H

#include <Packet\ByteBuffer.h>

#define SIZE 2
#define SIZE_OPCODE 2

namespace AgmdNetwork
{

    struct ClientPacketHeader
    {
        uint16 size;
        uint16 opcode;
    };

    struct ServerPacketHeader
    {
        uint16 size;
        uint16 opcode;
    };


    class Packet : public ByteBuffer
    {
        public:

            Packet()                                       : ByteBuffer(0), m_opcode(0)
            {
            }

            explicit Packet(uint16 opcode, size_t res=200) : ByteBuffer(res), m_opcode(opcode) { }
                                                                // copy constructor
            Packet(const Packet &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode)
            {
            }

            void Initialize(uint16 opcode, size_t newres=200)
            {
                clear();
                _storage.reserve(newres);
                m_opcode = opcode;
            }

            uint16 GetOpcode() const { return m_opcode; }
            void SetOpcode(uint16 opcode) { m_opcode = opcode; }

        protected:
            uint16 m_opcode;
    };
}

#endif //PACKET_H