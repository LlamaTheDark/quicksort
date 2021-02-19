#include <string>
#include <iostream>
#include <sstream>
#include "QS.h"

#define SWAP(a, b) \
if(a != b) { a ^= b; b ^= a; a^=b; }\

#define ASSERT(x) if(!(x)) {std::cerr << "you big failure when u try \'" << #x << "\'" << std::endl; exit(1);}


void printArr(int min, int max, int *array){
    for(int i = min; i < max; i++){
        std::cout << *(array + i) << "\t";
    }
    std::cout << std::endl;
}

QS::QS(){

}
QS::~QS(){
    if(arr != NULL){
        delete [] arr;
        arr = NULL;
    }
}

void QS::quicksort(int first, int last){
    // std::cout << "first: " << first << ", last: " << last << std::endl;

    if((last - first) < 1) return;

    int pivot = medianOfThree(first, last); // get initial pivot index
    pivot = partition(first, last, pivot);

    // std::cout << "\tpivot: " << pivot << std::endl;

    quicksort(first, pivot-1); // recursive call to left part
    quicksort(pivot+1, last);  // recursive call to right part
}
void QS::sortAll(){
    // std::cout << "################################################################\n";
    // std::cout << "######################## SORT ALL START ########################\n";
    // std::cout << "################################################################" << std::endl;
    if(arr != NULL && size != 0){
        quicksort(0, size-1);
    }
}

int QS::medianOfThree(int left, int right){
    // std::cout << "mo3" << std::endl;
    if(size == 0 
    || left < 0 
    || right < 0 
    || left >= size
    || right >= size
    || left >= right
    ) return -1;

    int middle = (left + right) / 2;
    // std::cout << "\tmiddle: " << middle << std::endl;

    for(int i = 0; i < 2; i++){
        if(arr[left] > arr[middle]) {
            // std::cout << "left > middle!" << std::endl;
            SWAP(arr[left], arr[middle])
        }
        if(arr[middle] > arr[right]){ 
            // std::cout << "middle > right!" << std::endl;
            SWAP(arr[middle], arr[right])
        }
    }

    return middle;
}

int QS::partition(int left, int right, int pivotIndex){ // there are many ways to do the partitioning algorithm

    if(arr == NULL 
    || size == 0
    || left < 0 
    || right < 0 
    || left >= capacity 
    || right >= capacity 
    || left >= right
    || pivotIndex < left
    || pivotIndex > right
    ) {
        // std::cout << "partition failure" << std::endl;
        return -1;
    }

    // std::cout << " = = = = = = = new partition run info = = = = = = = \npivot value: " << arr[pivotIndex] << std::endl;
    // std::cout << "left, right, and initial pivot indices: " << left << ", " << right << ", " << pivotIndex << ";" << std::endl;
    // std::cout << "entire array: \n";
    // printArr(0, size, arr);
    // std::cout << "part being partitioned: \n";
    // printArr(left, right+1, arr);
    SWAP(arr[left], arr[pivotIndex]) // put the pivot value (@pivotIndex) at the start of the array
                                     // i.e. arr[left] is now the pivot value

    int up = left + 1, down = right;
    int lastOK = -1;

    do {
        // find first element greater than the pivot value (from the left)
        // std::cout << " - - - Finding value for \'up\' - - - " << std::endl;
        while(up != right && !(arr[left] < arr[up])) {
            if(arr[up] != arr[left]) {
                lastOK = up;
                // std::cout << "last non-pivot index: " << lastOK << std::endl;
            }
            // printArr(left, right+1, arr);
            // for(int i = left; i <= right; i++){
            //     if(i == up){
            //         std::cout << "|\t";
            //     }else{
            //         std::cout << "\t";
            //     }
            // }
            // std::cout << std::endl;
            up++;
        }
        
        // std::cout << "\tfound value for up: " << up << ", arr[" << up << "]" << " = " << arr[up] << "\n" << std::endl;

        ASSERT(up == (right) || arr[up] > arr[left])

        // std::cout << " - - - Finding value for \'down\' - - - " << std::endl;
        while(down != left && arr[left] < arr[down]) {
            // printArr(left, right+1, arr);
            // for(int i = left; i <= right; i++){
            //     if(i == down){
            //         std::cout << "|\t";
            //     }else{
            //         std::cout << "\t";
            //     }
            // }
            // std::cout << std::endl;
            down--;
        }

        // std::cout << "\tfound value for up: " << down << ", arr[" << down << "]" << " = " << arr[down] << "\n" << std::endl;
        
        ASSERT(down == left || arr[down] <= arr[left])

        // std::cout << "is up (" << up << ") < down (" << down << ")?" << std::endl;
        if(up < down) { 
            // std::cout << "\tYes. swapping up and down" << std::endl;
            SWAP(arr[up], arr[down]) 
        }
        // else std::cout << "\tnope" << std::endl;


        // std::cout << "\t Are these the same, and both equal to the pivot value? If so, let's swap up with the last pivot index" << std::endl;
        if(arr[up] == arr[left] && lastOK != -1) {
            SWAP(arr[up], arr[lastOK]);
            // std::cout << "\t\tswapped!\n\t\tnew values (arr[up], arr[down]) = (" << arr[up] << ", " << arr[down] << ")" << std::endl;
        } // if these are the same the program will infinitely loop. so we'll just take the second to last value instead...

    } while(up < down);

    // std::cout << "PARTITION COMPLETE. SWAPPING VALUES @$\n";
    // printArr(left, right+1, arr);
    // for(int i = left; i <= right; i++){
    //     if(i == down || i == left){
    //                 std::cout << "$\t";
    //             }else{
    //                 std::cout << "\t";
    //             }
    // }
    // std::cout << std::endl;

    SWAP(arr[left], arr[down])

    // printArr(left, right+1, arr);


    return down; // index of last pivot
}

std::string QS::getArray() const {
    if(size == 0) return "";

    std::stringstream buffer;
    for(int i = 0; i < size-1; i++){
        buffer << arr[i] << ",";
    }
    buffer << arr[size-1];
    return buffer.str();
}

int QS::getSize() const { return size; }

bool QS::addToArray(int value){
    if(size >= capacity) return false;

    arr[size] = value;
    size++;

    return true;
}

bool QS::createArray(int capacity){
    if(capacity < 0) return false;

    if(arr != NULL) clear();

    arr = new int[capacity];
    QS::capacity = capacity;

    // std::cout << " = = = ARRAY CREATED WITH FOLLOWING SPECS: = = = \n";
    // std::cout << "\tcapacity: " << capacity << std::endl;

    return true;
}

void QS::clear(){
    delete [] arr;
    arr = NULL;
    size = 0;
    capacity = 0;
}


