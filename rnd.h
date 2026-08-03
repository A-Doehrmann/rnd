/******************************************************************************
 * $Author: adoehrmann $
 * $Revision: 15 $
 * $Date: 2024-08-01 10:23:03 +0200 (Do, 01 Aug 2024) $
 * description: generates different test patterns that can be used during testing
 ******************************************************************************/
#ifndef RND_TEST_DATA_H
#define RND_TEST_DATA_H

extern const string alphanum_string;

namespace LIB
{
   /******************************************************************************
    * Reseed
    * Reseed the Random module
    * returns the used seed value - careful not to downcast it to an int, you will
    * loose information
    ******************************************************************************/
   long long int Reseed();

   /******************************************************************************
    * SetSeed
    * set a fixed Seed value
    ******************************************************************************/
   void SetSeed(long long int fixed_seed);

   /******************************************************************************
    * GetSeed
    ******************************************************************************/
   long long int GetSeed();

   /******************************************************************************
    * GenRndString
    * Generates a random string of length len
    * len  : size of the random string that will be put out; ASCII Range 33 to 127
    ******************************************************************************/
   string GenRndString(size_t len, size_t ascii_pos_min, size_t ascii_pos_max);
   string GenRndString(size_t len, const string& allowed_chars = alphanum_string);

   /******************************************************************************
    * GenRndInt
    * Generates a random integer in the specified range
    ******************************************************************************/
   long long int GenRndInt(long long int min, long long int max);

   /******************************************************************************
    * GenRndBool
    * Generates a random bool value
    ******************************************************************************/
   bool GenRndBool();

   /******************************************************************************
    * GenUniqueTimebasedStr
    * Can be used to generate unique strings that contain a timecode
    ******************************************************************************/
   string GenUniqueTimebasedStr(size_t chiffre_length = 10);
}

#endif