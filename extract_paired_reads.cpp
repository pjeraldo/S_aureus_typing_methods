#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

struct fastq_record {
  string id;
  string seq;
  string div;
  string qual;
  bool defined;
};

fastq_record make_record(const string& id, const string& seq, const string& div, const string& qual){
  fastq_record new_record;
  new_record.id= id;
  new_record.seq= seq;
  new_record.div= div;
  new_record.qual= qual;
  new_record.defined= true;
  
  return new_record;
}

void split(vector<string>& elems, const string& s, const char delim ) {
    stringstream ss(s);
    string item;
    while(std::getline(ss, item, delim)) {
      if(item.compare("") != 0){
        elems.push_back(item);
      }
    }
}

bool is_pair(const fastq_record& read1, const fastq_record& read2){
  vector<string> subparts1, subparts2;
  
  if(read1.id.substr(read1.id.length() - 2) == "/1" && read2.id.substr(read2.id.length() - 2) == "/2"){
    split(subparts1, read1.id, '/');
    split(subparts2, read2.id, '/');
    
    if(subparts1[0] == subparts2[0]){
      return true;
    }
  }
  return false;
}
    


void write_record(ofstream& out, const fastq_record& rec){
  out << rec.id << "\n";
  out << rec.seq << "\n";
  out << rec.div << "\n";
  out << rec.qual << "\n";
}
  
int main(int argc, char const **argv){
  
  
  ifstream in_file;
  ofstream pe_file, se_file;
  string in_filename;
  string pe_filename, se_filename;
  in_filename= string(argv[1]);
  pe_filename= in_filename + ".pe";
  se_filename= in_filename + ".se";
  string id_line, seq_line, div_line, qual_line;
  in_file.open(in_filename.c_str(), ios::in);
  pe_file.open(pe_filename.c_str(), ios::out);
  se_file.open(se_filename.c_str(), ios::out);
  fastq_record rec_current, rec_previous;
  rec_previous.defined= false;
  
  unsigned long index=0, pairs=0, singletons=0;
  
   
  cerr << "Splitting reads for file " << in_filename << endl;
  while(!in_file.eof()){
    /*if(index % 100000 == 0 && index > 0){
      cerr << "..." << index << endl;
    }*/
    if(!getline(in_file,id_line,'\n')) break;
    if(!getline(in_file,seq_line,'\n')) break;
    if(!getline(in_file,div_line,'\n')) break;
    if(!getline(in_file,qual_line,'\n')) break;
    rec_current= make_record(id_line, seq_line, div_line, qual_line);
    
    if(rec_previous.defined){
      if(is_pair(rec_previous, rec_current)){
	write_record(pe_file, rec_previous);
	write_record(pe_file, rec_current);
	index += 2;
	pairs += 1;
	rec_current.defined= false;
      }
      else {
	write_record(se_file, rec_previous);
	index += 1;
	singletons += 1;
      }
    }
    
    rec_previous= rec_current;
    rec_current.defined= false;
  }
  // Last record
 if(rec_previous.defined){
   write_record(se_file, rec_previous);
   index += 1;
   singletons += 1;
 }
 
 in_file.close();
 pe_file.close();
 se_file.close();
 
 //Debriefing
 cerr << "Read " << index << " sequences: " << endl << pairs << " pairs and " << singletons << " singletons." << endl;
 cerr << endl << "Written to " << pe_filename << " and " << se_filename << endl;
  
  
  return EXIT_SUCCESS;
  
}