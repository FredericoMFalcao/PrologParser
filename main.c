#include <stdio.h>
#include <strings.h>

#define streq(a,b) (strcmp(a,b) == 0)

#define TRUE      1
#define FALSE     0
#define UNKNOWN  -1

#define OP_AND 1
#define OP_OR  2
#define OP_XOR 3
#define OP_NOT 4
#define OP_ASS 5

#define VARS_LENGTH 26

int vars[VARS_LENGTH];

char buffer[256];
char lastError[256];


#define MODE_ARG     1
#define MODE_PROOF   2
#define MODE_QUIT    3
int mode = 1;


int main() 
{

	int retVal, operation = 0;

	for(int i=0;i<VARS_LENGTH;i++) vars[i] = FALSE;

	while(mode != MODE_QUIT && printf("%c ",(mode == MODE_ARG?'%':'#')) && gets(buffer)) {
		retVal = -1; operation = 0;
		for(int i=0,l=strlen(buffer);i<l; i++) {
			if (0) {}
			/* parse literals */
			else if ( buffer[i] == '0' ) {
				if (operation == 0)      retVal  = 0;                    
				if (operation == OP_AND) retVal &= 0;                    
				if (operation == OP_OR ) retVal |= 0;                    
				if (operation == OP_XOR) retVal ^= 0;                    
			  	if (operation == OP_NOT) retVal =  1;
				if (operation == OP_ASS) { strcpy(lastError,"cannot assign to literal"); goto print_error; }
			}
			else if ( buffer[i] == '1' ) {
				if (operation == 0)      retVal  = 1;                    
				if (operation == OP_AND) retVal &= 1;                    
				if (operation == OP_OR ) retVal |= 1;                    
				if (operation == OP_XOR) retVal ^= 1;                    
			  	if (operation == OP_NOT) retVal =  0;                    
				if (operation == OP_ASS) { strcpy(lastError,"cannot assign to literal"); goto print_error; }
			}
			/* parse variables */
			else if ( buffer[i] >= 'A' && buffer[i] <= 'Z') {
				if (operation == 0) retVal = vars[buffer[i] - 'A'];
				if (operation == OP_AND) retVal &= vars[buffer[i] - 'A'];
				if (operation == OP_OR ) retVal |= vars[buffer[i] - 'A'];
				if (operation == OP_XOR) retVal ^= vars[buffer[i] - 'A'];
			  	if (operation == OP_NOT) retVal = !vars[buffer[i] - 'A'];
				if (operation == OP_ASS) vars[buffer[i] - 'A'] = retVal;
			}
			/* parse operations */
			else if ( buffer[i] == '&') operation = OP_AND;
			else if ( buffer[i] == '|') operation = OP_OR;
			else if ( buffer[i] == '+') operation = OP_XOR;
			else if ( buffer[i] == '!') operation = OP_NOT;
			else if ( buffer[i] == '=') operation = OP_ASS;
			/* parse mode change to proof (white space) */
			else if ( buffer[i] == ' ') mode = MODE_PROOF;
			else { strcpy(lastError,"syntax error!"); goto print_error;}
		}

		if (retVal > 0 ) printf("true");
		if (retVal ==0 ) printf("false");
		if (retVal < 0 ) printf("unknown");
		printf("\n");
		continue;
print_error:
		printf("ERROR: %s\n",lastError);
	}

	return 0;
}

