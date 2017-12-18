#include "Functions.c"
#include "FuncFloat.c"
#include "SLE.c"
#include "canonic_2.c"
#define MAXLENGTH 100
int HELP()
{
	printf("\nexit -- to leave the programme;\nmatrix -- working with matrixes;\nhelp -- help;\nabout -- autors;\ncanonic -- canonic;\ncalc -- calculations;\nlong -- long numbers;\n");
	printf("sle -- solution of system of linear equations\nfunction -- some functions with float arguments\n");
	return 1;
}
int ABOUT()
{
	printf("*****\t\t\tAUTHORS\t\t\t*****\n");
	printf("*****\tPAVELLL\n*****\tMICHAEL\n*****\tORLOV\n");
	return 1;
}
int Bot(char* Command)
{
	if(Command[0] == 'e' && Command[1] == 'x' && Command[2] == 'i' && Command[3] == 't')
		return -1;
	if(Command[0] == 'm' && Command[1] == 'a' && Command[2] == 't' && Command[3] == 'r' && Command[4] == 'i' && Command[5] == 'x')
		return MATRIX();
	if(Command[0] == 'h' && Command[1] == 'e' && Command[2] == 'l' && Command[3] == 'p')
		return HELP();
	if(Command[0] == 'a' && Command[1] == 'b' && Command[2] == 'o' && Command[3] == 'u' && Command[4] == 't')
		return ABOUT();
	if(Command[0] == 'c' && Command[1] == 'a' && Command[2] == 'n' && Command[3] == 'o' && Command[4] == 'n' && Command[5] == 'i' && Command[6] == 'c')
		return CANONIC_2();
	if(Command[0] == 'c' && Command[1] == 'a' && Command[2] == 'l' && Command[3] == 'c')
		return CALC();
	if(Command[0] == 'l' && Command[1] == 'o' && Command[2] == 'n' && Command[3] == 'g')
		return LONG();
	if(Command[0] == 's' && Command[1] == 'l' && Command[2] == 'e')
		return SLE();
	if(Command[0] == 'f' && Command[1] == 'u' && Command[2] == 'n' && Command[3] == 'c' && Command[4] == 't' && Command[5] == 'i' && Command[6] == 'o' && Command[7] == 'n')
		return FUNCTION();
	return 0;
}
int main()
{
	int Prog = 1;
	printf("Hey. I'm the MathBot. Let's start: \n");
	while (Prog != -1)
	{
		char* WORD = (char *)malloc(MAXLENGTH * sizeof(char));
		printf("User>  ");
		scanf("%s", WORD);
		Prog = Bot(WORD);
		if(Prog == 0)
			printf("Unknown command\n");
		free(WORD);
		printf("\n");
	}
	return 0;
}
