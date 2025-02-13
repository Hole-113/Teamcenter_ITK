// Assign 14
// To assign the project to the members
// In this code we are assigning only one user



#include"Header.h"

int ITK_user_main(int argc, char* argv[])
{
	 
	int iFail = 0;
	int iUserCount = 1;

	char* cProjectID = NULL;
	tag_t tProject_tag = NULLTAG;
	tag_t tUser = NULLTAG;

	cProjectID = ITK_ask_cli_argument("-project_id=");

	
	iFail = ITK_init_module("infodba", "infodba", "dba");
	printf("\n\n Login successful");
	Report_Error(iFail);

	iFail = SA_find_user2("AdminV", &tUser);
	printf("\n\n User tag find successful");

	iFail = PROJ_find(cProjectID, &tProject_tag);
	printf("\n\n Project tag find successful");
	Report_Error(iFail);
	
	iFail = PROJ_add_members(tProject_tag, iUserCount,&tUser);
	printf("\n\n User added successfully");
	Report_Error(iFail);

	iFail = ITK_exit_module(TRUE);
	printf("\n\n Logout Success");
	Report_Error(iFail);
	
	return 0;
}
