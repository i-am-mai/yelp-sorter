#include "YelpDataset.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "../lib/json.hpp"

using json = nlohmann::json;

YelpDataset::YelpDataset(double userLat, double userLng) {
    this->userLat = userLat;
    this->userLng = userLng;
    loadData(data);
}

// Loads a YelpBusiness vector with data from the yelp_academic_dataset_business.json file
void YelpDataset::loadData(std::vector<YelpBusiness>& data) {
    std::ifstream file("../assets/yelp_academic_dataset_business.json");
    std::string temp;
    while (getline(file, temp)) {
        json j = json::parse(temp);

        YelpBusiness business;

        // Add data about the business to the YelpBusiness object.
        business.businessID = j["business_id"];
        business.name = j["name"];
        business.address = j["address"];
        business.city = j["city"];
        business.state = j["state"];
        business.postalCode = j["postal_code"];
        business.latitude = j["latitude"];
        business.longitude = j["longitude"];
        business.stars = j["stars"];
        business.reviewCount = j["review_count"];
        business.isOpen = j["is_open"] == 1 ? true : false;
        business.makeRating(business.stars, business.reviewCount);
        business.calculateDistance(userLat, userLng); 

        for (json::iterator it = j["attributes"].begin(); it != j["attributes"].end(); it++) {
            business.attributes[(std::string)it.key()] = (std::string)it.value();
        }

        // Try-catch block is necessary in case the business has no categories.
        try {
            std::istringstream temp((std::string)j["categories"]);
            std::string category;
            while (getline(temp, category, ',')) {
                if (category[0] == ' ') {
                    category = category.substr(1);
                }
                business.categories.push_back(category);
            }
        }
        catch (...) {
        }
        // Adds hours to the business and properly formats them.
        for (json::iterator it = j["hours"].begin(); it != j["hours"].end(); it++) {
            std::string hour = (std::string)it.value();
            std::size_t found = hour.find('-');
            if (found != std::string::npos) {
                std::string openTime = hour.substr(0, found);
                std::string closeTime = hour.substr(found + 1);
                if (openTime.substr(openTime.find(':')).length() < 3) {
                    openTime = openTime + "0";
                }
                if (closeTime.substr(closeTime.find(':')).length() < 3) {
                    closeTime = closeTime + "0";
                }
                hour = openTime + "-" + closeTime;
            }
            business.hours[(std::string)it.key()] = hour;
        }
        data.push_back(business);
    }
}

// Implements merge for merge sort.
void YelpDataset::merge(std::vector<YelpBusiness>& vec, int low, int mid, int high, int sortKind, bool descending) {

    std::vector<YelpBusiness> temp;

    int templow = low;
    int tempmid = mid + 1;

    int mult = 1;
    if (!descending) {
        mult = -1;
    }

    if (sortKind == 1) {        // Sorts by stars
        while (templow < mid + 1 && tempmid < high + 1) {

            if (vec[templow].stars * mult <= vec[tempmid].stars * mult) {
                temp.push_back(vec[templow]);
                templow++;
            }
            else {
                temp.push_back(vec[tempmid]);
                tempmid++;
            }
        }
    }
    else if (sortKind == 2) {   // Sorts by rating
        while (templow < mid + 1 && tempmid < high + 1) {

            if (vec[templow].rating * mult <= vec[tempmid].rating * mult) {
                temp.push_back(vec[templow]);
                templow++;
            }
            else {
                temp.push_back(vec[tempmid]);
                tempmid++;
            }
        }
    }
    else if (sortKind == 3) {   // Sorts by distance
        while (templow < mid + 1 && tempmid < high + 1) {

            if (vec[templow].distance * -mult <= vec[tempmid].distance * -mult) {
                temp.push_back(vec[templow]);
                templow++;
            }
            else {
                temp.push_back(vec[tempmid]);
                tempmid++;
            }
        }
    }

    // Adds the remaining items to the merged list
    for (int i = templow; i < mid + 1; i++) {
        temp.push_back(vec[i]);
    }

    for (int i = tempmid; i < high + 1; i++) {
        temp.push_back(vec[i]);
    }

    // Adds the merged list to the original vector
    for (int i = low; i < high + 1; i++) {
        vec[i] = temp[i - low];
    }

}

// Driver function for merge sort
void YelpDataset::mergeSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending) {
    if (low < high) {

        int mid = (low + high) / 2;

        mergeSort(vec, low, mid, sortKind, descending);
        mergeSort(vec, mid + 1, high, sortKind, descending);

        merge(vec, low, mid, high, sortKind, descending);
    }
}

// Calls merge sort and returns the sorted data
std::vector<YelpBusiness> YelpDataset::mergeSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending) {
    mergeSort(vec, 0, vec.size() - 1, sortKind, descending);

    return vec;
}

// Implements partition for quick sort, returning a pivot index.
int YelpDataset::partition(std::vector<YelpBusiness>& vec, int low, int high, double piv, int sortKind, bool descending) {
    int up = low;
    int down = high;
    int mult = 1;
    while (up < down) {
        for (int j = up; j < high; j++) {
            double comparator;
            if (!descending) {
                mult = -1;
            }
            if (sortKind == 1) {
                comparator = vec[j].stars;
            }
            else if (sortKind == 2) {
                comparator = vec[j].rating;
            }
            else if (sortKind == 3) {
                comparator = vec[j].distance * -1;
            }
            if (comparator * mult > piv * mult) {
                break;
            }
            up++;
        }
        for (int j = down; j > low; j--) {
            double comparator;
            if (!descending) {
                mult = -1;
            }
            if (sortKind == 1) {
                comparator = vec[j].stars;
            }
            else if (sortKind == 2) {
                comparator = vec[j].rating;
            }
            else if (sortKind == 3) {
                comparator = vec[j].distance * -1;
            }
            if (comparator * mult < piv * mult) {
                break;
            }
            down--;
        }
        if (up < down) {
            YelpBusiness temp = vec[up];
            vec[up] = vec[down];
            vec[down] = temp;
        }
    }
    YelpBusiness temp = vec[low];
    vec[low] = vec[down];
    vec[down] = vec[low];
    return down;
}

// Driver for the quicksort algorithm
void YelpDataset::quickSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending) {
    while (low < high) {
        double piv;
        if (sortKind == 1) {
            piv = vec[low].stars;
        }
        else if (sortKind == 2) {
            piv = vec[low].rating;
        }
        else if (sortKind == 3) {
            piv = vec[low].distance * -1;
        }

        int pos = partition(vec, low, high, piv, sortKind, descending);
        
        // Stack overflow workaround
        // https://stackoverflow.com/questions/33884057/quick-sort-stackoverflow-error-for-large-arrays
        if (pos - low <= high - (pos + 1)) {
            quickSort(vec, low, pos - 1, sortKind, descending);
            low = pos + 1;
        }
        else {
            quickSort(vec, pos + 1, high, sortKind, descending);
            high = pos;
        }

    }
}

// Calls the quicksort function and returns the sorted data.
std::vector<YelpBusiness> YelpDataset::quickSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending) {
    quickSort(vec, 0, vec.size() - 1, sortKind, descending);

    return vec;
}

// Calls each respective sorting function, times it, then returns the sorted data.
std::vector<YelpBusiness> YelpDataset::sortTimer(int type, int sortKind, bool descending) {
    auto initialTime = std::chrono::steady_clock::now();
    std::vector<YelpBusiness> returnVec;

    if (type == 1) {
        returnVec = mergeSortCaller(data, sortKind, false);
    }
    else if (type == 2) {
        returnVec = quickSortCaller(data, sortKind, false);
    }
    auto finalTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = std::chrono::duration_cast<std::chrono::duration<double>>(finalTime - initialTime);
    std::cout << "<>----< Sort Duration: " << dur.count() << " s >----<>\n";

    return returnVec;
}
