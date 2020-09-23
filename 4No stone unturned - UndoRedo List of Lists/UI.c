#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LENGTH_INPUT 200
#define MAXIMUM_NUMBER_PROFILES 100
#define MAXIMUM_LENGTH_PROFILE_STRING 200
#define MAXIMUM_LENGTH_PSYCHOLOGICAL_PROFILE_STRING 50
#define MAXIMUM_LENGTH_PROFILE_ARGUMENT_STRING 50


UI* createUI(Controller* controller)
{
	UI* newUI = (UI*)malloc(sizeof(UI));
	newUI->controller = controller;

	return newUI;
}

void destroyUI(UI* ui)
{
	destroyController(ui->controller);

	free(ui);
}

int addProfileUI(UI* ui, char* inputParameters)
{
	int profileIdNumber, yearsOfRecordedService;
	char* placeOfBirth = NULL;
	char* psychologicalProfile = NULL;

	inputParameters = strtok(NULL, ", ");
	profileIdNumber = atoi(inputParameters);

	inputParameters = strtok(NULL, ", ");
	placeOfBirth = inputParameters;

	inputParameters = strtok(NULL, ", ");
	psychologicalProfile = inputParameters;

	inputParameters = strtok(NULL, " ");
	yearsOfRecordedService = atoi(inputParameters);

	int duringUndo = 0;
	if (addProfileController(ui->controller, profileIdNumber, placeOfBirth, psychologicalProfile, yearsOfRecordedService, duringUndo) == -1)
	{
		printf("No! \n");
	}

	return 0;
}

int updateProfileUI(UI* ui, char* inputParameters)
{
	int newProfileIdNumber, newYearsOfRecordedService;
	char* newPlaceOfBirth = NULL;
	char* newPsychologicalProfile = NULL;

	inputParameters = strtok(NULL, ", ");
	newProfileIdNumber = atoi(inputParameters);

	inputParameters = strtok(NULL, ", ");
	newPlaceOfBirth = inputParameters;

	inputParameters = strtok(NULL, ", ");
	newPsychologicalProfile = inputParameters;

	inputParameters = strtok(NULL, " ");
	newYearsOfRecordedService = atoi(inputParameters);

	int duringUndo = 0;
	if (updateProfileController(ui->controller, newProfileIdNumber, newPlaceOfBirth, newPsychologicalProfile, newYearsOfRecordedService, duringUndo) == -1)
	{
		printf("No! \n");
	}
	return 0;
}

int deleteProfileUI(UI* ui, char* inputParameters)
{
	int profileIdNumber;

	inputParameters = strtok(NULL, " ");
	profileIdNumber = atoi(inputParameters);

	int duringUndo = 0;
	if (deleteProfileController(ui->controller, profileIdNumber, duringUndo) == -1)
	{
		printf("No! \n");
	}
	return 0;
}

char* getProfileAsString(Profile* profile)
{
	int profileIdNumber, yearsOfRecordedService;
	char profileAsString[MAXIMUM_LENGTH_PROFILE_STRING];
	char profileIdNumberAsString[MAXIMUM_LENGTH_PROFILE_ARGUMENT_STRING], yearsOfRecordedServiceAsString[MAXIMUM_LENGTH_PROFILE_ARGUMENT_STRING];

	strcpy(profileAsString, ""); //initialize profileAsString with the empty string
	strcpy(profileIdNumberAsString, "");
	strcpy(yearsOfRecordedServiceAsString, "");

	profileIdNumber = getProfileIdNumber(profile);
	yearsOfRecordedService = getYearsOfRecordedService(profile);

	strcat(profileAsString, "Profile Id Number: ");
	_itoa(profileIdNumber, profileIdNumberAsString, 10);
	strcat(profileAsString, profileIdNumberAsString);
	strcat(profileAsString, "  ");

	strcat(profileAsString, "Place Of Birth: ");
	strcat(profileAsString, getPlaceOfBirth(profile));
	strcat(profileAsString, "  ");

	strcat(profileAsString, "Psychological Profile: ");
	strcat(profileAsString, getPsychologicalProfile(profile));
	strcat(profileAsString, "  ");

	strcat(profileAsString, "Years Of Recorded Service: ");
	_itoa(yearsOfRecordedService, yearsOfRecordedServiceAsString, 10);
	strcat(profileAsString, yearsOfRecordedServiceAsString);

	return profileAsString;
}

void listProfilesUI(UI* ui)
{
	int indexProfiles;
	char profileAsString[MAXIMUM_LENGTH_PROFILE_STRING];

	Repository* repository = getAllProfilesController(ui->controller);
	int numberProfiles = getNumberProfilesController(ui->controller);

	for (indexProfiles = 0; indexProfiles < numberProfiles; indexProfiles++)
	{
		Profile* profile = getProfileByPosition(repository, indexProfiles);
		strcpy(profileAsString, getProfileAsString(profile));
		printf(profileAsString);
		printf("\n");
	}
	//free(profileAsString);
	//free(repository); //CHANGE

}

void listPsychologicalProfilesUI(UI* ui, char* inputParameter)
{
	char* psychologicalProfile = (char*)malloc(MAXIMUM_LENGTH_PSYCHOLOGICAL_PROFILE_STRING * sizeof(char));
	strcpy(psychologicalProfile, inputParameter);
	int indexProfiles;
	Repository* repository = getFilteredProfilesAfterPsychologicalProfileController(ui->controller, psychologicalProfile);
	int numberProfilesFilteredAfterPsychologicalProfile = getNumberProfiles(repository);
	char* profileAsString = (char*)malloc(MAXIMUM_LENGTH_PROFILE_STRING * sizeof(char));

	for (indexProfiles = 0; indexProfiles < numberProfilesFilteredAfterPsychologicalProfile; indexProfiles++)
	{
		Profile* profile = getProfileByPosition(repository, indexProfiles);
		strcpy(profileAsString, getProfileAsString(profile));
		printf(profileAsString);
		printf("\n");
	}
	free(psychologicalProfile);
	free(profileAsString);
	destroyRepository(repository);
	//free(repository);
}

void listMaximumYearsOfServiceUI(UI* ui, char* inputParameter)
{
	int indexProfiles;
	int maximumYearsOfService = atoi(inputParameter);
	Repository* repository = getFilteredProfilesAfterYearsOfServiceSortedAscendingController(ui->controller, maximumYearsOfService);
	int numberProfilesFilteredAfterYearsOfService = getNumberProfiles(repository);
	char* profileAsString = (char*)malloc(MAXIMUM_LENGTH_PROFILE_STRING * sizeof(char));

	for (indexProfiles = 0; indexProfiles < numberProfilesFilteredAfterYearsOfService ; indexProfiles++)
	{
		Profile* profile = getProfileByPosition(repository, indexProfiles);
		strcpy(profileAsString, getProfileAsString(profile));
		printf(profileAsString);
		printf("\n");
	}
	free(profileAsString);
	destroyRepository(repository);
	//free(repository);
}

int undoUI(UI* ui)
{
	if (undo(ui->controller) == -1)
	{
		printf("No more undos. \n");
	}

	return 0;
}

int redoUI(UI* ui)
{
	if (redo(ui->controller) == -1)
	{
		printf("No more redos. \n");
	}

	return 0;
}

void startUI(UI* ui)
{
	char input[MAXIMUM_LENGTH_INPUT];
	char* inputCommand = NULL;
	char* inputParameter = NULL;
	char* inputParameters = NULL;

	strcpy(input, "");

	while(1)
	{
		gets(input); //read a line ans store it in input

		if (strcmp(input, "exit") == 0)
		{
			return 0;
		}
		else
		{
			inputCommand = strtok(input, " ");

			if (strcmp(inputCommand, "list") == 0)
			{
				inputParameter = strtok(NULL, " ");

				if (inputParameter == NULL)
				{
					//the command is 'list'
					listProfilesUI(ui);
				}
				else
				{
					if (inputParameter[0] >= '0' && inputParameter[0] <= '9')
					{
						//the inputParameter is a number(maximumYearsOfService)
						listMaximumYearsOfServiceUI(ui, inputParameter);
					}
					else
					{
						//the inputParameter is 'psychologicalProfiles'
						listPsychologicalProfilesUI(ui, inputParameter);
					}
				}				
			}
			else if(strcmp(inputCommand, "add") == 0)
			{
				inputParameters = inputCommand;
				addProfileUI(ui, inputParameters);
			}
			else if (strcmp(inputCommand, "update") == 0)
			{
				inputParameters = inputCommand;
				updateProfileUI(ui, inputParameters);
			}
			else if(strcmp(inputCommand, "delete") == 0)
			{
				inputParameters = inputCommand;
				deleteProfileUI(ui, inputParameters);
			}
			else if (strcmp(inputCommand, "undo") == 0)
			{
				undoUI(ui);
			}
			else if (strcmp(inputCommand, "redo") == 0)
			{
				redoUI(ui);
			}
			else
			{
				printf("Bad Command \n");
			}
		}

	}
}
