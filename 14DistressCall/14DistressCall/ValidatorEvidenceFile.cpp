#include "ValidatorEvidenceFile.h"

void ValidatorEvidenceFile::validateEvidenceFile(const EvidenceFile& evidenceFileToValidate)
{
	std::string errorsMessage;

	if (evidenceFileToValidate.getId() == "")
		errorsMessage += "Invalid id.\n";
	if(evidenceFileToValidate.getMeasurement() == "")
		errorsMessage += "Invalid measurement.\n";
	if (evidenceFileToValidate.getImageClarityLevel() == 0)
		errorsMessage += "Invalid image clarity level.\n";
	if (evidenceFileToValidate.getQuantity() == 0)
		errorsMessage += "Invalid quantity.\n";
	if (evidenceFileToValidate.getPhotograph() == "")
		errorsMessage += "Invalid photograph.\n";

	if (errorsMessage.size() > 0)
		throw ValidationException(errorsMessage);
}

void ValidatorId::validateId(const std::string& idToValidate)
{
	if (idToValidate == "")
		throw ValidationException("Invalid id.\n");
}