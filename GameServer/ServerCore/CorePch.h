#pragma once

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

#include <iostream>
#include <format>
#include <string_view>
#include <thread>


#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma	comment(lib, "ws2_32.lib")

using namespace std;

#include "NetAddress.h"