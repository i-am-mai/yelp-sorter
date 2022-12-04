#include "YelpDataset.h"

int main() {
    YelpDataset data;

    data.sortTimer(2, 1, false); 
    //synatx:
    //first slot: 1 = mergesort, 2 = quicksort
    //second slot: 1 = stars, 2 = ratings, 3 = distance
    //third: "is descending": false = ordered logically, highest stars, rating, lowest distance | true = illogically, lowest stars and ratings, highest distance

    int yeah; //this is just to make it so i could type without closing the window
    std::cin >> yeah;
}
