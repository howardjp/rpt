/*
 *  I saw a similar program on a BSD/OS 3.1 system.  Used it to exploit
 *  local security holes.
 */ 

#include <err.h> 
#include <stdio.h> 
#include <stdlib.h> 

static void help();

int main(int argc, char *argv[]) 
{
	int c, loops = -1, seconds = 2;

	if(argc < 2)
		help();
	while((c = getopt(argc, argv, "n:s:")) != EOF)
		switch(c) {
		case 'n':
			loops = strtol(optarg, (char **)NULL, 10);
			break;
		case 's':
			seconds = strtol(optarg, (char **)NULL, 10);
			break;
		default:
			help();
		}
	argc -= optind;
        argv += optind;  
	for(c = 0; c != loops; c++) 
		if(!fork()) {
			execvp(argv[0], &argv[0]);
			err(1, "%s", argv[0]);
		} else {
			wait();
			sleep(seconds);
		}
}

void help() {

	(void)fprintf(stderr, "\
usage: daemon [-cf] executable argv[1] ...\n");
	(void)exit(2);
}
