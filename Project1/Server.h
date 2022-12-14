#pragma once
#include <Windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <vector>
#include "Client.h"
#include "Authenticator.h"
#include "auth.pb.h"
#define DEFAULT_BUFLEN 512
#define TOTAL_ROOMS 5

#pragma comment(lib, "Ws2_32.lib")

// Server class
class Server {
public:
	Server();
	~Server();
	int Initialize();
	int Accept();
	int ReceiveAndSend();
private:
	int CreateSocket();
	int BindSocket();
	int Listen();
	int Broadcast(std::string , std::string , Client&, int );
	int GetRoomId(std::string);
	int AuthenticateUser(authenticator::AuthenticateWeb* auth);
	int AuthenticateUser(authenticator::CreateAccountWeb* auth);

	// tried creating a map, but using iterator for such simple thing seemed unnecessary
	//std::map < std::string, std::vector<Client>> Rooms;

	std::string Rooms[TOTAL_ROOMS] = {"general", "resources", "polls", "announcements", "off-topic"};
	std::string helpString = "";

	char recvbuf[DEFAULT_BUFLEN];
	std::vector<Client> clients;
	Client clientSocket;
	Authenticator authenticatorServer;
	int iResult, iSendResult, iSelectResult;
	int recvbuflen = DEFAULT_BUFLEN;
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	fd_set activeSockets;
	fd_set socketsReadyForReading;
};