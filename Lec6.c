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
	tag_t tHomeFolder = NULLTAG;
	tag_t tDatasetType = NULLTAG;
	tag_t tDataset = NULLTAG;
	tag_t tRelationType = NULLTAG;
	tag_t tRelation = NULLTAG;

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
		Report_Error(iFail);
		printf("\n Item tag find Success");
		Report_Error(iFail);

		// Find Item revision tag
		iFail = ITEM_find_revision(tItem, "A", &tRev);
		printf("\n Item Revision tag find success");
		Report_Error(iFail);

		// Find DatasetType tag
		iFail = AE_find_datasettype2("PDF", &tDatasetType);
		printf("\n\n DatasetType tag find Success");
		Report_Error(iFail);

		// Create dataset
		iFail = AE_create_dataset_with_id(tDatasetType,"MyPDF","","","",&tDataset);
		printf("\n\n Dataset create succeess");
		Report_Error(iFail);

		// Save Dataset
		iFail = AE_save_myself(tDataset);
		printf("\n\n Dataset Save Success");
		Report_Error(iFail);

		// Find RelationType tag
		iFail = GRM_find_relation_type("IMAN_specification", &tRelationType);
		printf("\n\n RelationType tag find success");
		Report_Error(iFail);

		// Relation successfully created means Dataset attach to ItemRevision.
		iFail = GRM_create_relation(tRev, tDataset,tRelationType,NULLTAG,&tRelation);
		printf("\n\n Relation create Success");
		Report_Error(iFail);

		// Save Relation
		iFail = GRM_save_relation(tRelation);
		printf("\n\n Relation save success");

		iFail = ITK_exit_module(TRUE);
		printf("\n\n Logout Success");
		Report_Error(iFail);
	}
	return 0;
}
