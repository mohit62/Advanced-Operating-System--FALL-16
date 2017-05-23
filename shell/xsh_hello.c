#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - obtain and print the name with a message
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]){
	
	/* Checking argument count */
	if(nargs == 2){
	
		printf("Hello %s, Welcome to world of Xinu! \n", args[1]);
		return 0;	

	}
	else if(nargs < 2){

		fprintf(stderr, "Sorry! Too few arguments.\n");
		return 1;

	}
	else{
		
		fprintf(stderr, "Sorry! Too many arguments.\n");
		return 1;

	}	

}
