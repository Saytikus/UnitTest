#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/L3/�1/�1/modAlphaCipher.h"
#include "/home/stud/C++Projects/L3/�1/�1/modAlphaCipher.cpp"

SUITE(KeyTests)
{
    TEST(ValidKey) {
        CHECK_EQUAL("�����", modAlphaCipher("���").encrypt("�����"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("BCDEF", modAlphaCipher("����Ũ��").encrypt("�����"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("�����", modAlphaCipher("���").encrypt("�����"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("�1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("�,�"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("� �"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("�");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTests)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("��������������������", p->encrypt("��������������������"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("��������������������", p->encrypt("��������������������"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_THROW(p->encrypt("� ��������� ��� �������-_-"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_THROW(p->encrypt("����� 2023 ���"), cipher_error);
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
        CHECK_EQUAL("��������������������", p->decrypt("��������������������"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("��������������������"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceAndPunctString) {
        CHECK_THROW(p->decrypt("�� ��� ��� ������� �� ���!!,/"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("����55�����888��������11���"), cipher_error);
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