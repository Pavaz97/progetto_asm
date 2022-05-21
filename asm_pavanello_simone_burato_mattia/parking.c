#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <unistd.h>

#include <stdint.h>

#include <sys/time.h>

/* Inserite eventuali extern modules qui */
extern void inizializza(char* bufferin,char* bufferout_asm);

/* ************************************* */
enum {
    MAXLINES = 200
};
enum {
    LIN_LEN = 5
};
enum {
    LOUT_LEN = 15
};

long long current_timestamp() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, & tp);
    /* te.tv_nsec nanoseconds divide by 1000 to get microseconds*/
    long long nanoseconds = tp.tv_sec * 1000LL + tp.tv_nsec; // caculate nanoseconds
    return nanoseconds;
}

int main(int argc, char * argv[]) {
    int i = 0;
    char bufferin[MAXLINES * LIN_LEN + 1];
    char line[1024];
    long long tic_c, toc_c, tic_asm, toc_asm;

    char bufferout_c[MAXLINES * LOUT_LEN + 1] = "";
    char bufferout_asm[MAXLINES * LOUT_LEN + 1] = "";

    FILE * inputFile = fopen(argv[1], "r");

    if (argc != 3) {
        fprintf(stderr, "Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    if (inputFile == 0) {
        fprintf(stderr, "failed to open the input file. Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    while (i < MAXLINES && fgets(line, sizeof(line), inputFile)) {
        i = i + 1;
        strcat(bufferin, line);
    }

    bufferin[MAXLINES * LIN_LEN] = '\0';

    fclose(inputFile);

    /* ELABORAZIONE in C */
    tic_c = current_timestamp();
    
    int j=0;
	int k=0;
	int	P_A=0;
	int P_B=0;
	int P_C=0;
	char flagA='0';
	char flagB='0';
	char flagC='0';
	int select=0;
	
	while(bufferin[k]!='I' && bufferin[k]!='O')
	{
		if(bufferin[k]=='A')
		{
			if(bufferin[k+2]>='0' && bufferin[k+2]<='9' )
				P_A=(bufferin[k+2]-'0')*10 +(bufferin[k+3]-'0');
			else 
				P_A=(bufferin[k+2]-'0');
		}
		if(P_A>31)
			P_A=31;
		if(bufferin[k]=='B')
		{
			if(bufferin[k+2]>='0' && bufferin[k+2]<='9' )
				P_B=(bufferin[k+2]-'0')*10 +(bufferin[k+3]-'0');
			else 
				P_B=(bufferin[k+2]-'0');
		}
		if(P_B>31)
			P_B=31;
		if(bufferin[k]=='C')
		{
			if(bufferin[k+2]>='0' && bufferin[k+2]<='9' && bufferin[k+3]>='0' && bufferin[k+3]<='9'  )
				P_C=(bufferin[k+2]-'0')*10 +(bufferin[k+3]-'0');
			else 
				P_C=(bufferin[k+2]-48);
		}
		if(P_C>24)
			P_C=24;
		k=k+1;
	}

	while(bufferin[k]!='\0')	
	{
	//printf("--%c--\n",bufferin[k]);
		if(bufferin[k]=='I' && bufferin[k+1]=='N' && bufferin[k+2]=='-')
		{
		select=1;
			if(bufferin[k+3]=='A' && P_A<31)	
			{
				flagA='0';
				P_A++;
				if(P_A>=31)
					flagA='1';
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;

			}
			else if(bufferin[k+3]=='A' && P_A>=31)	
			{
				
				flagA='1';
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+3]=='B' && P_B<31)	
			{
				flagB='0';
				P_B++;
				if(P_B>=31)
					flagB='1';	
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+3]=='B' && P_B>=31)	
			{
			
				flagB='1';
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+3]=='C' && P_C<24)	
			{
				flagC='0';
				P_C++;
				if(P_C>=34)
					flagC='1';
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+3]=='C' && P_C>=24)	
			{
				flagC='1';
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}else{
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
		
			
			
			}
		}
		else if(bufferin[k]=='O' && bufferin[k+1]=='U' && bufferin[k+2]=='T' && bufferin[k+3]=='-')
		{
		select=1;
			if(bufferin[k+4]=='A' && P_A>0)
			{
				P_A--;	
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+4]=='B' && P_B>0)
			{
				P_B--;	
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}
			else if(bufferin[k+4]=='C' && P_C>0)
			{
				P_C--;

				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='O';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
			}else{
							bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
		}
			
		}else if(bufferin[k]=='\n' && select==0){
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='C';
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_A/10)+48;
				j++;
				bufferout_c[j]=(P_A%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_B/10)+48;
				j++;
				bufferout_c[j]=(P_B%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=(P_C/10)+48;
				j++;
				bufferout_c[j]=(P_C%10)+48;
				j++;
				bufferout_c[j]='-';
				j++;
				bufferout_c[j]=flagA;
				j++;
				bufferout_c[j]=flagB;
				j++;
				bufferout_c[j]=flagC;
				j++;
				bufferout_c[j]='\n';
				j++;
		
		
		}else if(bufferin[k]=='\n' && select==1){
			select=0;
		}
			
				k++;
    }
	j++;
	bufferout_c[j]='\0';
	// printf("%s",bufferout_c);
    /* è possibile inserire qui il codice per l'elaborazione in C (non richiesto per l'elaborato) */
    /* questo pezzo di codice è solo una base di partenza per fare dei check sui dati */
    /*
    int c = 0;
    while ( bufferin[c] != '\0') {
      printf( "%c", bufferin[c] );
      strncat( bufferout_asm, &bufferin[c], 1);
      c = c + 1 ;
    }
    
*/
 
    
    toc_c = current_timestamp();

    long long c_time_in_nanos = toc_c - tic_c;

    /* FINE ELABORAZIONE C */

    /* INIZIO ELABORAZIONE ASM */
    

    
    tic_asm = current_timestamp();
    inizializza(bufferin,bufferout_asm);
    /* Assembly inline:
    Inserite qui il vostro blocco di codice assembly inline o richiamo a funzioni assembly.
    Il blocco di codice prende come input 'bufferin' e deve restituire una variabile stringa 'bufferout_asm' che verrÃ  poi salvata su file. */
    toc_asm = current_timestamp();

    long long asm_time_in_nanos = toc_asm - tic_asm;

    /* FINE ELABORAZIONE ASM */
    printf("C time elapsed: %lld ns\n", c_time_in_nanos);
    printf("ASM time elapsed: %lld ns\n", asm_time_in_nanos);
    /* Salvataggio dei risultati ASM */
    FILE * outputFile;
    outputFile = fopen(argv[2], "w");
    fprintf(outputFile, "%s", bufferout_asm);
    fclose(outputFile);
    return 0;
}
