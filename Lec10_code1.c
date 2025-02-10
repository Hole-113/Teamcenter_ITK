// Assign 13
// To chnage the ownership of the contents of the folder


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
	tag_t tNewUser = NULLTAG;
	tag_t tGroup = NULLTAG;
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
	tc_strcpy(tCriteria.name, "plm_OWNER");
	tCriteria.owner = tUser;

	iFail = WSOM_search(tCriteria, &iCount, &tSerachList);
	for (i = 0; i < iCount; i++)
	{
		WSOM_ask_name2(tSerachList[i], &cFolderName);
		printf("\n\n Name of Searched folder is %s", cFolderName);

		iFail = FL_ask_references(tSerachList[i], FL_fsc_by_name, &iObjectCount, &tObjects);
	//	Report_Error(iFail);

		iFail = SA_find_user2("AdminV", &tNewUser);
		printf("\n\n New user tag is find successfuly");
	//	Report_Error(iFail);
		
		iFail = SA_find_group("Engineering", &tGroup);
		printf("\n\n Group tag is find successfuly");
		//Report_Error(iFail);


		if (iObjectCount > 0)
		{
			printf("\n\n Number of child parts : %d", iObjectCount);
			for (int j = 0; j < iObjectCount; j++)
			{
				iFail = AOM_refresh(tObjects[j], TRUE);
				printf("\n\n Lock is apply on Object");
			//	Report_Error(iFail);

				iFail = AOM_set_ownership(tObjects[j], tNewUser, tGroup);
				printf("\n\n Ownership change successfuly");
				//Report_Error(iFail);

				iFail = AOM_save_with_extensions(tObjects[j]);
				//Report_Error(iFail);


				iFail = AOM_refresh(tObjects[j], FALSE);
			//	Report_Error(iFail);


			}
		}
		else
		{
			printf("\n\n Container is empty");
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

	iFail = ITK_exit_module(TRUE);
	printf("\n\n Logout Success");
	Report_Error(iFail);


	return 0;
}
