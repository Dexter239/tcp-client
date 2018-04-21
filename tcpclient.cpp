//CLIENT!!!!!
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
 #pragma comment (lib,"Ws2_32.lib")
#define PORT 22
#define SERVERADDR "31.31.196.224" 
int client()
{
	char buff[1000];
	printf("Tellnet CLIENT started\n");
	if (WSAStartup(0x202, (WSADATA *)&buff[0]))
	{
		printf("WSAStart error %d\n", WSAGetLastError());
		return -1;
	}
	SOCKET my_sock;
	my_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (my_sock < 0)
	{
		printf("Socket() error %d\n", WSAGetLastError());
		return -1;
	}
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	HOSTENT *hst;
	if (inet_addr(SERVERADDR) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
	{
		if (hst = gethostbyname(SERVERADDR))
			((unsigned long *)&dest_addr.sin_addr)[0] =
			((unsigned long **)hst->h_addr_list)[0][0];
		else
		{
			printf("Invalid address %s\n", SERVERADDR);
			closesocket(my_sock);
			WSACleanup();
			return -1;
		}
	}
	if (connect(my_sock, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		printf("Connect error %d\n", WSAGetLastError());
		_getch();
		return -1;
	}

	printf("Connecting with %s succesfuly\n ", SERVERADDR);

	


	char post[1000];
	while ((recv(my_sock, &buff[0], strlen(&buff[0]), 0)) != SOCKET_ERROR)
	{
			//printf("Server:");
			printf("%s", buff);
			printf("\n");
			scanf("%s", post);
			send(my_sock, &post[0], strlen(&post[0]), 0);
		
	}
	closesocket(my_sock);
}








int main(void)
{
client();
_getch ();
return 0;
}