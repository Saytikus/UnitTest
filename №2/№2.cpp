#include <UnitTest++/UnitTest++.h>
#include "/home/stud/C++Projects/L3/№2/№2/Methods.h"
#include "/home/stud/C++Projects/L3/№2/№2/Methods.cpp"

SUITE(KeyTests) {
    TEST(ValidKey) {
        CHECK_EQUAL("54321", Methods(5).Encrypt("12345"));
    }
    TEST(SmallKey) {
        CHECK_THROW(Methods(1).Encrypt("12345"), Mymethods_error);
    }
    TEST(HugeKey) {
        CHECK_THROW(Methods(1256).Encrypt("12345"), Mymethods_error);
    }
    TEST(ShortStringToKey) {
        CHECK_THROW(Methods(11).Encrypt("12345"), Mymethods_error);
    }
}

struct KeyB_fixture {
    Methods* p;
    KeyB_fixture()
    {
        p = new Methods(5);
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTests) {
    TEST_FIXTURE(KeyB_fixture, UpperCaseANDDigits) {
        CHECK_EQUAL("5X49382716", p->Encrypt("123456789X"));
    }
    TEST_FIXTURE(KeyB_fixture, UpperCase) {
        CHECK_EQUAL("NVAHATORLJTO", p->Encrypt("JOHNTRAVOLTA"));
    }
    TEST_FIXTURE(KeyB_fixture, Digits) {
        CHECK_EQUAL("549382716", p->Encrypt("123456789"));
    }
    TEST_FIXTURE(KeyB_fixture, PunctuationsANDSpaces) {
        CHECK_THROW(p->Encrypt("! @#1 2 34 56 78 9 X"), Mymethods_error);
    }
    TEST_FIXTURE(KeyB_fixture, LowerCase) {
        CHECK_THROW(p->Encrypt("johntravolta"), Mymethods_error);
    }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->Encrypt(""), Mymethods_error);
    }
}

SUITE(DecryptTests) {
    TEST_FIXTURE(KeyB_fixture, UpperCaseANDDigits) {
        CHECK_EQUAL("123456789X", p->Decrypt("5X49382716"));
    }
    TEST_FIXTURE(KeyB_fixture, UpperCase) {
        CHECK_EQUAL("JOHNTRAVOLTA", p->Decrypt("NVAHATORLJTO"));
    }
    TEST_FIXTURE(KeyB_fixture, Digits) {
        CHECK_EQUAL("123456789", p->Decrypt("549382716"));
    }
    TEST_FIXTURE(KeyB_fixture, Spaces) {
        CHECK_THROW(p->Decrypt("NVA HA TOR LJTO"), Mymethods_error);
    }
    TEST_FIXTURE(KeyB_fixture, Punctuations) {
        CHECK_THROW(p->Decrypt("&%NVAHATO%(LJTO"), Mymethods_error);
    }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->Decrypt(""), Mymethods_error);
    }
}

int main() {
    return UnitTest::RunAllTests();
}