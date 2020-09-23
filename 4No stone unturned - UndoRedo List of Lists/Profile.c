#include "Profile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Profile* createProfile(int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService)
{
	Profile* newProfile = (Profile*)malloc(sizeof(Profile));
	newProfile->profileIdNumber = profileIdNumber;

	newProfile->placeOfBirth = (char*)malloc((strlen(placeOfBirth) + 1) * sizeof(char));
	strcpy(newProfile->placeOfBirth, placeOfBirth);

	newProfile->psychologicalProfile = (char*)malloc((strlen(psychologicalProfile) + 1) * sizeof(char));
	strcpy(newProfile->psychologicalProfile, psychologicalProfile);

	newProfile->yearsOfRecordedService = yearsOfRecordedService;

	return newProfile;
}

Profile* copyProfile(Profile* profile)
{
	if (profile == NULL)
		return NULL;

	Profile* copyProfile = createProfile(getProfileIdNumber(profile), getPlaceOfBirth(profile), getPsychologicalProfile(profile), getYearsOfRecordedService(profile));
	return copyProfile;
}

int getProfileIdNumber(Profile* profile)
{
	return profile->profileIdNumber;
}

char* getPlaceOfBirth(Profile* profile)
{
	return profile->placeOfBirth;
}

char* getPsychologicalProfile(Profile* profile)
{
	return profile->psychologicalProfile;
}

int getYearsOfRecordedService(Profile* profile)
{
	return profile->yearsOfRecordedService;
}

void destroyProfile(Profile* profile)
{
	if (profile == NULL)
		return;
	free(profile->placeOfBirth);
	free(profile->psychologicalProfile);
	free(profile);
}
