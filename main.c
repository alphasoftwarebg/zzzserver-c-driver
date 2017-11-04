/*
	main.c : Defines the entry point for the console application.

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
#include <stdio.h>


int main(int argc, char* argv[])
{
	char ch;
	char result[1024] = "";

	zzzclient_zzzprogram("localhost", 3333, "#[cout;Hello World from ZZZServer!]", result);

	printf("%s\n", result);

	printf("%s", "Press any key...");


#ifdef _WIN32
	ch = _getch();
#else
	ch = getch();
#endif

	return 0;
}
