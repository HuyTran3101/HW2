#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

#include "TimeCode.h"


void TestConstructors()
{
    cout << "Testing Constructors" << endl;

    // Edge case: default constructor should create 0:0:0.
    TimeCode tc1;

    assert(tc1.ToString() == "0:0:0");
    assert(tc1.GetTimeCodeAsSeconds() == 0);

    TimeCode tc2(4, 15, 32);

    assert(tc2.ToString() == "4:15:32");
    assert(tc2.GetTimeCodeAsSeconds() == 15332);

    // Edge case: minutes and seconds greater than 59 should roll over.
    TimeCode tc3(3, 71, 3801);

    assert(tc3.ToString() == "5:14:21");

    // Edge case: 3600 seconds should roll over to exactly 1 hour.
    TimeCode tc4(0, 0, 3600);

    assert(tc4.ToString() == "1:0:0");

    // Test copy constructor.
    TimeCode tc5(tc2);

    assert(tc5.ToString() == "4:15:32");
    assert(tc5.GetTimeCodeAsSeconds() == tc2.GetTimeCodeAsSeconds());

    cout << "PASSED!" << endl << endl;
}


void TestGetHours()
{
    cout << "Testing GetHours" << endl;

    TimeCode tc(8, 15, 9);

    assert(tc.GetHours() == 8);

    // Edge case: rollover should correctly calculate the hours.
    TimeCode tc2(3, 71, 3801);

    assert(tc2.GetHours() == 5);

    cout << "PASSED!" << endl << endl;
}


void TestGetMinutes()
{
    cout << "Testing GetMinutes" << endl;

    TimeCode tc(8, 15, 9);

    assert(tc.GetMinutes() == 15);

    // Edge case: minutes greater than 59 should roll over into hours.
    TimeCode tc2(3, 71, 3801);

    assert(tc2.GetMinutes() == 14);

    // Edge case: exactly 60 minutes should become 0 minutes and add 1 hour.
    TimeCode tc3(1, 60, 0);

    assert(tc3.GetMinutes() == 0);

    cout << "PASSED!" << endl << endl;
}


void TestGetSeconds()
{
    cout << "Testing GetSeconds" << endl;

    TimeCode tc(8, 15, 9);

    assert(tc.GetSeconds() == 9);

    // Edge case: seconds greater than 59 should roll over into minutes.
    TimeCode tc2(3, 71, 3801);

    assert(tc2.GetSeconds() == 21);

    // Edge case: exactly 60 seconds should become 0 seconds and add 1 minute.
    TimeCode tc3(0, 0, 60);

    assert(tc3.GetSeconds() == 0);

    cout << "PASSED!" << endl << endl;
}


void TestGetComponents()
{
    cout << "Testing GetComponents" << endl;

    unsigned int h;
    unsigned int m;
    unsigned int s;

    TimeCode tc(5, 2, 18);

    tc.GetComponents(h, m, s);

    assert(h == 5);
    assert(m == 2);
    assert(s == 18);

    // Edge case: zero should return 0:0:0.
    TimeCode tc2(0, 0, 0);

    tc2.GetComponents(h, m, s);

    assert(h == 0);
    assert(m == 0);
    assert(s == 0);

    // Edge case: rollover values should be converted correctly.
    TimeCode tc3(3, 71, 3801);

    tc3.GetComponents(h, m, s);

    assert(h == 5);
    assert(m == 14);
    assert(s == 21);

    cout << "PASSED!" << endl << endl;
}


void TestComponentsToSeconds()
{
    cout << "Testing ComponentsToSeconds" << endl;

    assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
    assert(TimeCode::ComponentsToSeconds(1, 0, 0) == 3600);
    assert(TimeCode::ComponentsToSeconds(0, 1, 0) == 60);
    assert(TimeCode::ComponentsToSeconds(0, 0, 1) == 1);

    assert(TimeCode::ComponentsToSeconds(3, 17, 42) == 11862);

    // Edge case: 60 minutes should roll over into 1 hour.
    assert(TimeCode::ComponentsToSeconds(1, 60, 0) == 7200);

    // Edge case: 60 seconds should roll over into 1 minute.
    assert(TimeCode::ComponentsToSeconds(0, 0, 60) == 60);

    cout << "PASSED!" << endl << endl;
}


void TestSetHours()
{
    cout << "Testing SetHours" << endl;

    TimeCode tc(8, 15, 9);

    tc.SetHours(10);

    assert(tc.GetHours() == 10);
    assert(tc.GetMinutes() == 15);
    assert(tc.GetSeconds() == 9);

    // Edge case: setting hours to 0 should keep minutes and seconds.
    tc.SetHours(0);

    assert(tc.GetHours() == 0);
    assert(tc.GetMinutes() == 15);
    assert(tc.GetSeconds() == 9);

    cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
    cout << "Testing SetMinutes" << endl;

    TimeCode tc(8, 5, 9);

    tc.SetMinutes(15);

    assert(tc.GetHours() == 8);
    assert(tc.GetMinutes() == 15);
    assert(tc.GetSeconds() == 9);

    // Edge case: minutes greater than 59 should throw an exception.
    try
    {
        tc.SetMinutes(80);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Exception was expected.
    }

    // Edge case: invalid input should not change the TimeCode.
    assert(tc.ToString() == "8:15:9");

    // Edge case: exactly 59 minutes is valid.
    tc.SetMinutes(59);

    assert(tc.GetMinutes() == 59);

    cout << "PASSED!" << endl << endl;
}


void TestSetSeconds()
{
    cout << "Testing SetSeconds" << endl;

    TimeCode tc(8, 15, 9);

    tc.SetSeconds(30);

    assert(tc.GetHours() == 8);
    assert(tc.GetMinutes() == 15);
    assert(tc.GetSeconds() == 30);

    // Edge case: seconds greater than 59 should throw an exception.
    try
    {
        tc.SetSeconds(80);
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Exception was expected.
    }

    // Edge case: invalid input should not change the TimeCode.
    assert(tc.ToString() == "8:15:30");

    // Edge case: exactly 59 seconds is valid.
    tc.SetSeconds(59);

    assert(tc.GetSeconds() == 59);

    cout << "PASSED!" << endl << endl;
}


void TestReset()
{
    cout << "Testing Reset" << endl;

    TimeCode tc(10, 20, 30);

    tc.reset();

    assert(tc.GetHours() == 0);
    assert(tc.GetMinutes() == 0);
    assert(tc.GetSeconds() == 0);
    assert(tc.GetTimeCodeAsSeconds() == 0);

    // Edge case: resetting an already-zero TimeCode should remain zero.
    tc.reset();

    assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}


void TestAddition()
{
    cout << "Testing Addition" << endl;

    TimeCode tc1(1, 15, 55);
    TimeCode tc2(0, 1, 25);

    TimeCode result = tc1 + tc2;

    assert(result.ToString() == "1:17:20");

    // Edge case: addition should roll seconds into minutes and minutes into hours.
    TimeCode tc3(1, 59, 55);
    TimeCode tc4(0, 0, 10);

    TimeCode result2 = tc3 + tc4;

    assert(result2.ToString() == "2:0:5");

    // Edge case: adding zero should not change the TimeCode.
    TimeCode tc5(2, 30, 15);
    TimeCode tc6(0, 0, 0);

    TimeCode result3 = tc5 + tc6;

    assert(result3.ToString() == "2:30:15");

    cout << "PASSED!" << endl << endl;
}


void TestSubtraction()
{
    cout << "Testing Subtraction" << endl;

    TimeCode tc1(1, 0, 0);
    TimeCode tc2(0, 50, 0);

    TimeCode result = tc1 - tc2;

    assert(result.ToString() == "0:10:0");

    // Edge case: subtracting the same TimeCode should result in zero.
    TimeCode tc3(1, 0, 0);

    TimeCode result2 = tc1 - tc3;

    assert(result2.ToString() == "0:0:0");

    // Edge case: subtracting a larger TimeCode should throw an exception.
    TimeCode tc4(1, 15, 45);

    try
    {
        TimeCode result3 = tc1 - tc4;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Exception was expected.
    }

    cout << "PASSED!" << endl << endl;
}


void TestMultiplication()
{
    cout << "Testing Multiplication" << endl;

    TimeCode tc(1, 0, 0);

    // Edge case: multiplying by 0.5 should produce half the time.
    TimeCode result = tc * 0.5;

    assert(result.ToString() == "0:30:0");

    TimeCode tc2(2, 0, 0);

    TimeCode result2 = tc2 * 2.0;

    assert(result2.ToString() == "4:0:0");

    // Edge case: multiplying by 0 should produce zero.
    TimeCode result3 = tc * 0.0;

    assert(result3.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}


void TestDivision()
{
    cout << "Testing Division" << endl;

    TimeCode tc(1, 0, 0);

    TimeCode result = tc / 2.0;

    assert(result.ToString() == "0:30:0");

    // Edge case: division by zero should throw an exception.
    try
    {
        TimeCode result2 = tc / 0;
        assert(false);
    }
    catch (const invalid_argument& e)
    {
        // Exception was expected.
    }

    cout << "PASSED!" << endl << endl;
}


void TestComparisons()
{
    cout << "Testing Comparisons" << endl;

    TimeCode tc1(1, 0, 0);
    TimeCode tc2(2, 0, 0);
    TimeCode tc3(1, 0, 0);

    assert(tc1 == tc3);
    assert(tc1 != tc2);

    assert(tc1 < tc2);
    assert(tc1 <= tc2);

    assert(tc2 > tc1);
    assert(tc2 >= tc1);

    assert(tc1 <= tc3);
    assert(tc1 >= tc3);

    // Edge case: two TimeCodes with exactly the same value.
    TimeCode tc4(5, 30, 20);
    TimeCode tc5(5, 30, 20);

    assert(tc4 == tc5);
    assert(!(tc4 != tc5));
    assert(tc4 <= tc5);
    assert(tc4 >= tc5);
    assert(!(tc4 < tc5));
    assert(!(tc4 > tc5));

    // Edge case: compare zero with a positive TimeCode.
    TimeCode tc6(0, 0, 0);
    TimeCode tc7(0, 0, 1);

    assert(tc6 < tc7);
    assert(tc7 > tc6);
    assert(tc6 != tc7);

    cout << "PASSED!" << endl << endl;
}


int main()
{
    TestConstructors();
    TestGetHours();
    TestGetMinutes();
    TestGetSeconds();
    TestGetComponents();
    TestComponentsToSeconds();

    TestSetHours();
    TestSetMinutes();
    TestSetSeconds();
    TestReset();

    TestAddition();
    TestSubtraction();
    TestMultiplication();
    TestDivision();
    TestComparisons();

    cout << "PASSED ALL TESTS!!!" << endl;

    return 0;
}