/*
	zzzclient.h

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

#ifndef __ZZZCLIENT_H__
#define __ZZZCLIENT_H__

#include <conio.h>	// getch
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#define socklen_t int
#else
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <netdb.h>
#include <stdint.h>
#include <fcntl.h>

#define closesocket close
#if !defined(O_BINARY)
#define O_BINARY 0
#endif
#endif

int zzzclient_init_socket();
void zzzclient_uninit_socket();
void zzzclient_init(int* sock);
void zzzclient_destroy(int* sock);
BOOL zzzclient_connect(int* sock, char* host, int port);
void zzzclient_close(int* sock);
BOOL zzzclient_send(int* sock, char* data);
char* zzzclient_receive(int* sock, char* result);
char* zzzclient_zzzprogram(char* host, int port, char* data, char* result);

#endif // __ZZZCLIENT_H__