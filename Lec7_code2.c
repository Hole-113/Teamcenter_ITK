// Assign no 8
// To generate a report of all properties of the Item Revision.
// In this we are printing Real name



#include"Header.h"
int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	int i = 0;
	char* cError = NULL;
	char* cUserID = NULL;
	char* cPassword = NULL;
	char* cGroup = NULL;
	char* cItemID = NULL;
	char** cProp_Name = NULL;
	char* cProp_value = NULL;
	int iProp_Count = 0;

	tag_t tItem = NULLTAG;
	tag_t tRev = NULLTAG;
	tag_t tHomeFolder = NULLTAG;
	tag_t tDatasetType = NULLTAG;
	tag_t tDataset = NULLTAG;
	tag_t tRelationType = NULLTAG;
	tag_t tRelation = NULLTAG;
	tag_t* tSecObjects = NULLTAG;

	if (argc == 5)
	{

		cUserID = ITK_ask_cli_argument("-u=");
		cPassword = ITK_ask_cli_argument("-p=");
		cGroup = ITK_ask_cli_argument("-g=");
		cItemID = ITK_ask_cli_argument("-item_id=");

		iFail = ITK_init_module(cUserID, cPassword, cGroup);
		//iFail = ITK_init_module("infodba", "infodba", "dba");
		//iFail = ITK_auto_login();
		printf("\n\n Login success");
		Report_Error(iFail);

		
		// Find Item tag
		iFail = ITEM_find_item(cItemID, &tItem);
		printf("\n\n Item tag find success");
		Report_Error(iFail);


		// Find Item latest revision tag
		iFail = ITEM_ask_latest_rev(tItem, &tRev);
		printf("\n\n Item Revision tag find success");
		Report_Error(iFail);



		// Find property name
		iFail = AOM_ask_prop_names(tRev, &iProp_Count, &cProp_Name);
		printf("\n\n Property names find success");
		Report_Error(iFail);


		// Find Property value and print them
		
		for (i = 0; i < iProp_Count; i++)
		{
			iFail = AOM_UIF_ask_value(tRev, cProp_Name[i], &cProp_value);
			printf("\n\n Property Nmae is %s ===> Property value is %s",cProp_Name[i],cProp_value);
			Report_Error(iFail);
		}

		iFail = ITK_exit_module(TRUE);
		printf("\n\n Logout Success");
		Report_Error(iFail);
	}
	else {
		printf("\n\n Argument count is less or more");
	}
	if (cProp_Name)
	{
		MEM_free(cProp_Name);
	}
	return 0;
}
