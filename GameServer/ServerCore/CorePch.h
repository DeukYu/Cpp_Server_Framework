#pragma once

#include <iostream>
#include <format>
#include <string_view>

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma	comment(lib, "ws2_32.lib")

using namespace std;

#include "Types.h"
#include "NetAddress.h"