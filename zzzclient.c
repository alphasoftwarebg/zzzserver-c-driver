/*
	zzzclient.c

	Copyright 2017 ZZZ Ltd. - Bulgaria

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
 */ 

#include "zzzclient.h"


int zzzclient_init_socket()
{
#ifdef WIN32
	WSADATA wsaData;
	if (
		WSAStartup(MAKEWORD(2, 2), &wsaData) &&
		WSAStartup(MAKEWORD(2, 1), &wsaData) &&
		WSAStartup(MAKEWORD(1, 1), &wsaData)
		)
	{
		return 0;
	}
#endif
	return 1;
}

void zzzclient_uninit_socket()
{
#ifdef WIN32
	WSACleanup();
#endif
}

void zzzclient_init(int* sock)
{
	*sock = -1;

	zzzclient_init_socket();
}

void zzzclient_destroy(int* sock)
{
	zzzclient_close(sock);

	zzzclient_uninit_socket();
}

/**
 * Connect to a host on a certain port number
 */
BOOL zzzclient_connect(int* sock, char* address , int port)
{
	struct sockaddr_in server;

	// create socket if it is not already created
	if(*sock == -1)
	{
		//Create socket
		*sock = (int)socket(AF_INET , SOCK_STREAM , 0);
		if (*sock == -1)
		{
			// Could not create socket
		}
		// Socket created
	}
	else { /* OK , nothing */ }

	// setup address structure
	if((int)inet_addr(address) == -1)
	{
		struct hostent *he;
		struct in_addr **addr_list;

		// resolve the hostname, its not an ip address
		if((he = gethostbyname(address)) == NULL)
		{
			// Failed to resolve hostname

			return FALSE;
		}

		// Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
		addr_list = (struct in_addr **) he->h_addr_list;

		server.sin_addr = *addr_list[0];
	}
	else // plain ip address
	{
		server.sin_addr.s_addr = inet_addr(address);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	// Connect to remote server
	if (connect(*sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		// Error: Connect failed.
		return 1;
	}

#ifndef _WIN32
	{
		int sockFlags;
		sockFlags = fcntl(sock, F_GETFL, 0);
		sockFlags |= O_NONBLOCK;
		fcntl(sock, F_SETFL, sockFlags);
	}
#endif

	// Connected
	return TRUE;
}

/**
 * Send data to the connected host
 */
BOOL zzzclient_send(int* sock, char* data)
{
	// Send some data
	if(send(*sock, data, (int)strlen(data)+1, 0) < 0)
	{
		// Send failed
		return FALSE;
	}
	// Data "data" send;

	return TRUE;
}

/**
 * Receive data from the connected host
 */
char* zzzclient_receive(int* sock, char* result)
{
	char buffer[512];
	int len = 0;
	int all=0;
	result[0] = '\0';

	if(result == NULL)
		return result;

	// Receive a reply from the server
	while((len = (int)recv(*sock , buffer , sizeof(buffer) , 0)) > 0)
	{
		buffer[len] = '\0';
		memcpy(&result[all], buffer, len);
		all += len;
	}

	return result;
}

void zzzclient_close(int* sock)
{
	if(sock >= 0)
	{
		closesocket(*sock);
		*sock = -1;
	}
}

char* zzzclient_zzzprogram(char* host, int port, char* data, char* result)
{
	int sock;

	if(result == NULL)
		return result;

	zzzclient_init(&sock);

	if(zzzclient_connect(&sock, host, port))
	{
		zzzclient_send(&sock, data);
		result = zzzclient_receive(&sock, result);
		zzzclient_close(&sock);
	}

	zzzclient_destroy(&sock);

	return result;
}
