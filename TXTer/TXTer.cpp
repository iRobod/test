/* Reading text file by strings number */
#include <stdio.h>
#include<math.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

int *load (char name_file[]);	 // Read the file
void About(void);	             // App inf about
void printIt (char* format,...); // decode

int main(void)                   //void main ()
{
	About ();
	char name_file[50];		 // Mind name of the file
  printIt ("Enter a name of the file: ");
  scanf ("%s", name_file);
  int *p = load (name_file);	         // create Array of strings
  int m[250];  int j = 1;
  for (; p[j] != 0; m[j]=p[j], j++);	 // Copy & count a number of strings
	// Cout of nes.string
	for (;;)
  {
	 	int num;
    for (;;)
    {
			printIt ("Input num of string from 1 to %d (0 - Exit): ",j-1);
			scanf ("%d",&num);
      if (num >= 0 && num <= j-1) break;
		}
		if (num == 0) return 0;

		/* Open the file for loading strings. */
		FILE *fp;
		if ((fp = fopen(name_file, "r"))==NULL)
		{
			printIt("\a\nFile open error.\n");
			fclose(fp);
			exit (1);
		}
		char ch[3000], st[3000];
		fseek (fp, m[num], SEEK_SET);	// set CUR into the file. on nes.string
    fgets(ch, 3000, fp);	// Cin file string
    CharToOem (ch,st);	    // decode charset
    printIt ("\n%s\n", st);	// Cout the string
		fclose(fp);	// Close the file.
  }
	getchar(); // stub.
	return 0;
	/* App end. */
}

/* loading strings from file. */
int *load (char name_file[])
{
	int p[250];
  for (register int k = 0; k < 250; k++) p[k] = 0;
	/* Open the file. */
	FILE *fp;
	if ((fp = fopen(name_file, "r"))==NULL)
	{
		printIt("\a\n File open error.\n");
		fclose(fp);
		exit (1);
	}
	char ch[3000];
	int ex = 0;	    // EOF condition
	int num = 0;	// string num
	do {
		fgets(ch, 3000, fp);	  // Reading strings
		if (ch[0]=='\n') { num++;    p[num] = ftell(fp); }	// Remember string addr
		ex = feof(fp);		      // find EOF
    if (ex != 0) break;
	} while (ex == 0);
	fclose(fp);
  return p;
}

/* info cout */
void About (void)
{
	printIt("\		 Simple TXT Reader   v.1.1\n\n");
	printIt("Author: Vladislav Ushakov\n");
}

/* code for Win */
void printIt (char* format,...)
{
	char buf[100];
	va_list ptr;
	CharToOem(format,buf);
	va_start(ptr,format);
	vprintf(buf,ptr);
}
