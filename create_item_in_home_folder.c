#include"Header.h"
int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	char* cError = NULL;
	char* cUserID = NULL;
	char* cPassword = NULL;
	char* cGroup = NULL;
	char* cItemID = NULL;
	char* cItemName = NULL;

	tag_t tItem = NULLTAG;
	tag_t tRev = NULLTAG;
	tag_t tUser = NULLTAG;
	tag_t tHomeFolder = NULLTAG;

	if (argc == 6)
	{

		cUserID = ITK_ask_cli_argument("-u=");
		cPassword = ITK_ask_cli_argument("-p=");
		cGroup = ITK_ask_cli_argument("-g=");
		cItemID = ITK_ask_cli_argument("-item_id=");
		cItemName = ITK_ask_cli_argument("-item_name=");

		iFail = ITK_init_module(cUserID, cPassword, cGroup);
		//iFail = ITK_init_module("infodba", "infodba", "dba");
		//iFail = ITK_auto_login();
		printf("\n\n Login success");
		Report_Error(iFail);
		
		iFail = ITEM_create_item(cItemID, cItemName, "Item", "", &tItem, &tRev);
		Report_Error(iFail);
		printf("\n Item Create Success");
		Report_Error(iFail);
		
		iFail = ITEM_save_item(tItem);
		printf("\n Item Saved in Database");
		Report_Error(iFail);
		
		iFail = SA_find_user2(cUserID, &tUser);
		printf("\n\n User find Success");
		Report_Error(iFail);

		# We have to find home folder tag for login user.
		iFail = SA_ask_user_home_folder(tUser, &tHomeFolder);
		printf("\n\n User Home folder find Success");
		Report_Error(iFail);
		
		iFail = FL_insert(tHomeFolder, tItem, 999);
		printf("\n\n Item inserted in User Home folder Success");
		Report_Error(iFail);
		
		# We have done changes in Home folder so he have to save it.
		iFail = AOM_save_without_extensions(tHomeFolder);
		printf("\n\n Item save in Home Folder Success");
		Report_Error(iFail);
		
		iFail = ITK_exit_module(TRUE);
		printf("\n\n Logout Success");
		Report_Error(iFail);
	}
		return 0;
}
