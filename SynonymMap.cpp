#define BOOST_HAS_HASH 
#include <boost/serialization/hash_map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/filesystem/fstream.hpp>
#include <hash_map>

using namespace stdext;

class SynonymMap{
 private:
    string new_filename = p.leaf() + ".foo";
    stdext::hash_map<int, string[]> synMap; 

 public:
    SynonymMap(){

    }

     friend class boost::serialization::access;

     template <class Archive>
     void serialize(Archive &ar, const unsigned int version)
     {
        ar & myClassHashTable;
     }
};

void SynonymMap::serializedToDisk()
{
      boost::filesystem::path finalPath("SynonymMap.ser");
      // code to create  boost::filesystem::ifstream ofs object
      boost::archive::text_oarchive oa(ofs);
      oa << myClassHashTable;
}
void SynonymMap::restoreFromDisk()
{
     boost::filesystem::path finalPath(SOME_CONSTANT);
    // code to create  boost::filesystem::ifstream ifs object
      boost::archive::text_iarchive ia(ifs);
      ia >> myClassHashTable;
}



int main(int argc, char **argv) {
	


	//Save< map<int, customType> >("test.map", yourMap); 

	return 0;
}