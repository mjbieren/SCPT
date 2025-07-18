#!/bin/bash

#SCPT.out -f <FastaFilesPath> -r <OutputFolderPath> -t <TaxonomicGroupFile> [-s]

PROGRAM_PATH=SCPT.out
FASTAFILES= #Folder containing fasta FILES
OUTPUT=	#Output Folder
TAXANOMICGROUP= #Path to taxonomic group files


#Run where the headers are with gene ids e.g. >Species1-GeneID_123
$PROGRAM_PATH -f $FASTAFILES -r $OUTPUT -t $TAXANOMICGROUP


#Run where we only have species (taxa) and NO gene ids e.g. >Species1
#$PROGRAM_PATH -f $FASTAFILES -r $OUTPUT -t $TAXANOMICGROUP -s