#pragma once

#include "Profile.h"
#include "DynamicArray.h"


typedef struct
{
	DynamicArray* profiles;

} Repository;

/*
	Creates a Repository;
	input: -
	output: returns a pointer to a new Repository
*/
Repository* createRepository();
/*
	Destroys a Repository;
	input: pointer to a Repository
	output: -
*/
void destroyRepository(Repository* repository);

/*
	Adds a profile to the Repository.
	input:
		- pointer to Repository
		- Profile to be added
	output:
		- returns an error if the Profile could not be added
*/
int addProfileRepository(Repository* repository, Profile* profile);
/*
	Updates a profile in the Repository.
	input:
		- pointer to Repository
		- Profile to be updated (the ProfileIdNUmber will be the same)
	output:
		- returns an error if the Profile could not be updated
*/
int updateProfileRepository(Repository* repository, Profile* profile);
/*
	Deletes a profile from the Repository.
	input:
		- pointer to Repository
		- ProfileIdNumber of the Profile to be deleted
	output:
		- returns an error if the Profile could not be deleted
*/
int deleteProfileRepository(Repository* repository, int profileIdNumber);

/*
	Gets the numberOfProfiles in the repository.
	input:
		- pointer to Repository
	output:
		- int numberOfProfiles
*/
int getNumberProfiles(Repository* repository);
/*
	Gets all the profiles as a Repository.
	input:
		- pointer to Repository
	output:
		- returns a Repository with all the profiles
*/
Repository* getAllProfiles(Repository* repository);
/*
	Gets a profile by the position in repository.
	input:
		- pointer to Repository
		- int positionProfile
	output:
		- returns the profile on position positionProfile
*/
Profile* getProfileByPosition(Repository* repository, int positionProfile);
/*
	Gets a profile by the profileIdNumber.
	input:
		- pointer to Repository
		- int profileIdNumber
	output:
		- returns the profile with the profileIdNumber
*/
Profile* getProfileByIdNumber(Repository* repository, int profileIdNumber);
/*
	Gets all the profiles that have YearsOfRecordedService < maximumYearsOfService as a Repository.
	input:
		- pointer to Repository
		- int maximumYearsOfService
	output:
		- returns a Repository with the profiles that match the criteria
*/
Repository* getFilteredProfilesAfterYearsOfService(Repository* repository, int maximumYearsOfService);
/*
	Gets all the profiles that have the psychologicalProfile the same as parameter PsychologicalProfile as a Repository.
	input:
		- pointer to Repository
		- char* psychologicalProfile
	output:
		- returns a Repository with the profiles that match the criteria
*/
Repository* getFilteredProfilesAfterPsychologicalProfile(Repository* repository, char* psychologicalProfile);
