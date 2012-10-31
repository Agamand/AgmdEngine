#ifndef OPCODEMGR_H
#define OPCODEMGR_H

#include <AgmdUtilities\Utilities\Singleton.h>
#include <Packet\Packet.h>
#include <AgmdDefines.h>

namespace AgmdNetwork
{
	class Packet;

	template<class T>
	struct OpcodeHandler
	{
		const char* name;
		void (T::*handler)(Packet& data);
	};
	template<class T>
    class OpcodeMgr
	{

	public:

		void SetReader(OpcodeHandler<T>* reader);
		void RecvPacket(Packet& packet);

		static T& Instance()
		{
			if (!Inst)
				Inst = new T;

			return *Inst;
		}

		static void Destroy()
		{
			delete Inst;
			Inst = NULL;
		}

	protected:

		OpcodeMgr();
		~OpcodeMgr();

		OpcodeHandler<T>* m_recvOpcode;


	private :

		static T* Inst;
	
		
	};


	template<class T> T* OpcodeMgr<T>::Inst = NULL;

	template<class T> OpcodeMgr<T>::OpcodeMgr() :
	m_recvOpcode(NULL)
	{}

	template<class T> OpcodeMgr<T>::~OpcodeMgr()
	{};

	template<class T> void OpcodeMgr<T>::SetReader(OpcodeHandler<T>* reader)
	{
		m_recvOpcode = reader;
	}

	template<class T> void OpcodeMgr<T>::RecvPacket(Packet& packet)
	{
		if(!m_recvOpcode)
			return;
		((static_cast<T*>(this))->*m_recvOpcode[packet.GetOpcode()].handler)(packet);
	}
	
}




#endif //OPCODEMGR_H