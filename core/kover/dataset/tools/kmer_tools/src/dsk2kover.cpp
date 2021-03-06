/*
*	Kover: Learn interpretable computational phenotyping models from k-merized genomic data
*	Copyright (C) 2015  Alexandre Drouin & Gaël Letarte St-Pierre
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <gatb/gatb_core.hpp>
#include "kl_64.h"
#include "kl_128.h"
#include "kl_192.h"
#include "kl_256.h"
#include "progress.h"

static const char* STR_KMER_LENGTH= "-kmer-length";
static const char* STR_FILTER= "-filter";
static const char* STR_COMPRESSION= "-compression";
static const char* STR_CHUNK_SIZE= "-chunk-size";
static const char* STR_NB_GENOMES= "-nb-genomes";
/********************************************************************************/
class DSK2Kover : public Tool
{
private:
public:

    /** */
    DSK2Kover () : Tool ("DSK2Kover")
    {
		// Adding command line options
        getParser()->push_front(new OptionOneParam (STR_URI_OUTPUT, "output file",           true));
        getParser()->push_front(new OptionOneParam (STR_URI_FILE,   "file generated by dsk", true));
        getParser()->push_front(new OptionOneParam (STR_FILTER, "filter", false, "nothing"));
        getParser()->push_front(new OptionOneParam (STR_KMER_LENGTH, "kmer-length", false, "31"));
        getParser()->push_front(new OptionOneParam (STR_COMPRESSION, "compression", false, "4"));
        getParser()->push_front(new OptionOneParam (STR_CHUNK_SIZE, "chunk size", false, "100000"));
        getParser()->push_front(new OptionOneParam (STR_NB_GENOMES,   "Number of genomes", true));
    }

    /** */
    void execute ()
    {
        // Initializing progress bar
        bool progress;
        getInput()->getStr(STR_VERBOSE) == "True" ? progress = true : progress = false;
        ProgressBar bar(2 * (getInput()->getInt(STR_NB_GENOMES)) + 2, progress, "dsk2kover");
        
        // Launching the adequate KmerLister
		size_t kmer_size = getInput()->getInt(STR_KMER_LENGTH);
		if (kmer_size <= 32)
		{
			KmerLister64 tool(kmer_size);
			tool.analyse(getInput()->getStr(STR_URI_FILE), getInput()->getStr(STR_URI_OUTPUT), getInput()->getStr(STR_FILTER), getInput()->getInt(STR_COMPRESSION), getInput()->getInt(STR_CHUNK_SIZE), bar);
		}
		else if (kmer_size <= 64)
		{
			KmerLister128 tool(kmer_size);
			tool.analyse(getInput()->getStr(STR_URI_FILE), getInput()->getStr(STR_URI_OUTPUT), getInput()->getStr(STR_FILTER), getInput()->getInt(STR_COMPRESSION), getInput()->getInt(STR_CHUNK_SIZE), bar);
		}
				else if (kmer_size <= 96)
		{
			KmerLister192 tool(kmer_size);
			tool.analyse(getInput()->getStr(STR_URI_FILE), getInput()->getStr(STR_URI_OUTPUT), getInput()->getStr(STR_FILTER), getInput()->getInt(STR_COMPRESSION), getInput()->getInt(STR_CHUNK_SIZE), bar);
		}
		else if (kmer_size <= 128)
		{
			KmerLister256 tool(kmer_size);
			tool.analyse(getInput()->getStr(STR_URI_FILE), getInput()->getStr(STR_URI_OUTPUT), getInput()->getStr(STR_FILTER), getInput()->getInt(STR_COMPRESSION), getInput()->getInt(STR_CHUNK_SIZE), bar);
		}
		else
		{
			std::cout << "K-mers size is limited to 128" << std::endl;
		}
    }
};


/********************************************************************************/
int main (int argc, char* argv[])
{
    try
    {
        DSK2Kover().run (argc, argv);
    }
    catch (Exception& e)
    {
        std::cout << "EXCEPTION: " << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}
