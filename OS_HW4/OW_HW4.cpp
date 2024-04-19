// Platform Information:
// - Platform: This C++ code can be compiled and run on any platform that supports C++ (e.g., Windows, macOS, Linux).
// - Compiler: Any C++ compiler such as GCC (GNU Compiler Collection), Clang, or Microsoft Visual C++ can be used to compile this code.
// - Libraries: This code does not depend on any external libraries.

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
predict() that takes a frame vector, index, and page array. It returns the  predicted page.
*/
int predictPage(int page[], vector<int>& frames, int pageNumber, int pageIndex)
{
    int result = -1, farthestPage = pageIndex;
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = pageIndex; j < pageNumber; j++)
        {
            if (frames[i] == page[j])
            {
                if (j > farthestPage)
                {
                    farthestPage = j;
                    result = i;
                }
                break;
            }
        }

        if (j == pageNumber)
            return i;
    }

    if (result == -1)
        return 0;
    else
        return result;
}


/*
boolSearch() that takes a frame vector, and a key that has to be searched in the frame. It return true if the key is found else it returns false
*/
bool searchPage(int key, vector<int>& frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        // if the frame is found, return true
        if (frames[i] == key)
            return true;
    }

    return false;
}

/*
find() that takes a page array, frame number, and page number. It finds and prints the page hits and page misses.
*/
void OPTAlgo(int page[], int pageNumber, int frameNumber)
{
    vector<int> frames;
    int hit = 0;
    for (int i = 0; i < pageNumber; i++)
    {
        if (searchPage(page[i], frames))
        {
            // if found, increment the hit counter
            hit++;
            continue;
        }

        if (frames.size() < frameNumber)
            frames.push_back(page[i]);
        else
        {
            int j = predictPage(page, frames, pageNumber, i + 1);
            frames[j] = page[i];
        }

        for (int k : frames) { //loop to display the current frame contents 
            cout << k;
        }
        cout << endl;
        cout << "Optimal Algo Page faults: " << pageNumber - hit << endl; //outpute current number of faults
    }


}

void FIFOAlgo(int page[], int pageNumber, int frameNumber)
{
    queue<int> pageQueue;
    unordered_set<int> pageSet;
    int PF = 0;

    for (int i = 0; i < pageNumber; i++) {
        if (pageSet.size() < frameNumber) {
            if (pageSet.find(page[i]) == pageSet.end()) {
                pageSet.insert(page[i]);
                PF++;
                pageQueue.push(page[i]);
            }
        }
        else {
            if (pageSet.find(page[i]) == pageSet.end()) {
                int val = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(val);
                pageSet.insert(page[i]);
                pageQueue.push(page[i]);
                PF++;
            }
        }

        for (int j : pageSet) {
            cout << j;
        }
        cout << endl;
        cout << "FIFO Algo Page faults: " << PF << endl;
    }
}

void LRUAlgo(int page[], int pageNumber, int frameNumber)
{
    // To represent set of current pages. We use an unordered_set so that we quickly check if a page is present in set or not 
    unordered_set<int> pageSet;

    // To store least recently used indexes of pages. 
    unordered_map<int, int> indexes;

    // Start from initial page 
    int PF = 0;
    for (int i = 0; i < pageNumber; i++)
    {
        // Check if the set can hold more pages 
        if (pageSet.size() < frameNumber)
        {
            // Insert it into set if not present already which represents page fault 
            if (pageSet.find(page[i]) == pageSet.end())
            {
                pageSet.insert(page[i]);

                // increment page fault 
                PF++;
            }

            // Store the recently used index of each page 
            indexes[page[i]] = i;
        }
        // If the set is full then need to perform lru 
        else
        {
            // Check if current page is not already present in the set 
            if (pageSet.find(page[i]) == pageSet.end())
            {
                // Find the least recently used pages that is present in the set 
                int lru = INT_MAX, val;
                for (auto it = pageSet.begin(); it != pageSet.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }

                // Remove the indexes page 
                pageSet.erase(val);

                // insert the current page 
                pageSet.insert(page[i]);

                // Increment page faults 
                PF++;
            }
            // Update the current page index 
            indexes[page[i]] = i;
        }
        for (int j : pageSet) {
            cout << j;
        }
        cout << endl;
        cout << "LRU Algo Page faults: " << PF << endl;
    }
}
   


int main()
{
    int page[] = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int pageNumber = sizeof(page) / sizeof(page[0]);
    int frameNumber = 4;
    cout << "For the Optimal Algorithim " << endl;
    OPTAlgo(page, pageNumber, frameNumber);
    cout << endl <<"For FIFO Algorithim " << endl;
    FIFOAlgo(page, pageNumber, frameNumber);
    cout << endl << "For LRU Algorithim " << endl;
    LRUAlgo(page, pageNumber, frameNumber);


    return 0;
}