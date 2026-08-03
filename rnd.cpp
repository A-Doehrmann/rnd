/******************************************************************************
 $Author: adoehrmann $
 $Revision: 15 $
 $Date: 2024-08-01 10:23:03 +0200 (Do, 01 Aug 2024) $
 description: generates different test patterns that can be used during testing
 ******************************************************************************/

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

//non std includes
#include "global_const_data.h"
#include "typedefs.h"
#include "logger.h"
#include "rnd.h"

//local variables
//seeding MUST be done after main() has been called since it cannot be guaranteed that
//all necessary objects in the generator are set up yet
static long long int used_seed{0};// = LIB::Reseed();
//use random engine mersenne twister
static mt19937 rnd_generator;

const string alphanum_string = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/******************************************************************************
 * Reseed
 ******************************************************************************/
long long int LIB::Reseed()
{
   long long int retVal = 0;
   system_clock::time_point tp = system_clock::now();
   used_seed = tp.time_since_epoch().count();
   rnd_generator.seed(used_seed);
   retVal = used_seed;
   return retVal;
}

/******************************************************************************
 * SetSeed
 ******************************************************************************/
void LIB::SetSeed(long long int fixed_seed)
{
   used_seed = fixed_seed;
   rnd_generator.seed((unsigned int)used_seed);
}

/******************************************************************************
 * GetSeed
 ******************************************************************************/
long long int LIB::GetSeed()
{
   return used_seed;
}

/******************************************************************************
 * GenRndString
 ******************************************************************************/
string LIB::GenRndString(size_t len, size_t ascii_pos_min, size_t ascii_pos_max)
{
   string retVal = "";
   for (size_t i = 0; i < len; ++i)
   {
      retVal.push_back((char) (GenRndInt(ascii_pos_min, ascii_pos_max)));
   }
   return retVal;
}

/******************************************************************************
 * GenRndString
 ******************************************************************************/
string LIB::GenRndString(size_t len, const string& allowed_chars)
{
   string retVal = "";
   size_t max_index = allowed_chars.size() - 1;
   for (size_t i = 0; i < len; ++i)
   {
      size_t index = GenRndInt(0, max_index);
      if (index < allowed_chars.size())
      {
         retVal.push_back(allowed_chars[index]);
      }
   }
   return retVal;
}

/******************************************************************************
 * GenRndInt
 ******************************************************************************/
long long int LIB::GenRndInt(long long int min, long long int max)
{
   long long int retVal = 0;
   //allocate a distribution object
   uniform_int_distribution<long long int> distribution(min, max);
   //generate random number
   retVal = distribution(rnd_generator);
   return retVal;
}

/******************************************************************************
 * GenRndBool
 ******************************************************************************/
bool LIB::GenRndBool()
{
   bool retVal = false;
   if (GenRndInt(0, 1) == 0)
   {
      retVal = false;
   }
   else
   {
      retVal = true;
   }
   return retVal;
}

/******************************************************************************
 * GenUniqueTimebasedStr
 ******************************************************************************/
string LIB::GenUniqueTimebasedStr(size_t chiffre_length)
{
   string retVal;
   //generate a unique string -> combination of current time and random value
   time_t time_since_epoch = time(nullptr);
   tm timestamp_tm = *(localtime(&time_since_epoch));
   retVal.resize(64);
   size_t num_bytes = strftime(&retVal[0], retVal.size(), "%Y%m%d%H%M%S", &timestamp_tm);
   retVal.resize(num_bytes);
   //add random key
   retVal += "_";
   retVal += LIB::GenRndString(chiffre_length, (int)'A', (int)'Z');;
   return retVal;
}


