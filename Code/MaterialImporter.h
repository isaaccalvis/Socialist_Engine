#ifndef __MaterialImporter_H__
#define __MaterialImporter_H__

#include "Importer.h"

class MaterialImporter : public Importer
{
public:
	MaterialImporter();
	~MaterialImporter();

	void Import(const char* path, const uuid_unit uuid, const ImporterSettings* settings = nullptr);
	void Load(const char* exportedFile);
	Texture* LoadTexture(const char* exportedFile);
};

#endif