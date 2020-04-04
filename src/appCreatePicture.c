#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "pictureFromText.h"

#define PATH_TO_FONT 			"fonts/cmunrm.ttf"

#define DEFAULT_WIDTH 			128
#define DEFAULT_HEIGHT			128
#define DEFAULT_FONT_SIZE		16
#define DEFAULT_NAME_FILE_OUT 	"fileout.png"

#define DEFAULT_MARGIN_LEFT		0
#define DEFAULT_MARGIN_TOP		0

/******************************************************************************/
/* Public variable definitions												  */
/******************************************************************************/

// To parse argv
// put ':' in the starting of the string so that program can distinguish between '?' and ':'
static char optString[] = ":w:h:l:m:f:t:s:u";

static struct option longOptions[] =
{
    {"width", required_argument, NULL, 'w'},
    {"height", required_argument, NULL, 'h'},
	{"margin-left", required_argument, NULL, 'l'},
	{"margin-top", required_argument, NULL, 'm'},
	{"filename", required_argument, NULL, 'f'},
	{"text", required_argument, NULL, 't'},
	{"size-font", required_argument, NULL, 's'},
	{"usage", no_argument, NULL, 'u'},
    {NULL, 0, NULL, 0}
};

/******************************************************************************/
/* Public functions                                                           */
/******************************************************************************/

void usage(int exitValue){
	fprintf(stdout, "\nUsage: appCreatePicture -t \"complete sentence\" -w WIDTH -h HEIGHT -s SIZE_FONT -f \"fileout.png\"\n");
	fprintf(stdout, "\t--text|-t : text to put on picture\n");
	fprintf(stdout, "\t--width|-w : width in pixels (default : %d)\n", DEFAULT_WIDTH);
	fprintf(stdout, "\t--height|-h : height in pixels (default : %d)\n", DEFAULT_HEIGHT);
	fprintf(stdout, "\t--margin-left|-l : margin-left in pixels (default : %d)\n", DEFAULT_MARGIN_LEFT);
	fprintf(stdout, "\t--margin-top|-m : margin-top in pixels (default : %d)\n", DEFAULT_MARGIN_TOP);
	fprintf(stdout, "\t--size-font|-s : size of font (default : %d)\n", DEFAULT_FONT_SIZE);
	fprintf(stdout, "\t--filename|-f : name of fileout (default : %s)\n", DEFAULT_NAME_FILE_OUT);
	fprintf(stdout, "\t--usage|-u : Display usage\n");
	
	fprintf(stdout, "\nNotes : Fonts supported are .ttf and .otf\n");

	exit(exitValue);
}  

int main(int argc, char *argv[])  
{ 
	int opt;

	// To create picture
	char *text = NULL;
	char *filename = NULL;

	char *font = PATH_TO_FONT;

	int width = DEFAULT_WIDTH;
	int height = DEFAULT_HEIGHT;
	int marginLeft = DEFAULT_MARGIN_LEFT;
	int marginTop = DEFAULT_MARGIN_TOP;
	int fontSize = DEFAULT_FONT_SIZE;

	while ( (opt=getopt_long(argc, argv, optString, longOptions, NULL)) != -1){
		
		switch(opt){
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 'l':
				marginLeft = atoi(optarg);
				break;
			case 'm':
				marginTop = atoi(optarg);
				break;
			case 's':
				fontSize = atoi(optarg);
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

	if(!font){
		fprintf(stderr, "Couldn't set specified font\n");
		usage(EXIT_FAILURE);
	}

	if(!filename){
		filename = DEFAULT_NAME_FILE_OUT;

		if(!filename){
			fprintf(stderr, "Failed to set out filename\n");
			exit(EXIT_FAILURE);
		}
	}

	createPictureFromText(text, filename, width, height, font, fontSize, marginLeft, marginTop);
    
	return 0; 
} 
