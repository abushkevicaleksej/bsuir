#include "FloatNumber.h"
FloatNumber::FloatNumber()
{
    this->minus = '0';
    this->exp = this->exp127;
    this->mantiss = this->clearMantiss;
}
FloatNumber::FloatNumber(float decNum)
{
    this->exp = exp127;
    if (decNum < 0)
    {
        this->minus = '1';
        decNum *= -1;
    }
    else
        this->minus = '0';
    std::string intPart = clearMantiss;
    std::string behindPointPart = clearMantiss;
    SeparateParts(decNum, intPart, behindPointPart);
    int i = 0;
    if (intPart != this->clearMantiss)
        FillByNumWithIntPart(intPart, behindPointPart, i);
    else
        FillByNumWhithNoIntPart(intPart, behindPointPart, i);
}
void FloatNumber::FillByNumWithIntPart(std::string& intPart, std::string& behindPointPart, int& index)
{
    while (intPart[index] == '0')
        index++;
    for (int j = index + 1; j < intPart.size(); j++)
    {
        this->mantiss.push_back(intPart[j]);
        this->exp = BinarySum(binOne, this->exp);
    }
    int mantissSize = this->mantiss.size();
    for (int j = 0; j < 23 - mantissSize; j++)
        this->mantiss.push_back(behindPointPart[j]);
}
void FloatNumber::FillByNumWhithNoIntPart(std::string& intPart, std::string& behindPointPart, int& index)
{
    while (behindPointPart[index] == '0') {
        index++;
        this->exp = BinarySum(binMinusOne, this->exp);
    }
    this->exp = BinarySum(binMinusOne, this->exp);
    for (int j = index + 1; j < behindPointPart.size(); j++)
        this->mantiss.push_back(behindPointPart[j]);
    for (int j = this->mantiss.size(); j < 23; j++)
    {
        this->mantiss.push_back('0');
    }
}

void FloatNumber::SeparateParts(float decNum, std::string& intPart, std::string& behindPoinPart)
{
    float DecIntPart;
    float DecBehindPoinPart = modf(decNum, &DecIntPart);
    MakeIntBinary(DecIntPart, intPart);
    MakeBehindPointBinary(DecBehindPoinPart, behindPoinPart);
}

void FloatNumber::MakeIntBinary(int decNum, std::string& output)
{
    int i = output.size() - 1;
    do
    {
        output[i] = char('0' + decNum % 2);
        decNum = decNum / 2;
        i--;
    } while (decNum > 0);
}
void FloatNumber::MakeBehindPointBinary(float numLowerThanOne, std::string& output)
{
    if (numLowerThanOne < 0)
        numLowerThanOne *= -1;
    for (int i = 0; i < 23; i++)
    {
        numLowerThanOne *= 2;
        if (numLowerThanOne >= 1)
        {
            numLowerThanOne -= 1;
            output[i] = '1';
        }
        else
            output[i] = '0';
    }
}

std::string FloatNumber::BinarySum(std::string binaryNum1, std::string binaryNum2)
{
    bool oneForNextDigit = 0;
    for (int i = binaryNum1.size() - 1; i >= 0; i--)
    {
        if (binaryNum1[i] == '1' && binaryNum2[i] == '1')
            SumOfTwoOnes(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if ((binaryNum1[i] == '0' && binaryNum2[i] == '1') || (binaryNum1[i] == '1' && binaryNum2[i] == '0'))
            SumOfOneAndZero(binaryNum1, binaryNum2, oneForNextDigit, i);
        else if (binaryNum1[i] == '0' && binaryNum2[i] == '0')
            SumOfTwoZeros(binaryNum1, binaryNum2, oneForNextDigit, i);
    }
    return binaryNum1;
}
void FloatNumber::SumOfTwoOnes(std::string& num1, std::string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
    {
        num1[index] = '0';
        oneForNextDigit = 1;
    }
    else
    {
        num1[index] = '1';
        oneForNextDigit = 1;
    }
}
void FloatNumber::SumOfOneAndZero(std::string& num1, std::string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '1';
    else
        num1[index] = '0';
}
void FloatNumber::SumOfTwoZeros(std::string& num1, std::string& num2, bool& oneForNextDigit, int index)
{
    if (oneForNextDigit == 0)
        num1[index] = '0';
    else
    {
        oneForNextDigit = 0;
        num1[index] = '1';
    }
}

FloatNumber FloatNumber::operator+(const FloatNumber& num)
{
    FloatNumber num1;
    num1.minus = this->minus;
    num1.exp = this->exp;
    num1.mantiss = this->mantiss;
    FloatNumber num2 = num;
    MantiissEqualize(num1, num2);
    num1 = MantissSum(num1, num2);

    return num1;
}
bool FloatNumber::IsExpMore(std::string exp1, std::string exp2)
{
    for (int i = 0; i < exp1.size(); i++)
    {
        if (exp1[i] == '1' && exp2[i] == '0')
            return true;
        if (exp1[i] == '0' && exp2[i] == '1')
            return false;
    }
    return false;
}
void FloatNumber::MoveNum(std::string& mantiss, int added)
{
    std::string buffer = "";
    if (added == 1)
        buffer.push_back('1');
    else if ((added == 0))
        buffer.push_back('0');
    for (int i = 0; i < mantiss.size() - 1; i++)
        buffer.push_back(mantiss[i]);
    mantiss = buffer;
}
void FloatNumber::MantiissEqualize(FloatNumber& num1, FloatNumber& num2)
{
    num2.exp = BinarySum(num2.exp, binOne);
    MoveNum(num2.mantiss, 1);
    num1.exp = BinarySum(num1.exp, binOne);
    MoveNum(num1.mantiss, 1);
    if (IsExpMore(num1.exp, num2.exp))
    {
        while (IsExpMore(num1.exp, num2.exp))
        {
            num2.exp = BinarySum(num2.exp, binOne);
            MoveNum(num2.mantiss, 0);
        }
    }
    else if (IsExpMore(num2.exp, num1.exp))
    {
        while (IsExpMore(num2.exp, num1.exp))
        {
            num1.exp = BinarySum(num1.exp, binOne);
            MoveNum(num1.mantiss, 0);
        }
    }
}
FloatNumber FloatNumber::MantissSum(FloatNumber& num1, FloatNumber& num2)
{
    std::string num1MantissBuff = clearExp;
    std::string num2MantissBuff = clearExp;
    FloatNumber output;
    for (int i = 0; i < num1.mantiss.size(); i++)
        num1MantissBuff.push_back(num1.mantiss[i]);
    for (int i = 0; i < num2.mantiss.size(); i++)
        num2MantissBuff.push_back(num2.mantiss[i]);
    if (num1.minus == "1")
        num1MantissBuff = MakeAdditional(num1MantissBuff);
    if (num2.minus == "1")
        num2MantissBuff = MakeAdditional(num2MantissBuff);

    num1MantissBuff = BinarySum(num1MantissBuff, num2MantissBuff);

    if (num1MantissBuff[0] == '1')
    {
        num1MantissBuff = MakeAdditional(num1MantissBuff);
        output.minus = "1";
    }
    ConvertToStandartFormat(num1MantissBuff, num1, output);
    return output;
}
void FloatNumber::ConvertToStandartFormat(std::string& num1MantissBuff, FloatNumber& num1, FloatNumber& output)
{
    int capOfZeros = 1;
    while (num1MantissBuff[capOfZeros] == '0')
        capOfZeros++;
    if (capOfZeros < 7)
    {
        for (int i = capOfZeros; i < 8; i++)
            BinarySum(num1.exp, binOne);
    }
    if (capOfZeros > 7)
    {
        int i = 7;
        while (num1MantissBuff[i] == '0')
        {
            i++;
            num1.exp = BinarySum(num1.exp, binMinusOne);
        }
    }
    output.exp = num1.exp;
    output.mantiss = "";
    for (int i = capOfZeros + 1; i < 23 + capOfZeros; i++)
        output.mantiss.push_back(num1MantissBuff[i]);
}

void FloatNumber::operator=(const FloatNumber& num1)
{
    this->minus = num1.minus;
    this->exp = num1.exp;
    this->mantiss = num1.mantiss;
}
std::string FloatNumber::MakeAdditional(std::string binaryNum)
{
    std::string binOne = "";
    binOne.push_back('1');
    for (int i = 1; i < binaryNum.size(); i++)
        binOne.push_back('0');

    binaryNum = BinNumInverse(binaryNum);
    binaryNum = BinarySum(binaryNum, binOne);

    return binaryNum;
}
std::string FloatNumber::BinNumInverse(std::string binaryNum)
{
    for (int i = 1; i < binaryNum.size(); i++)
    {
        if (binaryNum[i] == '0')
            binaryNum[i] = '1';
        else if (binaryNum[i] == '1')
            binaryNum[i] = '0';
    }
    return binaryNum;
}

std::string FloatNumber::printFloatNumber()
{
    return this->minus + " " + this->exp + " " + this->mantiss;
}


float FloatNumber::calcInDec()
{
    FloatNumber copyOfMainNum;
    copyOfMainNum.minus = this->minus;
    copyOfMainNum.exp = this->exp;
    copyOfMainNum.mantiss = this->mantiss;
    float output = 0;
    std::string intPart = "1";
    std::string behindPointPart = "";
    if (copyOfMainNum.exp != this->exp127)
    {
        if (copyOfMainNum.exp[0] == '0')
            MultByExpWithNegativeDegree(copyOfMainNum, intPart, behindPointPart);
        else if (copyOfMainNum.exp[0] == '1')
            MultByExpWithPositiveDegree(copyOfMainNum, intPart, behindPointPart);
    }
    else
        for (int i = 0; i < copyOfMainNum.mantiss.size(); i++)
            behindPointPart.push_back(copyOfMainNum.mantiss[i]);
    output = IntPartInFloat(intPart) + BehindPointPartInFloat(behindPointPart);
    if (this->minus == "1")
        output *= -1;
    return output;
}
void FloatNumber::MultByExpWithNegativeDegree(FloatNumber& copyOfMainNum, std::string& intPart, std::string& behindPointPart)
{
    copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binOne);
    while (copyOfMainNum.exp != this->exp127)
    {
        copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binMinusOne);
        behindPointPart.push_back('0');
    }
    intPart = "0";
    behindPointPart.push_back('1');
    for (int i = 0; i < copyOfMainNum.mantiss.size(); i++)
        behindPointPart.push_back(copyOfMainNum.mantiss[i]);
}
void FloatNumber::MultByExpWithPositiveDegree(FloatNumber& copyOfMainNum, std::string& intPart, std::string& behindPointPart)
{
    int i = 0;
    while (copyOfMainNum.exp != this->exp127)
    {
        copyOfMainNum.exp = BinarySum(copyOfMainNum.exp, binMinusOne);
        intPart.push_back(copyOfMainNum.mantiss[i]);
        i++;
    }
    for (int j = i; j < copyOfMainNum.mantiss.size(); j++)
        behindPointPart.push_back(copyOfMainNum.mantiss[j]);
}
float FloatNumber::IntPartInFloat(std::string intPart)
{
    float koeff = 1;
    float buffer = 0;
    float output = 0;
    for (int i = intPart.size() - 1; i >= 0; i--)
    {
        buffer = intPart[i] - '0';
        output += buffer * koeff;
        koeff *= 2;
    }
    return output;
}

float FloatNumber::BehindPointPartInFloat(std::string behindPointPart)
{
    float koeff = 0.5;
    float buffer = 0;
    float output = 0;
    for (int i = 0; i < behindPointPart.size(); i++)
    {
        buffer = behindPointPart[i] - '0';
        output += buffer * koeff;
        koeff *= 0.5;
    }
    return output;
}