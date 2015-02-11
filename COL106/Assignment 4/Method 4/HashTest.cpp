#include <iostream>
#include "HashTest.h"
#include "Test.h"
#include "hashing.h"
#include "HashTable.h"
#include "WordCompression.h"
#include "WordDecompression.h"

bool RunAllTests()
{
	GetValueTests();
	HashingTests();
	HashTableTests();
	InitialisingAndInsertingTests();
	WordBestTests();
	HashInsertTests();
	HashCompDeTests();
	ASCITests();
}

bool GetValueTests()
{
	Test t("Get Value of char tests");
	t.VerifyTrue(getCharValue("abc",0)==2, "Value should be 2");
	t.VerifyTrue(getCharValue("abcz",3)==27, "Value should be 27");
	t.VerifyTrue(getCharValue("abcj",3)==11, "Value should be 11");
	t.VerifyTrue(getCharValue("Abcj",0)==28, "Value should be 28");
	t.VerifyTrue(getCharValue("abcZ",3)==53, "Value should be 53");
	t.VerifyTrue(getCharValue("abCj",2)==30, "Value should be 30");
	t.VerifyTrue(getCharValue("ab Cj",2)==1, "Value should be 1");
	t.VerifyTrue(getCharValue("ab.Cj",2)==54, "Value should be 54");
	return t.isPassed();
}

bool HashingTests()
{
	Test t("Hashing Tests");
	t.VerifyTrue(getHashKey("a",10001)==2,"Value for a should be 2");
	t.VerifyTrue(getHashKey("ab",10001)==113,"Value for ab should be 113");
	t.VerifyTrue(getHashKey("ba",10001)==167,"Value for ba should be 167");
	// cout <<getHashKey("RUZ",10001)<<"\n";
	return t.isPassed();
}

bool HashTableTests()
{
	Test t("Hash Table Tests");
	HashTable* h1=new HashTable(7919);
	t.VerifyTrue(not(h1->isFull()),"Hash Table should not be full");
	t.VerifyTrue((h1->getSize()==54),"Hash Table size should be 54");
	long s1=h1->Insert("ab");
	t.VerifyTrue(not(h1->isFull()),"Hash Table should not be full");
	t.VerifyTrue((h1->getSize()==55),"Hash Table size should be 55");
	t.VerifyTrue((h1->Find("a")==2),"a is at 2");
	t.VerifyTrue((h1->Find("ab")==113),"Position for ab should be 121");
	t.VerifyTrue((h1->Find("abc")==-1),"Position for abc should be -1");
	return t.isPassed();
}

bool InitialisingAndInsertingTests()
{
	Test t("Hast Table initialisation and Inserting Tests");
	HashTable* hashed=Initialize(7919);
	t.VerifyTrue(hashed->getSize()==54,"Size should be 54 initially");
	t.VerifyTrue(hashed->Find("Z")==53,"Z should be at 53");
	t.VerifyTrue(hashed->Find("AB")==-1,"AB should not exist");
	return t.isPassed();
}

bool WordBestTests()
{
	Test t("Hash Table Finding best word tests");
	HashTable* hashed=Initialize(7919);
	t.VerifyTrue(getBest("abcd",0,hashed)==2,"Best for a should be 1");
	t.VerifyTrue(getBest("abcd",1,hashed)==2,"Best for b should be 2");
	long coded=getCode("ab",hashed);
	t.VerifyTrue(getBest("abcd",0,hashed)==3,"Best for a should be 650");
	return t.isPassed();	
}

bool HashInsertTests()
{
	Test t("Hash Table Inserting Tests");
	HashTable* hashed=Initialize(7919);
	int till1=getBest("aabcd",0,hashed);
	t.VerifyTrue(till1==2,"Position till should be 2");
	string s2="aabcd";
	int inserted1=InsertInHash("aabcd",0,till1,hashed);
	t.VerifyTrue(hashed->getSize()==55,"Size should be 55");
	t.VerifyTrue(inserted1==2,"Position inserted should be 2");
	hashed=Initialize(7919);
	iterated("aaabbbbbbaaba",hashed);
	hashed=Initialize(7919);
	iterated("aaabbbbbbaabaaba",hashed);
	return t.isPassed();
}

bool HashCompDeTests()
{
	Test t("Hash Table compression and decompression tests");
	HashTable* hashed=Initialize(7919);
	vector<int> convertedform=iterated("aaabbbbbbaabaaba", hashed);
	t.VerifyTrue(mergeAll(convertedform,hashed).compare("aaabbbbbbaabaaba")==0,"Test1");
	hashed=Initialize(7919);
	convertedform=iterated("aaabbbbbbaabaaba asdkjhqwsadf sdaf. .asdf .sdjhdsaf kasdkfewofsdfa qoa . asdflk.ew .l", hashed);
	t.VerifyTrue(mergeAll(convertedform,hashed).compare("aaabbbbbbaabaaba asdkjhqwsadf sdaf. .asdf .sdjhdsaf kasdkfewofsdfa qoa . asdflk.ew .l")==0, "Test 2");
	hashed=Initialize(7919);
	convertedform=iterated("Trying out this completely new and random string. Lets see what the code can do to it or if it fails entirely.",hashed);
	t.VerifyTrue(mergeAll(convertedform,hashed).compare("Trying out this completely new and random string. Lets see what the code can do to it or if it fails entirely.")==0,"Test3");
	return t.isPassed();
}

bool ASCITests()
{
	Test t("ASCI conversion tests");
	t.VerifyTrue(ASCIval(97).compare("a")==0,"Asci for 97 should be a");
	t.VerifyTrue(ASCIval(45).compare("-")==0,"Asci for 45 should be -");
	t.VerifyTrue(ASCIval(10).compare("\n")==0,"Asci for 10 should be \n");
	return t.isPassed();
}

int main()
{
	RunAllTests();
	return 0;
}