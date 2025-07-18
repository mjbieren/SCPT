#pragma once

#include "stdafx.h"
#include "Management.h"

class CSCPTPropertyBag : CPropertyBag
{
protected:
	char m_szGetOrthoGroupSequenceGrabberErrMessage[255];
public:
	CSCPTPropertyBag() {};
	~CSCPTPropertyBag() {};
	const char* GetLastOrthoGroupSequenceGrabberErrorMessage() { return m_szGetOrthoGroupSequenceGrabberErrMessage; }

/*
Fasta File Directory
Output Directory
Taxonomic Group File
*/
	long SetTaxonomicGroupVectorSize(size_t sizeTaxonomicGroupsize)
	{
		return SetValueSizeT("TaxonomicGroup", "VectorSize", sizeTaxonomicGroupsize);
	}

	long GetTaxonomicGroupVectorSize(size_t* psizeTaxonomicGroup)
	{
		return GetValueSizeT("TaxonomicGroup", "VectorSize", psizeTaxonomicGroup, 0);
	}

	long SetFastaDirPath(const char* szFastaDirPath)
	{
		std::string strFastaPath = szFastaDirPath;
		AppendSlash(&strFastaPath); //This is to make sure the path ends with a /
		return SetValueString("Paths", "FastaFiles", strFastaPath.c_str());
	}

	long GetFastaDirPath(std::string* pstrFastaQueryPath)
	{
		return GetValueString("Paths", "FastaFiles", pstrFastaQueryPath);
	}

	long SetOutputFolderPath(const char* szOutputPath)
	{
		std::string strOutputPath = szOutputPath;
		AppendSlash(&strOutputPath);
		return SetValueString("Paths", "Output", strOutputPath.c_str());
	}

	long GetOutputFolderPath(std::string* pstrOutputPath)
	{
		return GetValueString("Paths", "Output", pstrOutputPath);
	}

	long SetTaxonomicGroupFilePath(const char* szTaxonomicGroupFile)
	{
		return SetValueString("Paths", "TaxonomicGroupFile", szTaxonomicGroupFile);
	}

	long GetTaxonomicGroupFilePath(std::string* pstrTaxonomicGroupFile)
	{
		return GetValueString("Paths", "TaxonomicGroupFile", pstrTaxonomicGroupFile);
	}

	long SetBoolStrainOnly(bool bStrainOnly = true)
	{
		return SetValueBool("Bool", "StrainOnly", bStrainOnly);
	}

	long GetBoolStrainOnly(bool* bpStrainOnly)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "StrainOnly", bpStrainOnly, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Strain only Bool Not Found: Default used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;

	}
};