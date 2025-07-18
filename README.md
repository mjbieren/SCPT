# SCPT (Sequence Counter Per Taxa)

SCPT is a small utility tool that scans FASTA files in a folder and counts the number of times each taxonomic group (species/strain) occurs, based on a user-provided taxonomic group file.

The output is a **tab-delimited summary file** containing the species name in the first column and the number of occurrences in the second column. This is useful for quickly assessing representation across orthogroups or gene family files.

## 🔧 Header Simplification
Before running SCPT, ensure that all FASTA headers follow a consistent format that links each gene to its corresponding species. This is essential for accurate taxonomic grouping.

### Example Required Format:
```
>Species1-GeneID_123
ATGG...
>Species1-GeneID_566
ATGC...
>Species2-GeneID_123
ATGA...
>Species3-GeneID_123
ATGT...
```

If your headers are inconsistent or complex, use the helper script [`simplify_headers_for_blastdb.py`](https://github.com/mjbieren/SCPT/blob/main/simplify_headers_for_blastdb.py) by Dr. Iker Irisarri to clean and standardize them. Before combining species sets (like with Orthofinder)

```
python simplify_headers_for_blastdb.py [inputFile] [RenameHeaders] >> [FileOutput]
```

---

## 🧰 Compiled Executables

This C++ tool was developed using Boost v1.88 and compiled with GCC (Linux) in Visual Studio 2019.

Precompiled versions:

- [Debian 12](https://github.com/mjbieren/SCPT/blob/main/Sources/Executables/SCPT_Static_Debian.out): `SCPT_Static_Debian.out`
- [Rocky Linux 8](https://github.com/mjbieren/SCPT/blob/main/Sources/Executables/SCPT_Static_HPC.out): `SCPT_Static_HPC.out`

You can also compile it yourself using the provided [source](https://github.com/mjbieren/SCPT/tree/main/Sources/main) code.

For an example script, see: [SCPT.sh]()

---

## ⚙️ Command-Line Options

With Gene IDs e.g. >Species1-GeneID_123
```
SCPT.out -f <FastaFilesPath> -r <OutputFolderPath> -t <TaxonomicGroupFile>
```

Without Gene IDs e.g. >Species1
```
SCPT.out -f <FastaFilesPath> -r <OutputFolderPath> -t <TaxonomicGroupFile> -s
```

### Arguments

| Flag | Description |
|------|-------------|
| `-f` | **Path to input FASTA files**. Provide a folder containing your `.fa` or `.fasta` files. **(Required)** |
| `-r` | **Path to the output folder**. Where the summary result will be saved. **(Required)** |
| `-t` | **Taxonomic group file**. Used to map and count species across input files. Format should be consistent with other tools (one group per line, species separated by commas). **(Required)** |
| `-s` | Optional flag. If set, the program will interpret FASTA headers as containing **only species/strain names**, not full gene IDs. |

---

## 🧪 Example Run

```
SCPT.out -f ./AllFastaFiles -r ./SCPT_Output -t ./TaxGroupFile.txt -s
```

This will:
* Count species occurrences from all .fasta/.fa files in AllFastaFiles
* Use TaxGroupFile.txt to identify taxonomic groups
* Output a .tsv file in SCPT_Output/

#### Taxonomic Group file
This program uses a taxonomic group file to identify the differences between species and species headers.  See the folder [TaxonomicGroupFiles](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/upload/main/TaxonomicGroupFiles) for examples.
The Taxonomic Group file is formatted like this:
```
SpeciesName1(HeaderName),Speciesname2(HeaderName)
SpeciesName3(HeaderName),SpeciesName4(HeaderName)
```
Each line represents a taxonomic group, and species are separated by a ",".

---

## 📄 Output
The output file will be a tab-delimited table named as follows:

```
[OutputFolder]/[Timestamp]_FastaFilesNrs_[N]_SCPT_OUTPUT.tsv
```
Where:
* Timestamp = the date and time of the run
* N = number of FASTA files processed

### Example Output Format
```
SpeciesA    187
SpeciesB    294
SpeciesC     82
...
```

## 🧬 Internal Workflow
1. Parse input:
   * Read all FASTA files in the specified folder
   * Load the taxonomic group file
2. Match & count:
   * For each FASTA header, match it to a taxonomic group
   * Increment a counter for the matching species/strain
3. Write output:
   * Save the count summary to the specified output folder as a `.tsv` file


## 📫 Contact

**Maaike Jacobine Bierenbroodspot**  
📧 maaikejacobine.bierenbroodspot@uni-goettingen.de
