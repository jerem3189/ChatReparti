#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "Socket.hpp"	
#include <iostream>
#include <string>


Socket::Socket(){
	this->end = false;
}	

int Socket::Open(u_short port) {
	
	//char	c_opt_on	= 1;
	//u_long	l_opt_on	= 1;
	sockaddr_in	name;
	
	if((m_sock = socket(AF_INET, SOCK_DGRAM, 0)) == BAD_SOCKET)
		return (m_init = false, CUDP_SOCKET);

	//setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, &c_opt_on, sizeof(char));
	
	name.sin_family			= AF_INET;
	name.sin_port			= ntohs(port);
	name.sin_addr.s_addr	= INADDR_ANY;

	if(bind(m_sock, (sockaddr *)&name, sizeof(name)) == BAD_SOCKET)
		return (m_init = false, CUDP_BIND);

	m_init	= true;
	return CUDP_OK;
}


void Socket::Terminate(){
}

bool Socket::SetWritePort(u_short port)
{
	m_sWriteAddress.sin_port	= ntohs(port);

	return true;
}
/*bool	Socket::SetWriteAddress(const char * szAddress){
	}*/
/*bool	Socket::SetWriteAddress(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4){
}*/
bool Socket::SetSendBuffer(size_t len)
{
	int	nLen	= (int)len;

	setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, (const char*)&nLen, sizeof(int));

	return true;
}

bool Socket::SetRecvBuffer(size_t len)
{
	//int	nLen	= (int)len;

	//setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (const char*)&nLen, sizeof(int));

	return true;
}

int Socket::getPort(){
	return 1;
}
bool Socket::getAddressIp()
{
	 std::cout << inet_ntoa(m_sReadAddress.sin_addr); 
	 return true;
}

