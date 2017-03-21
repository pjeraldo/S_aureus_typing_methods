/*

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2017, Mayo Foundation for Medical Education and Research.

*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const int QUAL_THRESHOLD= 30;

double median(vector<int>& qual_vector){
    int size= qual_vector.size();
    sort(qual_vector.begin(), qual_vector.end());
    return size % 2 ? qual_vector[size/2] : 0.5*(qual_vector[size/2-1] + qual_vector[size/2]);
}

int to_ascii_33(char c){
	return int(c) - 33;
}

void ascii_to_int(vector<int>& qual_vector, const string& quals){
	qual_vector.clear();
	qual_vector.resize(quals.length(),0);
	transform(quals.begin(),quals.end(),qual_vector.begin(), to_ascii_33);
	assert(qual_vector.size() == quals.length());
}

int main(int argc,char **argv)
{
    string name, seq, name2, qual;
    int good_reads= 0;
    int bad_reads= 0;
    ifstream in2(argv[1], ios::in);
    vector<int> qual_vector;
    while(!in2.eof())
    {
        if(!getline(in2,name,'\n')) break;
        if(!getline(in2,seq,'\n')) break;
        if(!getline(in2,name2,'\n')) break;
        if(!getline(in2,qual,'\n')) break;
	ascii_to_int(qual_vector, qual);
	double qual_median= median(qual_vector);
	if(qual_median >= QUAL_THRESHOLD){
        	cout << name << "\n" << seq << "\n" << name2 << "\n" << qual << '\n';
		good_reads += 1;
	}
	else {
		bad_reads+= 1;
	}
    }
    in2.close();
    //Summary
    cerr << "Number of good reads: " << good_reads << endl;
    cerr << "Number of bad reads: " << bad_reads << endl;
    return 0;
}
