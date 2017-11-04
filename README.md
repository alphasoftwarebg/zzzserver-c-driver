# zzzserver-c-driver
C driver for **ZZZ Base** through ZZZ Server

*zzzclient.h* - the header file with driver functions declarations
*zzzclient.c* - the file with driver functions implementations
*main.c* - sample access to **ZZZ Base** through function "zzzclient_zzzprogram"

{title="**sample usage**:",linenos=off,lang="c"}
~~~~~~~~
zzzclient_zzzprogram(
  "localhost",                            // **ZZZ Server** host
  3333,                                   // **ZZZ Server** port
  "#[cout;Hello World from ZZZServer!]",  // **ZZZ Base** sample program
  result);                                // result buffer of type char*
~~~~~~~~

Returned result encoded in utf-8
