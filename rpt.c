/*-
 * Copyright (c) 1998 James P. Howard, II <jh@jameshoward.us>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <err.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
			wait(&c);		/* reuse c */
			sleep(seconds);
		}
	return 0;
}

void help() {

	(void)fprintf(stderr, "\
usage: daemon [-cf] executable argv[1] ...\n");
	(void)exit(2);
}
