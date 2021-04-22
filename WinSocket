//获取本机ip：cmd -> ipconfig -> IPv4 地址
//获取本机ip后获取可用端口： cmd -> netstat -ano  ->ip对应：后的，不要用0~1024
//accept会睡眠直到连接
//防火墙放行端口：https://blog.csdn.net/qq_26105397/article/details/82747401
//gethostbyname( 域名 );    

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<cstdio> //for printf
#include<winsock2.h>
#pragma comment(lib,"ws2_32")
#define PORT 2333
#define IP "xxx.xxx.xx.xx"  //use your ip
int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(IP);
	server_addr.sin_port = htons(PORT);
	//服务端,先听后发
	bind(sockfd, (SOCKADDR*)&server_addr, sizeof(SOCKADDR));
	listen(sockfd, 5);	//数据队列的长度，一般为0~20
	while (true)	//只能主动关闭服务器
	{
		SOCKADDR_IN client_addr;
		int csize = sizeof(SOCKADDR);
		SOCKET sockcl = accept(sockfd, (SOCKADDR*)&client_addr, &csize); //自动睡眠直到连接

		const char* msg = "Don't Stave Together";
		int msglen = lstrlenA(msg), sendlen = 0;
		while (sendlen < msglen)
		{
			int sn = send(sockcl, msg + sendlen, msglen - sendlen, 0);  //send返回实际发送的len
			if (sn > 0) { sendlen += sn; }
		}

		char cmsg[1024] = "";
		recv(sockcl, cmsg, sizeof(cmsg), 0);
		printf("接收到了客户端发来的消息：\n%s\n", cmsg);
		closesocket(sockcl);
	}
  
  /*
	//客户端，先发后听
	while ((connect(sockfd, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == -1)); //一直运行直到连上服务器
	const char* msg = "这里是客户端，你好服务端！！" 
	int msglen = lstrlenA(msg), sendlen = 0;
	while (sendlen < msglen)
	{
		int sn = send(sockfd, msg + sendlen, msglen - sendlen, 0);  //send返回实际发送的len
		if (sn > 0) { sendlen += sn; }
	}

	char buf[1024] = "";
	recv(sockfd, buf, sizeof(buf), 0);
	printf("接收到服务端的信息：\n%s\n", buf);
*/


	system("pause");
	closesocket(sockfd);
	WSACleanup();
	return 0;
}

