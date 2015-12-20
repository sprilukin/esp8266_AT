/*
 * Esp8266_AT.h - library for Arduino to work with esp8266 wifi SoC wia AT commands
 * See README file in this directory for more documentation
 *
 * Author: Sergey Prilukin sprilukin@gmail.com
 */

#ifndef Esp8266AT_h
#define Esp8266AT_h

//wifi connection mode: AT+CWMODE=<mode>
//mode: 1 — STA, 2 — AP, 3 — BOTH
#define AT_WIFI_CONNECTION_MODE_STA "AT+CWMODE=1"
#define AT_WIFI_CONNECTION_MODE_AP "AT+CWMODE=2"
#define AT_WIFI_CONNECTION_MODE_BOTH "AT+CWMODE=3"

//wifi connect to AP command: AT+CWJAP="<ap name>","<password>"
#define AT_AP_CONNECT "AT+CWJAP="

//multiple connections mode AT+CIPMUX=<mode>
//mode: 0 - single connection, 1- multiple connection
#define SINGLE_CONNECTION_MODE "AT+CIPMUX=0"
#define MULTI_CONNECTION_MODE "AT+CIPMUX=1"

//tcp connection start: AT+CIPSTART="TCP","8.8.8.8",80
#define TCP_START_CONNECTION "AT+CIPSTART=\"TCP\""
//start sending message over tcp
#define TCP_SEND_MESSAGE "AT+CIPSEND="
//prompt message after which we can start sending our request
#define TCP_SEND_START_PROMPT ">"
//close tcp connection
#define TCP_CLOSE_CONNECTION "AT+CIPCLOSE"

//AT OK response
#define AT_RESPONSE_OK "OK"


//Some HTTP response codes
#define HTTP_200_OK "HTTP/1.1 200 OK"
#define HTTP_201_CREATED "HTTP/1.1 201 CREATED"

#include "Arduino.h"
#include <Stream.h>

//uncomment to enable output to debug serial
//#define ESP8266_DEBUG

class Esp8266AT {
public:

    /**
     * Constructor
     * stream - serial port connected to esp8266 chip
     * dbgStream - serial port for debug purposes
     */
    Esp8266AT(Stream *stream, Stream *dbgStream = NULL);
    boolean executeCommandAndWaitForResult(String command, String expectedResult);
    void executeCommandAndIgnoreResult(String command);
    boolean setup(String accessPoint, String password);

    //HTTP methods emulation
    boolean get(String ip, int port, String path);
    boolean post(String ip, int port, String path, String contentType, String payload, int expectedResponseCode);
private:
    Stream *_stream;
    Stream *_dbgStream;
    boolean _request(String ip, int port, String message, String expectedResponse);
    void _finishLastCommand();
};

#endif