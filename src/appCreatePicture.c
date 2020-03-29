#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "pictureFromText.h"

#define DEFAULT_WIDTH 			128
#define DEFAULT_HEIGHT			128
#define DEFAULT_NAME_FILE_OUT 	"fileout.png"

void usage(int exitValue){
	fprintf(stdout, "\nUsage: appCreatePicture -t \"complete sentence\" -w WIDTH -h HEIGHT -f \"fileout.png\"\n");
	fprintf(stdout, "\t-t : text to put on picture\n");
	fprintf(stdout, "\t-w : width in pixels (default : %d)\n", DEFAULT_WIDTH);
	fprintf(stdout, "\t-h : height in pixels (default : %d)\n", DEFAULT_HEIGHT);
	fprintf(stdout, "\t-f : name of fileout (default : %s)\n", DEFAULT_NAME_FILE_OUT);
	fprintf(stdout, "\t-u : Display usage\n");
	
	exit(exitValue);
}  

int main(int argc, char *argv[])  
{ 
	// To parse argv
	// put ':' in the starting of the string so that program can distinguish between '?' and ':'
	int opt;
	char optString[] = ":w:h:f:t:u";

	// To create picture
	char *text = NULL;
	char *filename = NULL;

	int width = DEFAULT_WIDTH;
	int height = DEFAULT_HEIGHT;

	while ( (opt=getopt(argc, argv, optString)) != -1){
		
		switch(opt){
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 'f':
				filename = optarg;
				break;
			case 't':
				text = optarg;
				break;
			case 'u':
				usage(EXIT_SUCCESS);
				break;
			case ':':
				fprintf(stderr, "Option -%c needs a value\n", optopt);
				usage(EXIT_FAILURE);
				break;
			case '?':
				fprintf(stderr, "Unknown option : %c\n", optopt);
				usage(EXIT_FAILURE);
				break;
		}
	}
 
	if(!text){
		fprintf(stderr, "Couldn't set specified text\n");
		usage(EXIT_FAILURE);
	}

	if(!filename){
		filename = DEFAULT_NAME_FILE_OUT;

		if(!filename){
			fprintf(stderr, "Failed to set out filename\n");
			exit(EXIT_FAILURE);
		}
	}

	createPictureFromText(text, filename, width, height, "fonts/cmunrm.ttf", 16);
    
	return 0; 
} 
