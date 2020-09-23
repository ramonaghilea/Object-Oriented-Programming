#include "Evidence.h"
#include <string>

using namespace std;

EvidenceFile::EvidenceFile() : id(""), measurement(""), imageClarityLevel(0), quantity(0), photograph("") {}

EvidenceFile::EvidenceFile(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph)
{
	this->id = id;
	this->measurement = measurement;
	this->imageClarityLevel = imageClarityLevel;
	this->quantity = quantity;
	this->photograph = photograph;
}

std::string EvidenceFile::getId() const
{
	return this->id;
}

std::string EvidenceFile::getMeasurement() const
{
	return this->measurement;
}

double EvidenceFile::getImageClarityLevel() const
{
	return this->imageClarityLevel;
}

int EvidenceFile::getQuantity() const
{
	return this->quantity;
}

std::string EvidenceFile::getPhotograph() const
{
	return this->photograph;
}

bool EvidenceFile::operator==(const EvidenceFile& evidenceFile)
{
	if (this->id == evidenceFile.getId() && this->measurement == evidenceFile.getMeasurement() && this->imageClarityLevel == evidenceFile.getImageClarityLevel() && this->quantity == evidenceFile.getQuantity() && this->photograph == evidenceFile.getPhotograph())
		return true;
	return false;
}

std::string EvidenceFile::EvidenceFileAsString()
{
	return getId() + " " + getMeasurement() + " " + std::to_string(getImageClarityLevel()) + " " + std::to_string(getQuantity()) + " " + getPhotograph();
}

std::string EvidenceFile::EvidenceFileAsStringFileFormat()
{
	return getId() + "," + getMeasurement() + "," + std::to_string(getImageClarityLevel()) + "," + std::to_string(getQuantity()) + "," + getPhotograph();
}

std::string EvidenceFile::EvidencefileAsStringHTMLFileFormat()
{
	std::string evidenceFileasString;
	evidenceFileasString += "<td>" + getId() + "</td> \n";
	evidenceFileasString += "<td>" + getMeasurement() + "</td> \n";
	evidenceFileasString += "<td>" + std::to_string(getImageClarityLevel()) + "</td> \n";
	evidenceFileasString += "<td>" + std::to_string(getQuantity()) + "</td> \n";
	evidenceFileasString += "<td>" + getPhotograph() + "</td>";

	return evidenceFileasString;
}

std::istream& operator>>(std::istream& inputStream, EvidenceFile& evidenceFile)
{
	std::string inputLine;
	getline(inputStream, inputLine);
	char delimiter = ',';

	std::vector<std::string> resultVectorStringEvidenceFileParameters = tokenizeStringEvidenceFile(inputLine, delimiter);

	if (resultVectorStringEvidenceFileParameters.size() == 0)
		return inputStream;

	// the EvidenceFile object has 5 parameters
	std::string id, measurement, imageClarityLevelAsString, quantityAsString, photograph;
	double imageClarityLevel;
	int quantity;

	id = resultVectorStringEvidenceFileParameters[0];
	measurement = resultVectorStringEvidenceFileParameters[1];
	imageClarityLevelAsString = resultVectorStringEvidenceFileParameters[2];
	quantityAsString = resultVectorStringEvidenceFileParameters[3];
	photograph = resultVectorStringEvidenceFileParameters[4];

	imageClarityLevel = atof(imageClarityLevelAsString.c_str());
	quantity = atoi(quantityAsString.c_str());

	// assign the parameters to evidenceFile
	evidenceFile.id = id;
	evidenceFile.measurement = measurement;
	evidenceFile.imageClarityLevel = imageClarityLevel;
	evidenceFile.quantity = quantity;
	evidenceFile.photograph = photograph;

	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, EvidenceFile& evidenceFile)
{
	std::string EvidenceFileAsStringFileFormat = evidenceFile.EvidenceFileAsStringFileFormat() + "\n";

	outputStream << EvidenceFileAsStringFileFormat;

	return outputStream;
}

std::vector<std::string> tokenizeStringEvidenceFile(std::string& EvidenceFileAsString, char delimiter)
{
	std::vector<std::string> resultVectorStringEvidenceFileParameters{};
	int lengthDelimiter = 1;
	std::string parameter;

	if (EvidenceFileAsString.size() == 0)
		return resultVectorStringEvidenceFileParameters;

	while (EvidenceFileAsString.find(delimiter) >= 0 && EvidenceFileAsString.find(delimiter) < EvidenceFileAsString.size())
	{
		parameter = EvidenceFileAsString.substr(0, EvidenceFileAsString.find(delimiter));
		resultVectorStringEvidenceFileParameters.push_back(parameter);
		EvidenceFileAsString = EvidenceFileAsString.erase(0, EvidenceFileAsString.find(delimiter) + lengthDelimiter);
	}
	parameter = EvidenceFileAsString;
	resultVectorStringEvidenceFileParameters.push_back(parameter);

	return resultVectorStringEvidenceFileParameters;
}