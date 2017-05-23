
#include <xinu.h>
//#include <stdio.h>
#include "prodcons.h"
#include <string.h>
#include <stdlib.h>




shellcmd xsh_udp_request(int nargs, char *args[])
{

	int  port_no, retval,temp;
	pid32 fpid;
	int future_flag=0;
	future *f_exlusive;
	int value,status;
	uint32 serverip;	
	int local_port = 42000;
	int udp_slot;		
	
	char buffer[512];
	char msg[512];
	int msg_len,free_status;		

	if(nargs==4 && strcmp(args[3],"-f")==0)
	{
		future_flag = 1;
	}

	if(nargs > 4 || (nargs > 3 && strcmp(args[3],"-f")!=0 ))
	{
		printf("Too many arguments!\n");
		printf("Use --help to know about usage.\n");
		return -1;
	}	

	if(nargs==3 && strcmp(args[2],"-f")==0)
	{
		printf("\ntoo few arguments!\n");
		return -1;
	}

	if((nargs == 2) && strncmp(args[1],"--help",7)== 0)
	{
		
		printf("Description:\n");
		printf("\tCommunicate with server using UDP\n");
		printf("Options:\n");
		printf("\tServer IP\n");
		printf("\tPort no\n");		
		printf("\t-f Future mode \n");
		printf("\t--help\t Display help\n");
		return -1;
	}

	if(nargs < 3)
	{
		printf("Too few arguments.\n");
		printf("Use --help to know about usage.\n");
		return -1;
	}

	if (dot2ip(args[1], &serverip) == SYSERR) {
		printf( "%s: invalid IP address argument\r\n",
			args[0]);
		return 1;
	}
	produced1 = semcreate(1);
	
	port_no = atoi(args[2]);

	udp_slot = udp_register(serverip, port_no, local_port);		
	if (udp_slot == SYSERR) 	
	{
		printf(" Error while registering udp slot! %d ",local_port);
		return -1;
	}

	if (future_flag)	
	{
		f_exlusive = future_alloc(FUTURE_EXCLUSIVE);

		if (f_exlusive != NULL )
		{
			fpid = create(fcons_udp_print, 1024, 20, "fcons1", 1, f_exlusive);
			resume(fpid);
	
			while(1)
			{
				while(f_exlusive->state==FUTURE_VALID)
					printf("");

				printf("\n>");
				fgets(msg,512,CONSOLE);
				msg_len = strlen(msg);
				msg[msg_len-1]='\0';

				if(strcmp(msg,"exit") == 0) 
					break;
				retval = udp_send(udp_slot, msg, msg_len);
				if(retval == SYSERR)
				{
					printf(" Error in sending udp request!");
					return -1;
				}
	
				retval = udp_recv(udp_slot, buffer, sizeof(buffer),3000);
				if(retval == SYSERR)
				{ 	
					printf("Error in receiving response!");
					return -1;
				}
				if(retval == TIMEOUT)
				{
					printf("No response received within timeout!");
					return -1;
				}
				value = atoi(buffer);
				printf("\nProduced %d",value);
				status = future_set(f_exlusive, &value);
  				if (status < 1)
  				{
    					printf("future_set failed\n");
    					return -1;
 				}
				if(value==-1)
					break;
				memset(buffer,'\0',sizeof(buffer));
				memset(msg,'\0',sizeof(msg));
		
			}
		}
		udp_release(udp_slot);
		//while(count)
			//printf("");

		if(!(future_free(f_exlusive)))
			return SYSERR;

	
	}	
	else
	{	
		while(1)
		{
			printf("\n>");
			fgets(msg,512,CONSOLE);
			msg_len = strlen(msg);
			msg[msg_len-1]='\0';
			if(strcmp(msg,"exit") == 0) 
				break;

			retval = udp_send(udp_slot, msg, msg_len);
			if(retval == SYSERR)
			{
				printf(" Error in sending udp request!");
				return -1;
	
			}
	
			retval = udp_recv(udp_slot, buffer, sizeof(buffer),3000);
			if(retval == SYSERR)
			{ 	
				printf("Error in receiving response!");
				return -1;

			}

			if(retval == TIMEOUT)
			{
				printf("No response received within timeout!");
				return -1;
			}

			printf(buffer);
			memset(buffer,'\0',sizeof(buffer));
			memset(msg,'\0',sizeof(msg));
		}
		udp_release(udp_slot);
	}	
	return 0;

}