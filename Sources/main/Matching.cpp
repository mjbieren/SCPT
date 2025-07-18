#include "GlobalHelper.h"

long MatchFastaSequencesToTaxa(std::vector<CFastaFile*>* pvecFastaFiles, CTaxonomicGroup* pTaxonomicGroupSorted)
{
	long lReturn = ERR_NOERROR;

	size_t sizeFastaVector = pvecFastaFiles->size();
	size_t sizeFastaBlocks = 0;
	CTaxonomicSpecies* pTaxonomicSpeciesToFind = nullptr;
	CFastaFile* pFastaFile = nullptr;
	CFastaBlock* pFastaBlock = nullptr;

	char* pSpeciesName = nullptr;

	bool bStrainOnly = false;
	lReturn = glb.propertyBag.GetBoolStrainOnly(&bStrainOnly);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_GETBOOLSTRAINONLY_SCPT;

	//Loop over all the fasta files
	for (size_t idx = 0; idx < sizeFastaVector; idx++)
	{
		//Loop over A fasta file and over their fasta blocks
		pFastaFile = pvecFastaFiles->at(idx);
		sizeFastaBlocks = pFastaFile->GetVectorSize();

		for (size_t idx2 = 0; idx2 < sizeFastaBlocks; idx2++)
		{
			//Find to which species this fasta block belongs to.
			pFastaBlock = pFastaFile->GetFastaBlock(idx2);
			if (bStrainOnly == false)
			{
				lReturn = pFastaBlock->GetFastaHeaderStrain(&pSpeciesName);
				if (lReturn != ERR_NOERROR)
					return lReturn;
			}
			else
			{
				lReturn = pFastaBlock->GetFastaHeader(&pSpeciesName);
				if (lReturn != ERR_NOERROR)
					return lReturn;
			}

			//Find the right Taxa and increase the sequence there.
			lReturn = pTaxonomicGroupSorted->FindTaxonomicSpeciesFromSpeciesName(pSpeciesName, &pTaxonomicSpeciesToFind);
			if (lReturn != ERR_NOERROR)
				return lReturn;

			//Increase the sequence counter because fasta block is matched to this one :)
			pTaxonomicSpeciesToFind->IncreaseSequenceCounter();
		}

	}


	return lReturn;
}