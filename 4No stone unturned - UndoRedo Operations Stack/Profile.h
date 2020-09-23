#pragma once

typedef struct
{
	int profileIdNumber;
	char* placeOfBirth;
	char* psychologicalProfile;
	int yearsOfRecordedService;
} Profile;

/*
	Creates a Profile.
	input:
		- int profileIdNumber
		- char* placeOfBirth
		- char* psychologicalProfile
		- int yearsOfRecordedService
	output: returns a pointer to a new Profile
*/
Profile* createProfile(int profileIdNumber, char* placeOfBirth, char* psychologicalProfile, int yearsOfRecordedService);
/*
	Copies a Profile and returns a pointer to the copy.
	input:
		- Profile* profileToBeCopied
	output: returns a pointer to a copy of the initial Profile
*/
Profile* copyProfile(Profile* profile);
/*
	Gets the ProfileIdNumber
	input:
		- Profile* Profile
	output: returns the ProfileIdNumber(int)
*/
int getProfileIdNumber(Profile* profile);
/*
	Gets the PlaceOfBirth
	input:
		- Profile* Profile
	output: returns the PlaceOfBirth(char*)
*/
char* getPlaceOfBirth(Profile* profile);
/*
	Gets the PsychologicalProfile
	input:
		- Profile* Profile
	output: returns the PsychologicalProfile(char*)
*/
char* getPsychologicalProfile(Profile* profile);
/*
	Gets the YearsOfRecordedService
	input:
		- Profile* Profile
	output: returns the YearsOfRecordedService(int)
*/
int getYearsOfRecordedService(Profile* profile);
/*
	Destroys a Profile
	input: pointer to a Profile
	output: -
*/
void destroyProfile(Profile* profile);

