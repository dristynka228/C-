#define	WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
int main()
{
	WSADATA wsaData; // структура для информации о версии сокетах винды
	ADDRINFO hints; // структура для подсказки функции getaddrinfo()
	ADDRINFO* addResult; // сказатель на структуру и информации об адресе
	SOCKET ClientSocket = INVALID_SOCKET; // дескриптор сокета для прослушивания входящих подключений
	SOCKET ListenSocket = INVALID_SOCKET; // дескриптор сокета для общения с подключившимся клиентом

	const char* sendBuffer = "hello from server"; // текст, который сервер выводит пользователю

	char recvBuffer[512]; // буфер для приема данных от клиента

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData); // Запрос версии винды Sockets 2.2
	if (result != 0) {
		cout << "WSAStartup fauled result" << endl;
		return 1;  // выход с ошибочкой
	}

	ZeroMemory(&hints, sizeof(hints)); // обнуление структуры
	hints.ai_family = AF_INET; // семейство адресов
	hints.ai_socktype = SOCK_STREAM; // тип сокета
	hints.ai_protocol = IPPROTO_TCP; // протокол TCP
	hints.ai_flags = AI_PASSIVE; // автоматическое назначение адреса

	result = getaddrinfo(NULL, "666", &hints, &addResult); // запрос адреса на порту 666
	if (result != 0) {
		cout << "Getaddrinfo fauled with error" << endl;
		WSACleanup(); // очистка сокетов
		return 1;
	}

	ListenSocket = socket(addResult->ai_family, addResult->ai_socktype, addResult->ai_protocol); // создание сокета для прослушивания
	if (ListenSocket == INVALID_SOCKET) {
		cout << "Socket creation with" << endl;
		WSACleanup(); // очистка сокетов 
		return 1;
	}
	result = bind(ListenSocket, addResult->ai_addr, (int)addResult->ai_addrlen); // привязка сокета к адресу
	if (result == SOCKET_ERROR) {
		cout << "binding connect failed" << endl;
		closesocket(ListenSocket); // закрытие сокета
		ListenSocket = INVALID_SOCKET;
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	result = listen(ListenSocket, SOMAXCONN); // запуск прослушивания на сокете
	if (result == SOCKET_ERROR) {
		cout << "listening socket failed" << endl;
		closesocket(ListenSocket);
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	
	ClientSocket = accept(ListenSocket, NULL, NULL); // принятие входящего подключения
	if (ClientSocket == INVALID_SOCKET) {
		cout << "accepting socket failed" << endl;
		closesocket(ListenSocket);
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}

	closesocket(ListenSocket);  // закрытие сокета для прослушивания
	do { // цикл обработки подключений 
		ZeroMemory(recvBuffer, 512);
		result = recv(ClientSocket, recvBuffer, 512, 0); // получение данных от клиента
		if (result > 0) {
			cout << "Received " << result << "bytes" << endl;
			cout << "Received data " << recvBuffer << endl;


			result = send(ClientSocket, sendBuffer, (int)strlen(sendBuffer), 0); // отправка данных клиенту

			if (result == SOCKET_ERROR) {
				cout << "Failed to send data back" << endl;
				closesocket(ClientSocket);
				freeaddrinfo(addResult);
				WSACleanup();
			}
		}

		else if (result == 0)
			cout << "Connection closing..." << endl; // клиент отключился

		else
		{
			cout << "recv failed with error" << endl;
			closesocket(ClientSocket);
			freeaddrinfo(addResult);
			WSACleanup();
			return 1;
		}


	} while (result > 0); // цикл продолжается, пока получаются данные

	result = shutdown(ClientSocket, SD_SEND); // закрытие сокета для отправки данных
	if (result == SOCKET_ERROR) {
		closesocket(ClientSocket);
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket); // закрытие сокетов и очистка ресурсов
	freeaddrinfo(addResult);
	WSACleanup();
	return 0;
}

