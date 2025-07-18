#include "GlobalHelper.h"

#define TOTALREQUIREMENTS 3

long ParseCommandLine(int argc, char* argv[], char* envp[])
{
	long lRet = ERR_NOERROR;

	int aiRequirements[TOTALREQUIREMENTS] = { 0,0,0};
	for (int i = 1; i < argc; i++)
	{

		printf_s("arg %i, %s %s", i, argv[i], EOL);



		if (*argv[i] == '-') //switch detected
		{
			switch (argv[i][1])
			{
			case 'f': //Input fasta files dir path
				lRet = glb.propertyBag.SetFastaDirPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_FASTADIR_OSG;
				aiRequirements[0] = 1;
				break;			
			case 'r': //Output dir Path
				lRet = glb.propertyBag.SetOutputFolderPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_OUTPUTDIR_OSG;
				aiRequirements[1] = 1;
				break;
			case 't': //Taxonomic Group File Path
				lRet = glb.propertyBag.SetTaxonomicGroupFilePath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_TAXONOMICGROUPFILE_OSG;
				aiRequirements[2] = 1;
				break;
			case 's': //You set if the fasta headers have only strain (no gene identifications!)
				lRet = glb.propertyBag.SetBoolStrainOnly();
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_BOOLSTRAINONLY_SCPT;
				break;
			default:
			{
				printf_s("Invalid command line parameter no %i detected: %s %s", i, argv[i], EOL);
				return PARSE_COMMAND_LINE;
			}
			}
		}
		else if (*argv[i] == '?')
		{
			//print arguments: ToDO change it
			printf_s(
				"%s"
				"-f <FastaFilesPath> Set the Path to the directory containing your fasta files: REQUIRED %s"
				"-r <OutputFolderPath>\t\t Set the Output Folder Path: REQUIRED %s"
				"-t <TaxonomicGroupFile>\t Set the Taxonomic Group File, used to filter your result: REQUIRED %s"
				"-s \t\t\t\t Tells the program that you just have strain/species and no gene identifications in your fasta header.%s"
				"%s"
				, EOL, EOL, EOL, EOL,EOL,EOL);
			return PARSE_COMMAND_LINE_MAN;
		}
		if (lRet != ERR_NOERROR)
			return lRet;
	}

	//Check if the other requiprements are met, if not sent a message to the user like if they would use ?. And sent back an error message.
	int iSum = 0;
	size_t idx = 0;
	while (idx < TOTALREQUIREMENTS)
	{
		iSum += aiRequirements[idx];
		idx++;
	}

	if (iSum == TOTALREQUIREMENTS)
		return lRet;
	else
	{
		//print arguments
		printf_s(
			"%s"
			"-f <FastaFilesPath> Set the Path to the directory containing your fasta files: REQUIRED %s"
			"-r <OutputFolderPath>\t\t Set the Output Folder Path: REQUIRED %s"
			"-t <TaxonomicGroupFile>\t Set the Taxonomic Group File, used to filter your result: REQUIRED %s"
			"-s \t\t\t\t Tells the program that you just have strain/species and no gene identifications in your fasta header.%s"
			"%s"
			, EOL, EOL, EOL, EOL,EOL,EOL);
		return PARSE_COMMAND_LINE_MAN;
	}
	
	return lRet;
}