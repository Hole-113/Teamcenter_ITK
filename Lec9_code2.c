// Assign 11
// To search workspace object(Item)
// In teamcenter whenever we want to search workspace object then we search through General.. (General search)

#include "Header.h"

int ITK_user_main(int argc, char* argv[])
{
	int i = 0;
	int iFail = 0;
	int iCount = 0;
	char* cItemID = NULL;
	char* cItemName = NULL;

	tag_t* tSerachList = NULLTAG;
	tag_t tUser = NULLTAG;
	WSO_search_criteria_t tCriteria; // Declare structure variable

	iFail = ITK_init_module("infodba", "infodba", "dba");
	printf("\n\n Login Successful");
	Report_Error(iFail);

	iFail = WSOM_clear_search_criteria(&tCriteria);
	printf("\n\n Clear Search criteria");
	Report_Error(iFail);

	iFail = SA_find_user2("infodba", &tUser);
	printf("\n\n User tag find success");
	Report_Error(iFail);

	// To copy string we have to use string copy
	// Whenever we are working with string we can not use = operator that's why we use tc_strcpy function
	tc_strcpy(tCriteria.class_name, "Item"); // kis type ka business object find krna hai
	tc_strcpy(tCriteria.name, "*");
	tCriteria.owner = tUser;

	iFail = WSOM_search(tCriteria, &iCount, &tSerachList);
	for (i = 0; i < iCount; i++)
	{
		WSOM_ask_name2(tSerachList[i], &cItemName);
		WSOM_ask_id_string(tSerachList[i], &cItemID);
		printf("\n ID is %s and Name is %s", cItemID, cItemName);
	}
	
	if (tSerachList)
	{
		MEM_free(tSerachList);
	}


	return 0;
}
