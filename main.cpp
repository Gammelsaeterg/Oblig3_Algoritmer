#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


template <typename T>
void MergeSort(vector<T> &VectorIn, unsigned int VectorSize)
{
    unsigned int i, j, k, Lower1, Lower2, Size, Upper1, Upper2;
    vector<T> ExtraVector;
    ExtraVector.resize(VectorSize);

    Size = 1;
    while (Size < VectorSize)
    {
           Lower1 = 0;
           k = 0;
           while (Lower1+Size < VectorSize)
           {
              Upper1 = Lower1 + Size - 1;
              Lower2 = Upper1 + 1;
              Upper2 = (Lower2 + Size-1 < VectorSize) ? Lower2 + Size - 1 : VectorSize - 1;
              for (i=Lower1, j=Lower2; i<=Upper1 && j<=Upper2; k++)
                 if (VectorIn[i] < VectorIn[j])
                    ExtraVector[k]=VectorIn[i++];
                 else
                    ExtraVector[k] = VectorIn[j++];

              for (; i<=Upper1; k++)
                 ExtraVector[k] = VectorIn[i++];
              for (; j<=Upper2; k++)
                 ExtraVector[k] = VectorIn[j++];

              Lower1 = Upper2+1;
           } // endwhile

           for (i=Lower1; k<VectorSize; i++)
              ExtraVector[k++] = VectorIn[i];
           for (i=0; i<VectorSize; i++)
              VectorIn[i] = ExtraVector[i];

           Size = Size*2;

       }
}

template <typename T>
void InsertionSort(vector<T> &VectorIn, unsigned int VectorSize)
{
   int key, j;
   for (unsigned int i = 1; i < VectorSize; i++)
   {
       key = VectorIn[i];
       j = static_cast<int>(i) - 1;

       while (j >= 0 && VectorIn[j] > key)
       {
           VectorIn[j + 1] = VectorIn[j];
           j = j - 1;
       }
       VectorIn[j + 1] = key;
   }
}

template <typename T>
void SelectionSort(vector<T> &VectorIn, unsigned int VectorSize)
{

    for (unsigned int StartIndex = 0; StartIndex < VectorSize - 1; ++StartIndex)
    {

        unsigned int SmallestIndex = StartIndex;

        for (unsigned int currentIndex = StartIndex + 1; currentIndex < VectorSize; ++currentIndex)
        {

            if (VectorIn[currentIndex] < VectorIn[SmallestIndex])

                SmallestIndex = currentIndex;
        }

        std::swap(VectorIn[StartIndex], VectorIn[SmallestIndex]);
    }

    for (unsigned int Index = 0; Index < VectorSize; ++Index)
        std::cout << VectorIn[Index] << ' ';
}

template <typename T>
vector<T> RandomVector(int VectorSize)
{
    vector<T> VectorToReturn;

    for (int i = 0; i < VectorSize; ++i)
    {
        VectorToReturn.push_back(i);
    }

    random_shuffle (VectorToReturn.begin(), VectorToReturn.end());

    return VectorToReturn;
}


int main()
{
    int OurVectorSize = 10;
    vector<int> OurVector = RandomVector<int>(OurVectorSize);

    // Merge sort
    cout << "\nAfter new shuffle: ";
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;

    cout << "\nAfter sorting with merge sort: ";

    MergeSort(OurVector, OurVector.size());
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;


    // Selection sort
    cout << "\nAfter new shuffle: ";
    OurVector = RandomVector<int>(OurVectorSize);
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;

    cout << "\nAfter sorting with selection sort: ";
    SelectionSort(OurVector, OurVector.size());
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;


    // Insertion sort
    cout << "\nAfter new shuffle: ";
    OurVector = RandomVector<int>(OurVectorSize);
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;

    cout << "\nAfter sorting with insertion sort: ";
    InsertionSort(OurVector, OurVector.size());
    for (auto VectorNum : OurVector)
    {
        cout << VectorNum << ", ";
    }
    cout << endl;

    return 0;
}
