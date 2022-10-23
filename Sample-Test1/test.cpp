#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using std::cout;
using std::endl;

class Check 
{
	int val;
public:
	Check() : val(0) {}
	void setValue(int newVal) { this->val = newVal; }
	int getValue() { return this->val; }
};

struct TF : public testing::Test //TF = Test Features
{
	//Arrange
	Check* c1 ;
	void SetUp() { cout << "SETUP" << endl;  c1 = new Check(); }
	void TearDown() { cout << "TEARDOWN" << endl;  delete c1; }
};

TEST_F(TF, TestName1) 
{

	//Act
	c1->setValue(101);

	//Assert
	ASSERT_EQ(c1->getValue(), 100);

}

TEST_F(TF, TestName2)
{

	//Act
	c1->setValue(200);

	//Assert
	EXPECT_EQ(c1->getValue(), 200);

}
// This is a test for my XYZ function
TEST(TestCaseName, TestName1)
{
	/*
	std::cout << "***Scratch Pad Area***" << std::endl;
	cout << "Test options: \n ASSERT(_EQ, _NE, _LT, _LE, _GT, _GE) \n Equal, Not Equal, Less than, Less Than or Equal, Greater Than, Greater than or Equal " << endl;
	EXPECT_EQ(1, 1);
	ASSERT_TRUE(100 == 100);
	cout << "*** no fatal failure***" << endl;
	EXPECT_EQ(100, 101);
	cout << "*** non fatal failure ***" << endl;
	*/

}