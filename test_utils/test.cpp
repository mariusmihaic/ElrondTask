#include "pch.h"


TEST(Base64, decode)
{
  std::string keytotal = "MWY0ZGQ4YjdkMThiNWQwNzg1YzlkMDgwMmVjMTRkNTUzZGJhMzU2ODEyYjg1YzdlMzQxNDM3MzM4ODQ3MjAxMDg0YTE2OGNkNGQ3ZDg2MDg4NDg2MzJkMDk3ODNkMjhhZTlhODIzOTAwNzc5Mjk1NjY3NTdlMjU1OTZmZTk2NDc";
  std::string const decoded = util::base64_decode(keytotal);
  std::vector<char> decoded_array = util::hexToBytes(decoded);


  std::string textBase64 = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
  std::string expectedDecoded = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
  std::string decodedBase64Txt = util::base64_decode(textBase64);

  EXPECT_EQ(expectedDecoded, decodedBase64Txt);

}

TEST(Base64, encode)
{
  std::string text = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
  std::string expectedEncoded = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
  std::string encodedBase64Txt = util::base64_encode(text);

  EXPECT_EQ(expectedEncoded, encodedBase64Txt);
}

TEST(Hex, toBytes)
{
  std::string textHex = "0A11f4C";

  std::vector<char> expectedBytes;
  expectedBytes.push_back(char(10)); // 0A -> 10
  expectedBytes.push_back(char(17)); // 11 -> 17
  expectedBytes.push_back(char(244));// f4 -> 244
  expectedBytes.push_back(char(12)); // C  -> 12

  std::vector<char> bytes = util::hexToBytes(textHex);

  EXPECT_EQ(bytes, expectedBytes);
}

