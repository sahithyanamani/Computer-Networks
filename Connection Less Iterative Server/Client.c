#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
int main()
{
  intsockfd,n,clilen,servlen;
  structsockaddr_incli_addr,serv_addr;
  charmsg[50],msg1[50];
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  
  if(sockfd<0)
  {
    printf("\n Sokcet Failed");
    exit(0);
  }
  
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr("192.168.2.58");
  serv_addr.sin_port=htons(3456);
  cli_addr.sin_family=AF_INET;
  cli_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  cli_addr.sin_port=htons(0);
  
  if(bind(sockfd,(structsockaddr*)&cli_addr,sizeof(cli_addr))<0)
  {
    printf("Client cantt bind");
    exit(1);
  }
  
  printf("Enter Strin");
  fgets(msg,50,stdin);
  
  if(sendto(sockfd,msg,50,0,(structsockaddr *)&serv_addr,sizeof(serv_addr))<0)
  {
    printf("Client send to error");
    exit(0);
  }
  
  servlen=sizeof(serv_addr);
  n=recvfrom(sockfd,msg1,50,0,(structsockaddr *)&serv_addr,&servlen);
  
  if(n<0)
  {
    printf("Recv error");
    exit(1);
  }
  else
  {
    printf("\n Client received msg : %s",msg1);
  }
  
  close(sockfd);
}
