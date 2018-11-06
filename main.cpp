#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

#include "binarynode.h"

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
           while (Lower1 + Size < VectorSize)
           {
              Upper1 = Lower1 + Size - 1;
              Lower2 = Upper1 + 1;
              Upper2 = (Lower2 + Size - 1 < VectorSize) ? Lower2 + Size - 1 : VectorSize - 1;
              for (i = Lower1, j = Lower2; i <= Upper1 && j <= Upper2; k++)
                 if (VectorIn[i] < VectorIn[j])
                    ExtraVector[k] = VectorIn[i++];
                 else
                    ExtraVector[k] = VectorIn[j++];

              for (; i<= Upper1; k++)
                 ExtraVector[k] = VectorIn[i++];
              for (; j<= Upper2; k++)
                 ExtraVector[k] = VectorIn[j++];

              Lower1 = Upper2+1;
           } // endwhile

           for (i = Lower1; k < VectorSize; i++)
              ExtraVector[k++] = VectorIn[i];
           for (i = 0; i < VectorSize; i++)
              VectorIn[i] = ExtraVector[i];

           Size = Size * 2;

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
}

template <typename T>
void StandardLibrarySort(vector<T> &VectorIn)
{
    sort(VectorIn.begin(), VectorIn.end());
}


template <typename T>
void BinarySearchTreeSort(vector<T> &VectorIn)
{
    TheBinaryTree::BinarySearchTree<int> OurTree{};
    for(int index : VectorIn)
    {
        OurTree.AddLeaf(VectorIn[index]);
    }
}


template <typename T>
void HeapSort(vector<T> &VectorIn)
{
    make_heap(VectorIn.begin(), VectorIn.end());

    // Hmm...
    //sort_heap(VectorIn.begin(), VectorIn.end());
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
    ////  Example print
    //    for (auto VectorNum : OurVector)
    //    {
    //        cout << VectorNum << ", ";
    //    }


//    cout << "Heap sort: ";
//    int PowerTo = 8;
//    for (int i = 1; i < PowerTo; ++i)
//    {
//        int OurVectorSize = static_cast<int>(pow(10, i));
//        vector<int> OurVector = RandomVector<int>(OurVectorSize);
//        clock_t Begin = clock();
//        HeapSort(OurVector);
//        clock_t End = clock();
//        double ElapsedSecs = double(End - Begin) / CLOCKS_PER_SEC;
//        cout << "Time to sort with 10 power to: " << i;
//        cout << endl << "Time elapsed: " << setprecision(5) << ElapsedSecs << endl;
//    }






////  All sorts

    int Power = 5;
    cout << "Testing algorithms based on 10 power to " << Power << ".\n\n";
    int OurVectorSize = static_cast<int>(pow(10, Power));
    vector<int> OurVector = RandomVector<int>(OurVectorSize);
    vector<int> OriginalVector = OurVector;

    cout << "Merge sort: ";
    auto Start1 = std::chrono::system_clock::now();
    MergeSort(OurVector, OurVector.size());
    auto End1 = std::chrono::system_clock::now();
    std::chrono::duration<double> ElapsedSecsMerge = End1 - Start1;
    std::time_t EndTime1 = std::chrono::system_clock::to_time_t(End1);

    std::cout << "Finished computation at " << std::ctime(&EndTime1)
                  << "Elapsed time: " << ElapsedSecsMerge.count() << "s\n";



    cout << "\nInsertion sort: ";
    OurVector = OriginalVector;
    auto Start2 = std::chrono::system_clock::now();
    InsertionSort(OurVector, OurVector.size());
    auto End2 = std::chrono::system_clock::now();
    std::chrono::duration<double> ElapsedSecsInsertion = End2 - Start2;
    std::time_t EndTime2 = std::chrono::system_clock::to_time_t(End1);

    std::cout << "Finished computation at " << std::ctime(&EndTime2)
                  << "Elapsed time: " << ElapsedSecsInsertion.count() << "s\n";



    cout << "\nSelection sort: ";
    OurVector = OriginalVector;
    auto Start3 = std::chrono::system_clock::now();
    SelectionSort(OurVector, OurVector.size());
    auto End3 = std::chrono::system_clock::now();
    std::chrono::duration<double> ElapsedSecsSelection = End3 - Start3;
    std::time_t EndTime3 = std::chrono::system_clock::to_time_t(End1);

    std::cout << "Finished computation at " << std::ctime(&EndTime3)
                  << "Elapsed time: " << ElapsedSecsSelection.count() << "s\n";



    cout << "\nStandard library sort: ";
    OurVector = OriginalVector;
    auto Start4 = std::chrono::system_clock::now();
    StandardLibrarySort(OurVector);
    auto End4 = std::chrono::system_clock::now();
    std::chrono::duration<double> ElapsedSecsStandardLibrary = End4 - Start4;
    std::time_t EndTime4 = std::chrono::system_clock::to_time_t(End4);

    std::cout << "Finished computation at " << std::ctime(&EndTime4)
                  << "Elapsed time: " << ElapsedSecsStandardLibrary.count() << "s\n";



    cout << "\nBinary search tree sort: ";
    OurVector = OriginalVector;
    BinarySearchTreeSort(OurVector);
    auto Start5 = std::chrono::system_clock::now();
    cout << "\nHeap sort: ";
    OurVector = OriginalVector;
    auto End5 = std::chrono::system_clock::now();
    std::chrono::duration<double> ElapsedSecsHeap = End5 - Start5;
    std::time_t EndTime5 = std::chrono::system_clock::to_time_t(End5);

    std::cout << "Finished computation at " << std::ctime(&EndTime5)
                  << "Elapsed time: " << ElapsedSecsHeap.count() << "s\n";




    return 0;
}
