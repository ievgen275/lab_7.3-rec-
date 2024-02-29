#include "pch.h"
#include "CppUnitTest.h"
#include "../PR_7.3(rec)/PR_7.3(rec).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(PositiveElementCountInColumnsWithNegative)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; ++i)
            {
                matrix[i] = new int[colCount];
                for (int j = 0; j < colCount; ++j)
                {
                    matrix[i][j] = (i + j) % 2 == 0 ? -1 : 1;
                }
            }

            int sum = 0;
            Assert::IsTrue(Part1_Count(matrix, rowCount, colCount, sum, 0));
            Assert::AreEqual(sum, 0);


            for (int i = 0; i < rowCount; ++i)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        TEST_METHOD(NoSaddlePointInMatrix)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; ++i)
            {
                matrix[i] = new int[colCount];
                for (int j = 0; j < colCount; ++j)
                {
                    matrix[i][j] = (i + j) % 2 == 0 ? 1 : -1;
                }
            }

            int No = 0;
            Part2_SaddlePointRows(matrix, rowCount, colCount, No, 0);

            Assert::AreEqual(0, No);

            for (int i = 0; i < rowCount; ++i)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
	};
}
