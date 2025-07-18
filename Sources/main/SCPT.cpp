#include "GlobalHelper.h"
CGlobal glb;

long CheckReturnValue(long lReturn, std::vector<CFastaFile*>* pvecFastaFilesSource, std::vector<CTaxonomicGroup*>* pvecTaxonomicGroups);
long ParseCommandLine(int argc, char* argv[], char* envp[]);
long ParseInputFiles(std::vector<CFastaFile*>* pvecFastaFilesSource, std::vector<CTaxonomicGroup*>* pvecTaxonomicGroups, CTaxonomicGroup* pTaxonomicGroupsSorted);
long MatchFastaSequencesToTaxa(std::vector<CFastaFile*>* pvecFastaFiles, CTaxonomicGroup* pTaxonomicGroupSorted);
long WriteOutputFiles(CTaxonomicGroup* pTaxonomicGroup, size_t sizeFastaFiles);


/*
This program is going to check all fasta files and count up the amount of sequences per taxa.
This is based on an TaxonomicGroup file.


1) Parse Command line
2) Parse the input files (Taxonomic file and fasta files)
3) Match the headers to the taxonomic species and increase the sequence counter in that taxonomic species)
4) Write the output file.
5) Clean up.

*/


int main(int argc, char* argv[], char* envp[])
{

    long lReturn = ERR_NOERROR;

    //STEP ONE
    printf_s("Parsing the command line %s", EOL);
    lReturn = ParseCommandLine(argc, argv, envp);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the command line %s", EOL);

    //Set the Variables
	std::vector<CFastaFile*> vecFastaFilesSource; //The original fasta files, you use during orthofinder
	std::vector<CTaxonomicGroup*> vecTaxonomicGroups; //Taxonomic Group file split in different groups. The amount of objects in the vectors = how many taxonomic group sthere is in total. Do not confuse that with how many there need to be.

	//Create an object for the taxonomic Group but then sorted, for easy search during the matching.
    CTaxonomicGroup* pTaxonomicGroupSorted = new CTaxonomicGroup;
    //Set the boolean to delete the vector objects to false, since the objects exist in the vecTaxonomicGroups vector and we can't delete an object twice!
    pTaxonomicGroupSorted->SetDeleteTaxonomicSpecies(false);
    //Set a Smart pointer for the object so that we do not have to keep trace of deleting it, it will be deleted automatically :)
    CSmartPtr<CTaxonomicGroup> pAutoDeleteTaxonomicGroup = pTaxonomicGroupSorted;

    //STEP TWO	
    printf_s("Parsing the input files %s", EOL);
    lReturn = ParseInputFiles(&vecFastaFilesSource, &vecTaxonomicGroups, pTaxonomicGroupSorted);
    CheckReturnValue(lReturn, &vecFastaFilesSource, &vecTaxonomicGroups);
	CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the input files %s", EOL);

    //STEP THREE
    printf_s("Count the Sequences in the fasta files %s", EOL);
    lReturn = MatchFastaSequencesToTaxa(&vecFastaFilesSource, pTaxonomicGroupSorted);
    CheckReturnValue(lReturn, &vecFastaFilesSource, &vecTaxonomicGroups);
	CHECK_RETURNVALUE(lReturn);
    printf_s("Done with Counting the sequences %s", EOL);

    //STEP FOUR
    printf_s("Writing Output File %s", EOL);
    lReturn = WriteOutputFiles(pTaxonomicGroupSorted, vecFastaFilesSource.size());
	CheckReturnValue(lReturn, &vecFastaFilesSource, &vecTaxonomicGroups);
	CHECK_RETURNVALUE(lReturn);
    printf_s("Done with Writing the output file %s", EOL);

    //STEP FIVE
    ClearVector(&vecFastaFilesSource);
    ClearVector(&vecTaxonomicGroups);

    return 0;
}