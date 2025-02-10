// Assign 12
// To find the contents (childern's) of the folder

#include "Header.h"

int ITK_user_main(int argc, char* argv[])
{
	int i = 0;
	int iFail = 0;
	int iCount = 0;
	int iObjectCount = 0;

	char* cFolderName = NULL;
	char* cValue = NULL;

	tag_t* tSerachList = NULLTAG;
	tag_t tUser = NULLTAG;
	tag_t* tObjects = NULLTAG;
	WSO_search_criteria_t tCriteria;

	iFail = ITK_init_module("infodba", "infodba", "dba");
	printf("\n\n Login Successful");
	Report_Error(iFail);

	iFail = WSOM_clear_search_criteria(&tCriteria);
	printf("\n\n Clear Search criteria");
	Report_Error(iFail);

	iFail = SA_find_user2("infodba", &tUser);
	printf("\n\n User tag find success");
	Report_Error(iFail);

	tc_strcpy(tCriteria.class_name, "Folder");
	tc_strcpy(tCriteria.name, "storage");
	tCriteria.owner = tUser;

	iFail = WSOM_search(tCriteria, &iCount, &tSerachList);
	for (i = 0; i < iCount; i++)
	{
		WSOM_ask_name2(tSerachList[i], &cFolderName);
		printf("\n\n Name of Searched folder is %s", cFolderName);

		iFail = FL_ask_references(tSerachList[i], FL_fsc_by_name, &iObjectCount, &tObjects);
		Report_Error(iFail);

		for (int j = 0; j < iObjectCount; j++)
		{
			iFail = WSOM_ask_name2(tObjects[i], &cValue);
			printf("\n\n %d Child is  %s", j + 1, cValue);
		}
	}

	if (tSerachList)
	{
		MEM_free(tSerachList);
	}
	if (tObjects)
	{
		MEM_free(tObjects);
	}


	return 0;
}
