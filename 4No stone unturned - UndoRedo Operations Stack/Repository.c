#include "Repository.h"
#include <stdlib.h>
#include <string.h>

Repository* createRepository()
{
	Repository* newRepository = (Repository*)malloc(sizeof(Repository));
	if (newRepository == NULL)
		return NULL;

	newRepository->profiles = createDynamicArray(DYNAMIC_ARRAY_CAPACITY);

	return newRepository;
}

void destroyRepository(Repository* repository)
{
	if (repository == NULL)
		return;

	destroyDynamicArray(repository->profiles); //here was the leak, wrote 'free' instead of 'destroyDynamicArray'
	free(repository);
}

int addProfileRepository(Repository* repository, Profile* profile)
{
	if (repository == NULL || profile == NULL)
		return -1;

	if (getIndexProfileByProfileIdNumber(repository->profiles, profile->profileIdNumber) >= 0)
	{
		return -1;
	}

	addElement(repository->profiles, profile);

	return 0;
}

int updateProfileRepository(Repository* repository, Profile* profile)
{
	if (repository == NULL || profile == NULL)
		return -1;

	int indexProfileToUpdate = getIndexProfileByProfileIdNumber(repository->profiles, profile->profileIdNumber);

	if (indexProfileToUpdate >= 0)
	{
		updateElement(repository->profiles, indexProfileToUpdate, profile);
		return 0;
	}
	return -1;
}

int deleteProfileRepository(Repository* repository, int profileIdNumber)
{
	if (repository == NULL)
		return -1;

	int indexProfileToDelete = getIndexProfileByProfileIdNumber(repository->profiles, profileIdNumber);

	if (indexProfileToDelete == -1)
	{
		return -1;
	}

	deleteElement(repository->profiles, indexProfileToDelete);

	return 0;
}

int getNumberProfiles(Repository* repository)
{
	if (repository == NULL)
		return -1;

	return getSize(repository->profiles);
}

Repository* getAllProfiles(Repository* repository)
{
	return repository;
}

Profile* getProfileByPosition(Repository* repository, int positionProfile)
{
	if (repository == NULL)
		return NULL;
	return getElementByPosition(repository->profiles, positionProfile);
}

Profile* getProfileByIdNumber(Repository* repository, int profileIdNumber)
{
	int indexProfile;
	if (repository == NULL)
		return NULL;
	for (indexProfile = 0; indexProfile < getSize(repository->profiles); indexProfile++)
	{
		if (getProfileIdNumber(getElementByPosition(repository->profiles, indexProfile)) == profileIdNumber)
		{
			return getElementByPosition(repository->profiles, indexProfile);
		}
	}
}

Repository* getFilteredProfilesAfterYearsOfService(Repository* repository, int maximumYearsOfService)
{
	Repository* filteredProfilesRepository = createRepository();
	Profile* profile = NULL;
	int numberProfiles = getSize(repository->profiles);

	for (int indexProfile = 0; indexProfile < numberProfiles; indexProfile++)
	{
		profile = getElementByPosition(repository->profiles, indexProfile);
		if (getYearsOfRecordedService(profile) < maximumYearsOfService)
		{
			addElement(filteredProfilesRepository->profiles, copyProfile(profile));
		}
	}
	//destroyProfile(profile);
	return filteredProfilesRepository;

}

Repository* getFilteredProfilesAfterPsychologicalProfile(Repository* repository, char* psychologicalProfile)
{
	Repository* filteredProfilesRepository = createRepository();
	Profile* profile = NULL;
	int numberProfiles = getSize(repository->profiles);

	for (int indexProfile = 0; indexProfile < numberProfiles; indexProfile++)
	{
		profile = getElementByPosition(repository->profiles, indexProfile);
		if (strcmp(getPsychologicalProfile(profile), psychologicalProfile) == 0)
		{
			addElement(filteredProfilesRepository->profiles, copyProfile(profile));
		}
	}
	return filteredProfilesRepository;

}