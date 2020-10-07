#include "string_t.h"
#include <string.h>
#include <stdio.h>
#define PRINT_TEST(X) ((X)? printf("%-20s: PASS\n",__func__):printf("%-20s :FAILED\n",__func__))



/*=================================== tests ===================================*/

void testDefCTOR();
void testDefCTOR2();

void testCTORFromChar();
void testCTORFromChar2();

void testCopyCTOR();
void testCopyCTOR2();

void testAssignment();
void testAssignment2();

void testLength();
void testLength2();
void testLength3();

void testSet();
void testSet2();

void testGet();

void testCompare();
void testCompare2();
void testCompare3();


void testLower();
void testUpper();

void testPrepend();
void testPrependFromString();

void testAddFromStr();
void testAddFromChar();

void testWrite();
void testRead();

void testNumOfElement();

void testOp();
void testCapacity();

void testCaseSen();
void testCaseSen2();

void testfirstOcc();
void testfirstOcc2();
void testfirstOcc3();
void testfirstOcc4();
void testfirstOcc5();

void testLastOcc();
void testLastOcc2();
void testLastOcc3();
void testLastOcc4();




/*=============================================================================*/

int main()
{
	testDefCTOR();
    testDefCTOR2();

    testCTORFromChar();
    testCTORFromChar2();

    testCopyCTOR();
    testCopyCTOR2();

    testAssignment();
    testAssignment2();

    testLength();
    testLength2();
    testLength3();
 
    testSet();
    testSet2();

    testGet();
 
    testCompare(); 
    testCompare2();
    testCompare3();
    
    testLower();
    testUpper();
    
    testPrepend();
    testPrependFromString();
    
    testAddFromStr();
    testAddFromChar();

    testNumOfElement();

    testOp();
    testCapacity();

    testCaseSen();
    testCaseSen2();

    testfirstOcc();
    testfirstOcc2();
    testfirstOcc3();
    testfirstOcc4();
    testfirstOcc5();

    testLastOcc();
    testLastOcc2();
    testLastOcc3();
    testLastOcc4();

    testWrite();
    testRead();


    return 0;

}


void testDefCTOR()
{
    string_t str1;
    const char *test = str1.getString();
    PRINT_TEST(test != NULL);
}

void testDefCTOR2()
{
    string_t str2;
    int test = str2.length();
    PRINT_TEST(test == 0);
}

void testCTORFromChar()
{
    string_t str1("stringgg");
    int test = str1.length();
    PRINT_TEST(test == 8);
}

void testCTORFromChar2()
{
    string_t str1("stringgg");
    const char *test = str1.getString();
    PRINT_TEST(strcmp(test, "stringgg") == 0);
}

void testCopyCTOR()
{
    string_t str1("cpyString");
    string_t& ref = str1;
    string_t str2(ref);
    int test = str2.length();
    PRINT_TEST(test == 9);
}

void testCopyCTOR2()
{
    string_t str1("cpyString");
    string_t& ref = str1;
    string_t str2(ref);
    const char *test = str2.getString();
    PRINT_TEST(strcmp(test, "cpyString") == 0);
}

void testAssignment()
{
    string_t str1("cpyString");
    string_t str2 = str1;
    PRINT_TEST(strcmp(str2.getString(), "cpyString") == 0);
}

void testAssignment2()
{
    string_t str1("cpyString");
    string_t str2 = str1;
    string_t &str3 = str2; 
    PRINT_TEST(strcmp(str3.getString(), "cpyString") == 0);
}

void testLength()
{
    string_t str1("cpyString");
    string_t str2 = str1;
    PRINT_TEST(str2.length() == 9);
}

void testLength2()
{
    string_t str1("");
    string_t str2 = str1;
    PRINT_TEST(str2.length() == 0);
}

void testLength3()
{
    string_t str("my string!");
    PRINT_TEST((strcmp(str.getString(), "my string!")) == 0);
    PRINT_TEST(10 == strlen(str.getString()));
    PRINT_TEST(10 == str.length()); 
}

void testSet()
{
    string_t str1("cpyString");
    str1.setString("new");
    PRINT_TEST(str1.length() == 3);
}

void testSet2()
{
    string_t str1("cpyString");
    str1.setString("new");
    PRINT_TEST(strcmp(str1.getString(), "new") == 0);
}

void testGet()
{
    string_t str1("getString");
    const char *test = str1.getString();
    PRINT_TEST(strcmp(test, "getString") == 0);
}

void testCompare()
{
    int test = 0;
    string_t str1("first");
    string_t& ref = str1;
    string_t str2("first");
    test = str2.Compare(ref);
    PRINT_TEST(test == 0);
}

void testCompare2()
{
    string_t test1("first");
    string_t test2("second");
    int test = 0;
    test = test2.Compare(test1);
    PRINT_TEST(test == 2);
}

void testCompare3()
{
    int test = 0;
    string_t newTest1("b");
    string_t& ref = newTest1;
    string_t newTest2("a");
    test = newTest2.Compare(ref);
    PRINT_TEST(test == 1);
}

void testLower()
{
	string_t newTest1("TOLOWER");
	char test[] = "tolower";
	newTest1.LowerCase();
	PRINT_TEST(strcmp(test, newTest1.getString()) == 0);
}	

void testUpper()
{
	string_t newTest1("toupper");
	char test[] = "TOUPPER";
	newTest1.UpperCase();
	PRINT_TEST(strcmp(test, newTest1.getString()) == 0);
}	


void testPrepend()
{
	string_t newTest1("strat");
	newTest1.Prepend("new");
	PRINT_TEST(!(strcmp(newTest1.getString(),"newstrat")));
}



void testPrependFromString()
{
	string_t newTest1("strat");
	string_t newTest2("new");
	newTest1.PrependFromString(newTest2);
	PRINT_TEST(!(strcmp(newTest1.getString(),"newstrat")));
}

void testAddFromStr()
{
	string_t newTest1("strat");
	newTest1.operator+=("new");
	PRINT_TEST(!(strcmp(newTest1.getString(),"stratnew")));
}

void testAddFromChar()
{
	string_t newTest1("strat");
	string_t newTest2("new");
	newTest1.operator+=(newTest2);
	PRINT_TEST(!(strcmp(newTest1.getString(),"stratnew")));
}


void testSmallerstr()
{
	string_t A("A");
	string_t B("B");
	PRINT_TEST(A<B);
}

void testSmallerEquel1()
{
	string_t A("A");
	string_t B("B");
	PRINT_TEST(A<=B);
}

void testSmallerEquel2()
{
	string_t A("B");
	string_t B("B");
	PRINT_TEST(A<=B);
}

void testSmallerEquel3()
{
	string_t A("C");
	string_t B("B");
	PRINT_TEST(!(A<=B));
}

void Equel1()
{
	string_t A("B");
	string_t B("B");
	PRINT_TEST((A==B));
}

void Equel2()
{
	string_t A("A");
	string_t B("B");
	PRINT_TEST(!(A==B));
}

void NotEquel1()
{
	string_t A("B");
	string_t B("B");
	PRINT_TEST(!(B!=A));
}

void NotEquel2()
{
	string_t A("abcd");
	string_t B("sdsdaw");
	PRINT_TEST((A!=B));
}

void IsContain1()
{
	string_t A("abcd");
	string_t B("sdsad");
	PRINT_TEST(A.Contains(B));
}

void IsContain2()
{
	string_t A("abcd");
	string_t B("adass");
	PRINT_TEST(!(A.Contains(B)));
}


void testNumOfElement()
{
	string_t str("abcde");
    string_t str2("sdsd");
    string_t str3("assd");
    int i = str.NumOstring();
    PRINT_TEST(i == 3);
}


void testOp()
{
	string_t str("abcde");
    string_t test = str(2,5);
    PRINT_TEST(test.Compare(str) != 0); 
}


void testCapacity()
{
    string_t str1("123456789101112");
    size_t test = str1.Capacity();
    PRINT_TEST(test == 16);
}

void testCaseSen()
{
    string_t str1("ThisIsNoCaseSens");
    string_t str2("thisisnocasesens");
    int test = 0;
    test = str1.Compare(str2);
    PRINT_TEST(test == 0);

}

void testCaseSen2()
{
    string_t str1("ThisIsNoCaseSens");
    string_t str2("thisisnocasesens");
    int test = 0;
    size_t caseSen = str1.GetCaseSen();
    PRINT_TEST(caseSen == 0);
    str2.ChangeCaseSen(1);
    caseSen = str1.GetCaseSen();
    PRINT_TEST(caseSen == 1);
    test = str1.Compare(str2);
    PRINT_TEST(test == 1);
}


void testWrite()
{
	string_t str("print working\n");
    printf("\n");
    cout << str;
}


void testRead()
{
	string_t str("abcde");
    cin >> str;
    str.print();
} 


void testfirstOcc()
{
	string_t A("banana");
	int index = A.FirstOccurrence('n');
	PRINT_TEST(index == 2);	
}

void testfirstOcc2()
{
	string_t A("banana");
	int index = A.FirstOccurrence('G');
	PRINT_TEST(index == -1);	
}

void testfirstOcc3()
{
	string_t A("BANANA");
    string_t::ChangeCaseSen(1);
	int index = A.FirstOccurrence('N');
	PRINT_TEST(index == 2);	
}

void testfirstOcc4()
{
	string_t A("BANANA");
    string_t::ChangeCaseSen(1);
	int index = A.FirstOccurrence('n');
	PRINT_TEST(index == -1);	
}


void testfirstOcc5()
{
	string_t::ChangeCaseSen(0);
	string_t A("aba");
	int ind = A.FirstOccurrence('A');
	PRINT_TEST(ind == 0);
    string_t::ChangeCaseSen(0);	
}

void testLastOcc()
{
    string_t::ChangeCaseSen(0);	
	string_t A("banana");
	int index = A.LastOccurrence('n');
	PRINT_TEST(index == 4);	
}

void testLastOcc2()
{
	string_t A("banana");
	int index = A.LastOccurrence('G');
    
	PRINT_TEST(index == -1);	
}

void testLastOcc3()
{
	string_t A("BANANA");
    string_t::ChangeCaseSen(1);
	int index = A.LastOccurrence('n');
    
	PRINT_TEST(index == -1);	
}

void testLastOcc4()
{
	string_t A("BANANA");
    string_t::ChangeCaseSen(1);
	int index = A.LastOccurrence('N');
	PRINT_TEST(index == 4);	
    
}



