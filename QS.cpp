#include <string>
#include <iostream>
#include <sstream>
#include "QS.h"

#define SWAP(a, b) \
if(a != b) { a ^= b; b ^= a; a^=b; }\


void printArr(int min, int max, int *array){
    for(int i = min; i <= max; i++){
        std::cout << *(array + i) << " ";
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
    if(arr != NULL && size != 0){
        quicksort(0, size-1);
    }
}

int QS::medianOfThree(int left, int right){
    // std::cout << "mo3" << std::endl;
    if(size == 0 || left < 0 || right < 0 || left >= capacity || right >= capacity || left >= right) return -1; // use an assert or whatever it's called

    int middle = (left + right) / 2;
    // std::cout << "\tmiddle: " << middle << std::endl;

    if(arr[left] > arr[middle]) {
        // std::cout << "left > middle!" << std::endl;
        SWAP(arr[left], arr[middle])
    }

    if(arr[middle] > arr[right]){ 
        // std::cout << "middle > right!" << std::endl;
        SWAP(arr[middle], arr[right])
    }

    return middle;
}

int QS::partition(int left, int right, int pivotIndex){ // there are many ways to do the partitioning algorithm
    if(arr == NULL || left < 0 || right < 0 || left >= capacity || right >= capacity || left >= right) return -1;
    
    SWAP(arr[left], arr[pivotIndex]) // put the pivot value (@pivotIndex) at the start of the array
                                     // i.e. arr[left] is now the pivot value

    int up = left + 1, down = right - 1;
    do {
        while(arr[up] <= arr[left] && up < right) up++;
        while(arr[down] >= arr[left] && down > left) down--; 

        if(up < down) { SWAP(arr[up], arr[down]) }
    } while(up < down);

    SWAP(arr[left], arr[down])

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

    if(arr != NULL) delete [] arr;

    arr = new int[capacity];
    QS::capacity = capacity;

    // std::cout << "capacity: " << capacity << std::endl;

    return true;
}

void QS::clear(){
    delete [] arr;
    arr = NULL;
    size = 0;
    capacity = 0;
}