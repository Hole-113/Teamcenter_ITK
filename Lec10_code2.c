// Assign 14
// To execute an query to search the items

#include"Header.h"

int ITK_user_main(int argc, char* argv[])
{
	int iFail = 0;
	int iEntriesCount = 0;
	int iItemFound = 0;

	char** cEntries = NULL;
	char** cValues = NULL;
	char* cItemName = NULL;

	tag_t tQuery = NULLTAG;
	tag_t* tResults = NULLTAG;

	iFail = ITK_init_module("infodba", "infodba", "dba");
	printf("\n\n Login Successful");
	Report_Error(iFail);

	// Find out the query tag by passing query name.
	iFail = QRY_find2("Item Name", &tQuery);
	printf("\n\n Query find Successfuly");
	Report_Error(iFail);

	if (tQuery != NULL)
	{
		// we get the query entries and there default values.
		iFail = QRY_find_user_entries(tQuery, &iEntriesCount, &cEntries, &cValues);

		if (cEntries != NULL)
		{
			printf("\n\n Query Entries find Successful");

			for (int j = 0; j < iEntriesCount; j++)
			{
				if (tc_strcmp(cEntries[j], "Item Name") == 0)
				{
					// updating the default values
					tc_strcpy(cValues[j], "*");

					iFail = QRY_execute(tQuery, iEntriesCount, cEntries, cValues, &iItemFound, &tResults);

					if (tResults != NULLTAG)
					{
						printf("\n\n NUmber of Items Found : %d", iItemFound);
						for (int i = 0; i < iItemFound; i++)
						{
							iFail = WSOM_ask_name2(tResults[i],&cItemName);
							printf("\n\n Item Name is : %s", cItemName);
						}
					}


				}
			}
		}


	}
	if (cEntries)
	{
		MEM_free(cEntries);
	}
	if (cValues)
	{
		MEM_free(cValues);
	}

	iFail = ITK_exit_module(TRUE);
	printf("\n\n Logout Success");
	Report_Error(iFail);

	return 0;
}
