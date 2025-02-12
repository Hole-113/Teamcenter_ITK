#include"Header.h"
int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	char* cError = NULL;
	char* cUserID = NULL;
	char* cPassword = NULL;
	char* cGroup = NULL;

	if (argc == 4)
	{


		cUserID = ITK_ask_cli_argument("-u=");
		cPassword = ITK_ask_cli_argument("-p=");
		cGroup = ITK_ask_cli_argument("-g=");

		iFail = ITK_init_module(cUserID, cPassword, cGroup);
		//iFail = ITK_init_module("infodba", "infodba", "dba");
		//iFail = ITK_auto_login();

		if (iFail == ITK_ok)
		{
			printf("\n\n Login success");
			iFail = ITK_exit_module(TRUE);
			if (iFail == ITK_ok)
			{
				printf("\n\n Logout Success");
			}
			else
			{
				EMH_ask_error_text(iFail, &cError);
				printf("\n\n Error is : %s", cError);
			}

		}
		else
		{
			printf("Inter error code is %d", iFail);
			EMH_ask_error_text(iFail, &cError);
			printf("\n\n Error is : %s", cError);

		}
		if (cError)
		{
			MEM_free(cError);
		}
	}
	else
	{
		printf("\n Argument is more or less");
	}
	return 0;
}
		
	
