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

// ��Ŷ ���� TEMP
struct BuffData
{
	uint64 bbuffId;
	float	remainTime;
};

struct S_TEST
{
	uint64 id;
	uint32 hp;
	uint16 attack;

	vector<BuffData>	buffs;
};

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);
	PacketHeader header;
	br >> header;

	uint64 id;
	uint32 hp;
	uint16 attack;
	br >> id >> hp >> attack;

	cout << "ID : " << id << "HP : " << hp << "ATT : " << attack << endl;

	vector<BuffData> buffs;
	uint16 buffCount;
	br >> buffCount;

	buffs.resize(buffCount);
	for (int32 i = 0; i < buffCount; ++i)
	{
		br >> buffs[i].bbuffId >> buffs[i].remainTime;
	}

	cout << "BufCount : " << buffCount << endl;
	for (int32 i = 0; i < buffCount; ++i)
	{
		cout << "BuffInfo : " << buffs[i].bbuffId << " " << buffs[i].remainTime << endl;
	}
}
 