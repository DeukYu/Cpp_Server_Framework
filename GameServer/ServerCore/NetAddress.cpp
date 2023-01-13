#include "CorePch.h"
#include "NetAddress.h"

NetAddress::NetAddress(SOCKADDR_IN sockAddr) : _sockAddr(sockAddr)
{
}

NetAddress::NetAddress(wstring_view ip, uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr = Ip2Address(ip.data());
	_sockAddr.sin_port = ::htons(port);
}

wstring NetAddress::GetIpAddress()
{
	//::InetPtonW(AF_INET, &_sockAddr.sin_addr, buffer, len32(buffer));
	return wstring();
}

IN_ADDR NetAddress::Ip2Address(wstring_view ip)
{
	return IN_ADDR();
}
