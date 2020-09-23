#pragma once
#include <iostream>
#include <vector>
#include <string>

class EvidenceFile
{
private:
	std::string id;
	std::string measurement;
	double imageClarityLevel;
	int quantity;
	std::string photograph;

public:
	EvidenceFile(); //default constructor

	EvidenceFile(const std::string& id, const std::string& measurement, const double& imageClarityLevel, const int& quantity, const std::string& photograph);

	// getters
	std::string getId() const;
	std::string getMeasurement() const;
	double getImageClarityLevel() const;
	int getQuantity() const;
	std::string getPhotograph() const;

	bool operator==(const EvidenceFile& evidenceFile);

	std::string EvidenceFileAsString();
	std::string EvidenceFileAsStringFileFormat();
	std::string EvidencefileAsStringHTMLFileFormat();

	// friend std::vector<std::string> tokenizeStringEvidenceFile(std::string& EvidenceFileAsString, char delimiter);

	friend std::istream& operator>>(std::istream& inputStream, EvidenceFile& evidenceFile);
	friend std::ostream& operator<<(std::ostream& outputStream, EvidenceFile& evidenceFile);
};

std::vector<std::string> tokenizeStringEvidenceFile(std::string& EvidenceFileAsString, char delimiter);


