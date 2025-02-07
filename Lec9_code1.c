// Assign 10
// To export the dataset named reference.


#include"Header.h"
int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	int i = 0;
	int j = 0;
	int iRefCount = 0;
	char* cError = NULL;
	char* cUserID = NULL;
	char* cPassword = NULL;
	char* cGroup = NULL;
	char* cItemID = NULL;
	char* cSecObjType = NULL;
	int iSec_obj_count = 0;

	tag_t tItem = NULLTAG;
	tag_t tRev = NULLTAG;
	tag_t tHomeFolder = NULLTAG;
	tag_t tDatasetType = NULLTAG;
	tag_t tDataset = NULLTAG;
	tag_t tRelationType = NULLTAG;
	tag_t tRelation = NULLTAG;
	tag_t* tSecObjects = NULLTAG;
	tag_t* tNamedRef = NULLTAG;

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


		// Find Item revision tag
		iFail = ITEM_find_rev(cItemID, "A", &tRev);
		printf("\n Item Revision tag find success");
		Report_Error(iFail);



		// Find RelationType tag
		iFail = GRM_find_relation_type("IMAN_specification", &tRelationType);
		printf("\n\n RelationType tag find success");
		Report_Error(iFail);


		// List secondary object 
		iFail = GRM_list_secondary_objects_only(tRev, tRelationType, &iSec_obj_count, &tSecObjects);
		printf("\n\n List all secondary objects");
		Report_Error(iFail);

		for (i = 0; i < iSec_obj_count; i++)
		{
			iFail = WSOM_ask_object_type2(tSecObjects[i], &cSecObjType);
			printf("\n\n Dataset Type is %s", cSecObjType);

			if (tc_strcmp(cSecObjType, "PDF") == 0)
			{
				iFail = AE_ask_all_dataset_named_refs2(tSecObjects[i], "PDF_Reference", &iRefCount, &tNamedRef);
				printf("\n\n Named Reference find success");
				Report_Error(iFail);

				for (j = 0; j < iRefCount; j++)
				{
					iFail = AE_export_named_ref(tSecObjects[i], "PDF_Reference","C:\\Data");
					printf("\n\n Named ref export success");
					Report_Error(iFail);
				}

			}
			else if (tc_strcmp(cSecObjType, "Text") == 0)
			{

				iFail = AE_ask_all_dataset_named_refs2(tSecObjects[i], "Text", &iRefCount, &tNamedRef);
				printf("\n\n Named Reference find success");
				Report_Error(iFail);

				for (j = 0; j < iRefCount; j++)
				{
					iFail = AE_export_named_ref(tSecObjects[i], "Text", "C:\\Data\\amit.txt");
					printf("\n\n Named ref export success");
					Report_Error(iFail);
				}
				
			}

		}

		iFail = ITK_exit_module(TRUE);
		printf("\n\n Logout Success");
		Report_Error(iFail);
	}
	else {
		printf("\n\n Argument count is less or more");
	}
	if (tSecObjects)
	{
		MEM_free(tSecObjects);
	}
	return 0;
}
