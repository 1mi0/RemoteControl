#include "pch.h"
#include "Application.h"
#include "sockets/Server.h"

Application::Application() {
  // Startup WinSock
  if (Server::setupWinSock() == SOCKET_ERROR) {
    std::cout << "Could not start up WinSock!";
    exit(1);
  }

  m_Server = std::unique_ptr<Server>(new Server);

  if (m_Server->bindDefault() == SOCKET_ERROR) {
    std::cout << "Could not bind hint to socket!" << std::endl;
    std::cout << "Error => " << WSAGetLastError() << std::endl;
    exit(1);
  }

  m_Buttons = std::unique_ptr<Buttons>(new Buttons);
  m_Pool = std::unique_ptr<ctpl::thread_pool>(new ctpl::thread_pool(1));
  m_PacketQueue = std::unique_ptr<std::queue<std::vector<byte>>>(
      new std::queue<std::vector<byte>>());
}

void Application::run() {
  m_Pool->push([this](int id) { receiveLoop(id); });

  while (true) {
    m_Mutex.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (!m_PacketQueue->empty()) {
      managePacket(m_PacketQueue->front());
      m_PacketQueue->pop();
    }
    m_Mutex.unlock();
  }
}

template <typename TInputIter>
std::string Application::makeHexString(TInputIter first, TInputIter last) {
  std::ostringstream ss;
  ss << std::hex << std::setfill('0');
  ss << std::uppercase;
  while (first != last) {
    ss << std::setw(2) << static_cast<int>(*first++) << " ";
  }
  ss << "\b\0";
  return ss.str();
}

void Application::receiveLoop(int id) {
  std::vector<byte> *packetReceived;
  SimplePacket *packet = new SimplePacket;
  while (true) {
    packetReceived = m_Server->receivePacket();
    if (packetReceived != nullptr) {
      std::string str =
          makeHexString(std::begin(*packetReceived), std::end(*packetReceived));
      m_Mutex.lock();
      std::cout << "Packet => \"" << str << "\"" << std::endl;
      m_PacketQueue->push(*packetReceived);
      m_Mutex.unlock();
    }
  }

  delete packetReceived;
}

void Application::managePacket(std::vector<byte> packetReceived) {
  SimplePacket *packet = new SimplePacket;
  if (packetReceived.empty()) {
    std::cout << "Error => " << WSAGetLastError() << std::endl;
    return;
  }

  packet->translatePacket(packetReceived);
  switch (packet->getAction()) {
  case Action::ClickButton:

    byte button = packet->getParam(0);
    std::string *szButton = m_Buttons->stringifyButton(button);
    std::cout << "Button received: " << *szButton << std::endl;
    m_Buttons->ExecuteButton(button);

    packet->addParam(0x01);
    packet->constructPacket();
    if (!m_Server->respond((char *)(packet->getPacket().data()))) {
      std::cout << "ERROR => " << WSAGetLastError() << std::endl;
    }

    delete szButton;
    break;
  }
}
