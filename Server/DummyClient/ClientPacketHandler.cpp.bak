#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	default:
		break;
	}
}

#pragma pack(1)
// 패킷 설계 TEMP


struct PKT_S_TEST
{
	struct BuffListItem
	{
		uint64 bbuffId;
		float	remainTime;
	};
	uint16 packetSize;
	uint16 packetId;
	uint64 id;
	uint32 hp;
	uint16 attack;
	uint16 buffsOffset;
	uint16 buffsCount;

	bool Validate()
	{
		uint32	size = 0;
		if (packetSize < size)
			return false;

		size += sizeof(PKT_S_TEST);
		size += buffsCount * sizeof(BuffListItem);
		if (size != packetSize)
			return false;

		if (buffsOffset * buffsCount * sizeof(BuffListItem) > packetSize)
			return false;
		return true;
	}

	using BuffsList = PacketList<PKT_S_TEST::BuffListItem>;

	BuffsList GetBuffsList()
	{
		BYTE* data = reinterpret_cast<BYTE*>(this);
		data += buffsOffset;
		return BuffsList(reinterpret_cast<PKT_S_TEST::BuffListItem*>(data), buffsCount);
	}
};
#pragma pack()

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	if (len < sizeof(PKT_S_TEST))
		return;

	PKT_S_TEST* pkt = reinterpret_cast<PKT_S_TEST*>(buffer);

	//PKT_S_TEST	pkt;
	//br >> pkt;

	if (pkt->Validate() == false)
		return;

	//cout << "ID : " << id << "HP : " << hp << "ATT : " << attack << endl;

	PKT_S_TEST::BuffsList buffs = pkt->GetBuffsList();

	cout << "BufCount : " << buffs.Count() << endl;
	for (int32 i = 0; i < buffs.Count(); ++i)
	{
		cout << "BuffInfo : " << buffs[i].bbuffId << " " << buffs[i].remainTime << endl;
	}

	for (auto it = buffs.begin(); it != buffs.end(); ++it)
	{
		cout << "BuffInfo : " << it->bbuffId << " " << it->remainTime << endl;
	}
}
 