// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

#pragma comment (lib, "ws2_32.lib")

const int BUFF_SIZE = 1024;

void send_message(SOCKET& socket, std::string s) {
	int packet_size = send(socket, s.c_str(), s.size(), 0);
	if (packet_size == SOCKET_ERROR) {
		std::cout << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
		closesocket(socket);
		WSACleanup();
		system("pause");
	}
}

void recv_message(SOCKET& client_socket) {

	int bytes = 0;
	std::vector <char> buffer(BUFF_SIZE);

	do {
		bytes = recv(client_socket, buffer.data(), buffer.size(), 0);

		if (bytes == SOCKET_ERROR) {
			std::cout << "Can't receive message from Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(client_socket);
			WSACleanup();
			system("pause");
		}
		else
			std::cout << "Server message: " << buffer.data() << std::endl;

		if (buffer.size() > 2 && buffer[0] == 'x' && buffer[1] == 'x' && buffer[2] == 'x') {
			shutdown(client_socket, SD_BOTH);
			closesocket(client_socket);
			WSACleanup();
			system("pause");
		}
	} while (bytes > 0);

}

void quick_close(SOCKET& sock) {
	closesocket(sock);
	WSACleanup();
}

#define EXPORT_METHOD extern "C" _declspec(dllexport)

EXPORT_METHOD
void Run(int port, std::string ip) {
		
	WSADATA wsData;

	int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) {
		//std::cout << "Error WinSock version initialization\n" << std::endl;
		//std::cout << WSAGetLastError() << std::endl;
		return;
	}
	else {
		//std::cout << "WinSock initialization is OK" << std::endl;
	}

	SOCKET client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == INVALID_SOCKET) {
		//std::cout << "Socket initialization error" << std::endl;
		quick_close(client_socket);
		return;
	}
	else {
		//std::cout << "Socket initialization success" << std::endl;
	}

	sockaddr_in  serv_info;
	ZeroMemory(&serv_info, sizeof(serv_info));

	in_addr ip_serv_sock;
	erStat = inet_pton(AF_INET, "127.0.0.1", &ip_serv_sock);
	if (erStat <= 0) {
		//std::cout << "Error in IP translation to specific format" << std::endl;
		quick_close(client_socket);
		return;
	}

	serv_info.sin_family = AF_INET;
	serv_info.sin_port = htons(1234);
	serv_info.sin_addr = ip_serv_sock;

	system("pause");

	erStat = connect(client_socket, (sockaddr*)&serv_info, sizeof(serv_info));
	if (erStat != 0) {
		//std::cout << "Connection to server is FAILED. " << WSAGetLastError() << std::endl;
		quick_close(client_socket);
		//system("pause");
		return;
	}
	else {
		std::cout << "Connected to server" << std::endl;
	}


	std::string send_buffer;
	short packet_size = 0;

	while(true) {

		//std::cout << i << std::endl;
		using namespace std::chrono_literals;

		//std::cout << "Your (Client) message to Server: ";
		std::getline(std::cin, send_buffer);

		std::thread recieve_(recv_message, std::ref(client_socket));
		//std::this_thread::sleep_for(50ms);
		std::thread send_(send_message, std::ref(client_socket), send_buffer);

		send_.detach();
		recieve_.detach();

		std::this_thread::sleep_for(100ms);
	}

	closesocket(client_socket);
	WSACleanup();
	//Run(port, ip);
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

