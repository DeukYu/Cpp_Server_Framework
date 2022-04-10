#pragma once
#include "JobQueue.h"

class Room : public JobQueue
{
public:	// 싱글 쓰레드 환경인마냥 코딩
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);

private:
	USE_LOCK;
	map<uint64, PlayerRef>	_players;
};

extern shared_ptr<Room> GRoom;