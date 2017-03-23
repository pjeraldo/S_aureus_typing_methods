# Supplementary information

This repository contains code used for the analysis described in "Comparison of Two Whole-Genome Sequencing Methods for Analysis of Three Methicillin-Resistant *Staphylococcus aureus* Outbreaks."

The published code includes the following:

- **De_novo_genome_assembly_pipeline.ipynb**: An IPython/Jupyter notebook describing the *de novo* assembly pipeline used in the isolates described in the pipeline. For more details, please inspect [the notebook](De_novo_genome_assembly_pipeline.ipynb).
- **median_filter.cpp**: C++ code used in the *de novo* assembly pipeline for a filter of fastq reads based on the median phred score of the reads. The cutoff is hardcoded at phred=30. Usage:
```bash
median_filter input.fastq > output.fastq
```
- **extract_paired_reads.cpp**: C++ code used in the *de novo* assembly pipeline to split the paired reads from single reads in a single fastq file, based on the reads ID. Two reads are considered paired if they are consecutive in the file and have the same IDs. Otherwise, they are considered orphaned, and output as single reads. Usage:
```bash
extract_paired_reads input.fastq
```
Two output files will be written: `input.fastq.pe` with interleaved paired reads, and `input.fastq.se` with the leftover single reads.

- **VCF2VariantMatrix**: This directory contains the Java program used to calculate a distance matrix from a multi-sample VCF file, as used in this manuscript. For more details, see inside the [directory](VCF2VariantMatrix).

## License information

Unless stated otherwise, the code is licensed under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Copyright 2017, Mayo Foundation for Medical Education and Research.

## Author information

The code in this repository was written by Patricio Jeraldo and Daniel Quest.

## Manuscript information
The manuscript "Comparison of Two Whole-Genome Sequencing Methods for Analysis of Three Methicillin-Resistant *Staphylococcus aureus* Outbreaks" is currently undergoing peer-review. Citation information will be written here when available.
