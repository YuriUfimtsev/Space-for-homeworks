#include <stdio.h>
#include <stdbool.h>
#include <math.h>

float raiseToDegreeStandart(basicOfExtent, exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    int const multiplier = basicOfExtent;
    for (int i = 0; i < abs(exponent) - 1; ++i)
    {
        basicOfExtent *= multiplier;
    }
    if (exponent < 0)
    {
        return 1 / (float)basicOfExtent;
    }
    return (float) basicOfExtent;
}

float raiseToDegreeModified(basicOfExtent, exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    if (abs(exponent) % 2 == 1)
    {
        if (exponent < 0)
        {
            return (float) 1 / (basicOfExtent * raiseToDegreeModified(basicOfExtent, abs(exponent) - 1));
        }
        return basicOfExtent * raiseToDegreeModified(basicOfExtent, abs(exponent) - 1);
    }
    else
    {
        if (exponent < 0)
        {
            float newValue = 1 / (float) raiseToDegreeModified(basicOfExtent, abs(exponent) / 2);
            return newValue * newValue;
        }
        float newValue = raiseToDegreeModified(basicOfExtent, abs(exponent) / 2);
        return newValue * newValue;
    }
}

bool checkRaiseToDegree(int basicOfExtent, int exponent, float result)
{
    return raiseToDegreeStandart(basicOfExtent, exponent) == result && raiseToDegreeModified(basicOfExtent, exponent) == result;
}

bool checkFirst()
{
    return checkRaiseToDegree(2, 3, 8);
}

bool checkSecond()
{
    return checkRaiseToDegree(1, 10, 1);
}

bool checkThird()
{
    return checkRaiseToDegree(2, -5, 0.03125);
}

bool checkFourth()
{
    return checkRaiseToDegree(2, -1, 0.5);
}

bool checkFifth()
{
    return checkRaiseToDegree(5, 0, 1);
}

bool checkSixth()
{
    return checkRaiseToDegree(0, 35, 0);
}

bool checkSeventh()
{
    return checkRaiseToDegree(-5, 3, -125);
}

int main()
{
    if (!checkFirst() || !checkSecond() || !checkThird() || !checkFourth() || !checkFifth() || !checkSixth() || !checkSeventh())
    {
        printf("Tests failed");
        return 0;
    }

    printf("Enter the basic of extent: ");
    int basicOfExtent = 0;
    int checkScanf = scanf("%d", &basicOfExtent);
    if (checkScanf != 1)
    {
        printf("We are amased with your failure");
        return 0;
    }

    printf("Enter the exponent: ");
    int exponent = 0;
    checkScanf = scanf("%d", &exponent);
    if (checkScanf != 1)
    {
        printf("We are amased with your failure");
        return 0;
    }

    if ((basicOfExtent == 0) && (exponent <= 0))
    {
        printf("The result doesn't exist\n");
        return 0;
    }
    printf("Exponentiation result (modified method): %f\n", raiseToDegreeModified(basicOfExtent, exponent));
    printf("Exponentiation result (standart method): %f\n", raiseToDegreeStandart(basicOfExtent, exponent));
}
