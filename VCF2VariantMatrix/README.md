# VCF2VariantMatrix

This program takes in a multi-sample VCF file, and outputs a distance matrix, where each unit distance is a qualified single-nucleotide variant.

## Installation

Copy the `conf` and `lib` directories into the directory of your choice. The `micro_VCF2VariantMatrix` script can be located anywhere, but we suggest to keep the organization the same as is in this directory, adding the directory to the system's `PATH`.

Before using the program, define the `MICRO_HOME` environment variable to the directory that holds the `conf` and `lib` directories. For example, if the directory is called `/path/to/my/VCF2VariantMatrix/directory`, then type
```bash
export MICRO_HOME=/path/to/my/VCF2VariantMatrix/directory
```
in your bash shell. Adjust your command if you use a different shell.

## Usage

```bash
micro_VCF2VariantMatrix [--rfile <region file>] [--rthresh <region threshold>]
[--delta <filter delta>] [--token <token symbol>]
[--filter <filter value>] [--help] --infile <input file (VCF)> [--log]
--output <output file (matrix)>
```
### Options

#### Required

`-i, --infile <input file (VCF)>`  
                The path to the multi-sample VCF file

`-o, --output <output file (matrix)>`  
                                The output matrix file  

#### Optional
`-r, --rfile <region file>`  
Genomic region file.  If the genomic region file is used, it provides background frequencies
                for variants based on technical replicate data.  This allows the software to filter out
                problematic regions based on the number of occurances of SNPs in the problem areas

`-s, --rthresh <region threshold>`  
                Genomic region file threshold.  Variants above this threshold in the region file will flag the
                genomic region to be masked, regions below this threshold will not be masked.  The threshold
                is in terms of number of SNPs/region length.  This param is required when using a region file.
                (default=0.0001)

`-d, --delta <filter delta>`  
                When two variants are compared, the delta that is allowed to call them the same (regardless of
                filter threshold) e.g. if delta=2 then variants with value 3 and 5 will be considered the same
                (but not 3 and 7) even if the filter value was 4.  Default=20

`-t, --token <token symbol>`  
                Token in the format column that the filter value will be applied to, e.g. DP, AD ect, this
                MUST be defined if the filter argument is defined!

`-f, --filter <filter value>`  
                Filter value; so samples under this value will be interpreted as NOT variants (default = 20)

`-h, --help`  
                Print this message.



`-l, --log`  
                Generate the log file 'log.txt'. By default, the log file is not generated.
