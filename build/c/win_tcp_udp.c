#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <stdlib.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#include "win_tcp_udp.h"

int send_http_post(unsigned char *senddata){
    char destination[] = RSERVER;
    unsigned short port = 80;
    unsigned char httppath[20] = "/upload";
    char httphost[] = LSERVER;
    int dstSocket;
    int result;
 
    char toSendText[MAXBUF];
    char postdata[MAXBUF];
    int read_size;

    // WSADATAの初期化
    WSADATA data;
    WSAStartup(MAKEWORD(2, 0), &data);

    // AF_INETを設定
    struct sockaddr_in dstAddr;
    memset(&dstAddr, 0, sizeof(dstAddr));
    dstAddr.sin_port = htons(port);
    dstAddr.sin_family = AF_INET;
    dstAddr.sin_addr.s_addr = inet_addr(destination);
 
    // Socket通信の開始
    printf("\t==>Creating socket...\n");
    dstSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (dstSocket < 0){
        printf("\t==>Creating socket failed!!\n");
        return 0;
    }
    printf("\t==>Creating socket succeeded!!\n");
 
    // 通信の開始
    printf("\t==>Connecting...\n");
    result = connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));
    if (result < 0){
        printf("\t==>Binding failed!!\n");
        return 0;
    }
    printf("\t==>Connecting succeeded!!\n");
 
    // HTTPリクエストの作成
    printf("\t==>Creating HTTP request...\n");
    sprintf(toSendText, "POST %s HTTP/1.1\r\n", httppath);
    send(dstSocket, toSendText, strlen(toSendText) , 0);
 
    sprintf(toSendText, "Host: %s:%d\r\n", httphost, port);
    send(dstSocket, toSendText, strlen(toSendText), 0);

    sprintf(postdata, "%s\r\n", senddata);
    sprintf(toSendText, "Content-Length: %d\r\n", strlen(postdata));
    send(dstSocket, toSendText, strlen(toSendText), 0);
         
    sprintf(toSendText, "\r\n");
    send(dstSocket, toSendText, strlen(toSendText), 0);

    // HTTPリクエストの送信
    printf("\t==>Sending HTTP request...\n");
    send(dstSocket, postdata, strlen(postdata), 0);
  
    // 通信のクローズ
    printf("\t==>HTTP request is sent!!\n");
    closesocket(dstSocket);
    WSACleanup();

    return 0;
}

int main()
{
    printf("Data to send...\n");
    int result = send_http_post("data=test");
    printf("Closing...\n");
    return 0;
}