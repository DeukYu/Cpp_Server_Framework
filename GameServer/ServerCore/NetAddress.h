#pragma once

class NetAddress
{
public:
	NetAddress() = default;
	NetAddress(SOCKADDR_IN sockAddr);
	NetAddress(wstring_view ip, uint16 port);

	SOCKADDR_IN& GetSockAddr() { return _sockAddr; }
	wstring		 GetIpAddress();
	uint16		 GetPort() { return ntohs(_sockAddr.sin_port); }

public:
	static IN_ADDR Ip2Address(wstring_view ip);

private:
	SOCKADDR_IN _sockAddr = {};
};

