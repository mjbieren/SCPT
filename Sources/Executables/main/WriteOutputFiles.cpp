#include "GlobalHelper.h"

long WriteOutputFiles(CTaxonomicGroup* pTaxonomicGroup, size_t sizeFastaFiles)
{
	long lReturn = ERR_NOERROR;

	size_t sizeTaxanomicSpecies = pTaxonomicGroup->GetVectorSize();

	std::string strOutputPath;
	lReturn = glb.propertyBag.GetOutputFolderPath(&strOutputPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_OUTPUTDIR_OSG;

	std::string strTimeStamp = std::to_string(std::time(0)); //Get a timeStamp
	std::string strFastaFileNumber = std::to_string(sizeFastaFiles);
	std::string strFullOutputPath = strOutputPath + strTimeStamp +"_FastaFilesNrs_"+ strFastaFileNumber+ "_SCPT_OUTPUT.tsv";

	//Set the File Buffer for all the files.
	char* pBuffer = new char[SIZE_BUFFER_ONE_GIG];
	CSmartPtr<char> pAutoDelete = pBuffer; //Create smart pointer so that we do not have to keep track of it.
	memset(pBuffer, '\0', SIZE_BUFFER_BIG); //Set all characters as zero terminated.
	char* pBufferPos = pBuffer;
	size_t sizeBufferLeft = SIZE_BUFFER_ONE_GIG;

	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "Species\tSequenceCount%s", EOL);
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - pBuffer);

	//Time to fill the file buffer
	CTaxonomicSpecies* pTaxonomicSpecies = nullptr;
	char* szStrainName = nullptr;
	size_t sizeCounter = 0;
	
	for (size_t idx = 0; idx < sizeTaxanomicSpecies; idx++)
	{
		pTaxonomicSpecies = pTaxonomicGroup->GetSpeciesVectorItem(idx);
		lReturn = pTaxonomicSpecies->GetSpeciesName(&szStrainName);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		sizeCounter = pTaxonomicSpecies->GetSequenceCounter();

		sizeBufferLeft = sizeBufferLeft - (pBufferPos - pBuffer);
		pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "%s\t%zu%s",szStrainName, sizeCounter, EOL);

	}

	FILE* hFileSCPT = nullptr;

	errno_t errFopen_s =  fopen_s(&hFileSCPT, strFullOutputPath.c_str(), "wb");
	if (errFopen_s != ERR_NOERROR)
	{
		printf_s("Error WRITE_OUTPUT_FILE_ERROR_FOPEN: %s on fopen_s() %s, on line %i in file %s %s", strFullOutputPath.c_str(), __LINE__, __FILE__,EOL);
		return WRITE_OUTPUT_FILE_ERROR_FOPEN;
	}
	else
	{
		fputs(pBuffer, hFileSCPT);
	}
	fclose(hFileSCPT);

	return lReturn;
}