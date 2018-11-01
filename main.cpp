#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


const int ARRAYSIZE = 100;


//void skrivtab(int tab[], int n)
//{
//    for (int k=0; k<n; k++)
//        cout << tab[k] << ", ";

//    cout << "trykk en tast" << endl;
//    getch();
//}


void MergeSort(int* tab, int n)
{
    int i, j, k, lower1, lower2, size, upper1, upper2;
    int hjelp[ARRAYSIZE];

//    skrivtab(tab, n);

    size = 1;
    while (size < n)
    {
           lower1 = 0;
           k = 0;
           while (lower1+size < n)
           {
              upper1 = lower1+size-1;
              lower2 = upper1+1;
              upper2 = (lower2+size-1 < n) ? lower2+size-1 : n-1;
              for (i=lower1, j=lower2; i<=upper1 && j<=upper2; k++)
                 if (tab[i] < tab[j])
                    hjelp[k]=tab[i++];
                 else
                    hjelp[k] = tab[j++];

              for (; i<=upper1; k++)
                 hjelp[k] = tab[i++];
              for (; j<=upper2; k++)
                 hjelp[k] = tab[j++];

              lower1 = upper2+1;
           } // endwhile

           for (i=lower1; k<n; i++)
              hjelp[k++] = tab[i];
           for (i=0; i<n; i++)
              tab[i] = hjelp[i];

           size = size*2;

           //skrivtab(tab, n);
       } //endwhile
}


void InsertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;

       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

void SelectionSort()
{
    const int length = 5;
    int array[length] = { 30, 50, 20, 10, 40 };

    // Step through each element of the array
    // (except the last one, which will already be sorted by the time we get there)
    for (int startIndex = 0; startIndex < length - 1; ++startIndex)
    {

        int smallestIndex = startIndex;

        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {

            if (array[currentIndex] < array[smallestIndex])

                smallestIndex = currentIndex;
        }

        std::swap(array[startIndex], array[smallestIndex]);
    }

    for (int index = 0; index < length; ++index)
        std::cout << array[index] << ' ';
}

template <typename T>
vector<T> RandomVector(int VectorSize)
{
    vector<T> VectorToReturn;
    //VectorToReturn.resize(static_cast<unsigned int>(VectorSize));

    for (int i = 0; i < VectorSize; ++i)
    {
        VectorToReturn.push_back(i);
    }

    random_shuffle (VectorToReturn.begin(), VectorToReturn.end());

    return VectorToReturn;
}


int main()
{
    int OurRandomVectorSize = 30;
    vector<int> OurRandomVector = RandomVector<int>(OurRandomVectorSize);

    for (auto VectorNum : OurRandomVector)
    {
        cout << VectorNum << ", ";
    }


    return 0;
}
