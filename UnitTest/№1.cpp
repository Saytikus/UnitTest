#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/L3/¹1/¹1/modAlphaCipher.h"
#include "/home/stud/C++Projects/L3/¹1/¹1/modAlphaCipher.cpp"

SUITE(KeyTests)
{
    TEST(ValidKey) {
        CHECK_EQUAL("ÁÂÃÁÂ", modAlphaCipher("ÁÂÃ").encrypt("ÀÀÀÀÀ"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("BCDEF", modAlphaCipher("ÁÂÃÄÅ¨ÆÇ").encrypt("ÀÀÀÀÀ"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("ÁÂÃÁÂ", modAlphaCipher("áâã").encrypt("ÀÀÀÀÀ"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Á1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Á,Â"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Á Â"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Á");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTests)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ÔÌÔËÏÍÏÑÛÀÅÔÂÈÆÌÆÎÚÊ", p->encrypt("ÓËÓÊÎÌÎÐÜßÄÓÁÇÅËÅÍÛÉ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ÔÌÔËÏÍÏÑÛÀÅÔÂÈÆÌÆÎÚÊ", p->encrypt("óëóêîìîðüÿäóáçåëåíûé"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_THROW(p->encrypt("Ó ËÓÊÎÌÎÐÜß ÄÓÁ ÇÅËÅÍÛÉ-_-"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_THROW(p->encrypt("ÍÎÂÛÉ 2023 ÃÎÄ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123-100=23"), cipher_error);
    }
}

SUITE(DecryptTests)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ÓËÓÊÎÌÎÐÜßÄÓÁÇÅËÅÍÛÉ", p->decrypt("ÔÌÔËÏÍÏÑÛÀÅÔÂÈÆÌÆÎÚÊ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("ôìôëïíïñûàåôâèæìæîúê"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceAndPunctString) {
        CHECK_THROW(p->decrypt("ÔÌ ÔËÏ ÍÏÑ ÛÀÅÔÂÈÆ ÌÆ ÎÚÊ!!,/"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ÔÌÔË55ÏÍÏÑÛ888ÀÅÔÂÈÆÌÆ11ÎÚÊ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, OnlyDigitsString) {
        CHECK_THROW(p->decrypt("22427118"), cipher_error);
    }
}

int main(int argc, char** argv) {
    return UnitTest::RunAllTests();
}