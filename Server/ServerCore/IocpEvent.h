#pragma once

class Session;

enum class EventType : uint8
{
	Connect,
	Accept,
	Recv,
	Send
};

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void			Init();
	EventType		GetType() { return eventType; }

public:
	EventType		eventType;
	IocpObjectRef	owner;
};

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() :IocpEvent(EventType::Connect) {}
};

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() :IocpEvent(EventType::Accept) {}

public:
	SessionRef session = nullptr;
};
class RecvEvent : public IocpEvent
{

public:
	RecvEvent() :IocpEvent(EventType::Recv) {}
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() :IocpEvent(EventType::Send) {}

	// temp
	vector<BYTE>	buffer;
};