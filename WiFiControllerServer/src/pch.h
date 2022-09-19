#pragma once

// basic console output and input
#include <iostream>

// winapi
// #include "Windows.h"

// winsocket in order to setup the server
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")

// standard
#include <functional>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <exception>
#include <future>
#include <mutex>
#include <queue>
#include <string>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iomanip>
#include <sstream>

// thread pool
#include <ctpl.h>
