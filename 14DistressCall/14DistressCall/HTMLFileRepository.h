#pragma once
#include "FileRepository.h"

class HTMLFileRepository: public FileRepository
{

public:
	HTMLFileRepository(const std::string& fileName);

	void addEvidenceFile(const EvidenceFile& evidenceFile) override;
	void deleteEvidenceFile(const std::string& evidenceFileToDeleteId) override;
	void updateEvidenceFile(const EvidenceFile& evidenceFileToUpdate) override;

	std::vector<EvidenceFile> loadDataFromFile() override;
	void storeDataToFile(std::vector<EvidenceFile> evidenceFiles) override;

	void openExternal() override;
	~HTMLFileRepository() override {};
};

