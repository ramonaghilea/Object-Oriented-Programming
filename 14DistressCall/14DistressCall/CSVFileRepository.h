#pragma once
#include "FileRepository.h"

class CSVFileRepository: public FileRepository
{
public:
	CSVFileRepository(const std::string& fileName);

	void addEvidenceFile(const EvidenceFile& evidenceFileToAdd) override;
	void deleteEvidenceFile(const std::string& evidenceFileToDeleteId) override;
	void updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate) override;

	std::vector<EvidenceFile> loadDataFromFile() override;
	void storeDataToFile(std::vector<EvidenceFile> evidenceFiles) override;
	void openExternal() override;

	~CSVFileRepository() override;
};

