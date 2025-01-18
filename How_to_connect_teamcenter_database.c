#include"Header.h"
int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	char* cError = NULL;
	iFail = ITK_init_module("infodba", "infdba", "dba");
	if (iFail == ITK_ok)
	{
		printf("\n\n Login success");
	}
	else
	{
		printf("Inter error code is %d", iFail);
		EMH_ask_error_text(iFail, &cError);
		printf("\n\n Error is : %s", &cError);

	}
	return 0;
}
