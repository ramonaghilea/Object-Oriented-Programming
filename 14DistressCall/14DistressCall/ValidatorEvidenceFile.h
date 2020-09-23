#pragma once
#include "Evidence.h"
#include "Exceptions.h"

class ValidatorEvidenceFile
{
public:
	static void validateEvidenceFile(const EvidenceFile& evidenceFileToValidate);
};

class ValidatorId
{
public:
	static void validateId(const std::string& idToValidate);
};