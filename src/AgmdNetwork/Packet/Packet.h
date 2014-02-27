#ifndef PACKET_H
#define PACKET_H

#include <Packet\ByteBuffer.h>

#define SIZE 2
#define SIZE_OPCODE 2

namespace AgmdNetwork
{

    struct ClientPacketHeader
    {
        a_uint16 size;
        a_uint16 opcode;
    };

    struct ServerPacketHeader
    {
        a_uint16 size;
        a_uint16 opcode;
    };


    class Packet : public ByteBuffer
    {
        public:

            Packet()                                       : ByteBuffer(0), m_opcode(0)
            {
            }

            explicit Packet(a_uint16 opcode, size_t res=200) : ByteBuffer(res), m_opcode(opcode) { }
                                                                // copy constructor
            Packet(const Packet &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode)
            {
            }

            void Initialize(a_uint16 opcode, size_t newres=200)
            {
                clear();
                _storage.reserve(newres);
                m_opcode = opcode;
            }

            a_uint16 GetOpcode() const { return m_opcode; }
            void SetOpcode(a_uint16 opcode) { m_opcode = opcode; }

        protected:
            a_uint16 m_opcode;
    };
}

#endif //PACKET_H