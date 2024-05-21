#define	WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
int main()
{
	WSADATA wsaData; // структура для информации о версии сокетов
	ADDRINFO hints; // структура для подсказки функции getaddrinfo()
	ADDRINFO* addResult; // указатель на структуру
	SOCKET ConnectSocket = INVALID_SOCKET; // дескриптор сокета для подключения к серверу
	char recvBuffer[512]; // буфер для приема данных от сервера
	 
	const char* sendBuffer1 = "I HATE GENSHINIMPACT"; // сообщения для отправки на секвер
	const char* sendBuffer2 = "ZAUZAT KNOPKY PARALITIKA";


	int result = WSAStartup(MAKEWORD(2,2),&wsaData); // запрос версии 
	if (result != 0) {
		cout << "WSAStartup fauled result" << endl;
		WSACleanup();
		return 1; // выход с кодом ошибки
	}
	ZeroMemory(&hints, sizeof(hints)); // обнуление структуры
	hints.ai_family = AF_INET; // семейство адресов
	hints.ai_socktype = SOCK_STREAM; // тип сокета
	hints.ai_protocol = IPPROTO_TCP; // протокол TCP

	// Получение информации об адресе сервера
	result = getaddrinfo("localhost", "666", &hints, &addResult); // Запрос адреса на порту 666
	if (result != 0) {
		cout << "Getaddrinfo fauled result" << endl;
		WSACleanup();
		return 1; // выход с кодом ошибки
	}
	

	ConnectSocket = socket(addResult->ai_family, addResult->ai_socktype, addResult->ai_protocol); // cоздание сокета для подключения
	if (ConnectSocket == INVALID_SOCKET) {
		cout << "Socket creation with" << endl;
		WSACleanup();
		return 1;
	}
	result = connect(ConnectSocket, addResult->ai_addr, (int)addResult->ai_addrlen); // подключение к серверу
	if (result == SOCKET_ERROR) {
		cout << "Anable connect to server" << endl;
		closesocket(ConnectSocket); // закрытие сокета
		ConnectSocket = INVALID_SOCKET; // сброс дескриптора сокета
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	result = send(ConnectSocket, sendBuffer1, (int)strlen(sendBuffer1), 0); // отправка первого сообщения на сервер
	if (result == SOCKET_ERROR) {
		cout << "send failed error" << endl;
		closesocket(ConnectSocket);
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	cout << "sent: " << result << "bytes" << endl;

	result = send(ConnectSocket, sendBuffer2, (int)strlen(sendBuffer2), 0); // отправка второго сообщения на сервер
	if (result == SOCKET_ERROR) {
		cout << "send failed error" << endl;
		closesocket(ConnectSocket);
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	cout << "sent: " << result << "bytes" << endl;

	result = shutdown(ConnectSocket, SD_SEND); // закрытие сокета для отправки данных
	if (result == SOCKET_ERROR) {
		cout << "shutdown error" << endl;
		freeaddrinfo(addResult);
		WSACleanup();
		return 1;
	}
	do { // цикл получения ответов от сервера
		ZeroMemory(recvBuffer, 512); // обнуление буфера для приема
		result = recv(ConnectSocket, recvBuffer, 512, 0); // получение данных от сервера
		if (result > 0) {
			cout << "received" << result << "bytes" << endl;
			cout << "received data" << result << "bytes" << endl;
		}
		else if (result == 0) {
			cout << "connection closed" << endl; // сервер отключился
		}
		else {
			cout << "received failed" << endl;
		}
	} while (result > 0); // цикл продолжается, пока получаются данные
	freeaddrinfo(addResult);
	WSACleanup();
	return 0;
}
