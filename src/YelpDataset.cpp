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

/* Takes in a reference to a YelpBusiness vector and loads it with
 * data from the yelp_academic_dataset_business.json file
 */

void YelpDataset::loadData(std::vector<YelpBusiness>& data) {
    std::ifstream file("../assets/yelp_dataset2.json");
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
        business.calculateDistance(userLat, userLng); //did this here because I thought it would be easier

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
        // business.print();
        data.push_back(business);
    }
}

void YelpDataset::merge(std::vector<YelpBusiness>& vec, int low, int mid, int high, int sortKind, bool descending) {

    std::vector<YelpBusiness> temp;

    int templow = low;
    int tempmid = mid + 1;

    int mult = 1;
    if (!descending) {
        mult = -1;
    }

    if (sortKind == 1) { //stars
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
    else if (sortKind == 2) { //rating
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
    else if (sortKind == 3) { //distance
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

    for (int i = templow; i < mid + 1; i++) {
        temp.push_back(vec[i]);
    }

    for (int i = tempmid; i < high + 1; i++) {
        temp.push_back(vec[i]);
    }

    for (int i = low; i < high + 1; i++) {
        vec[i] = temp[i - low];
    }

}

void YelpDataset::mergeSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending) {
    if (low < high) {

        int mid = (low + high) / 2;

        mergeSort(vec, low, mid, sortKind, descending);
        mergeSort(vec, mid + 1, high, sortKind, descending);

        merge(vec, low, mid, high, sortKind, descending);
    }
}

std::vector<YelpBusiness> YelpDataset::mergeSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending) {
    mergeSort(vec, 0, vec.size() - 1, sortKind, descending);

    return vec;
}

int YelpDataset::partition(std::vector<YelpBusiness>& vec, int low, int high, double piv, int sortKind, bool descending) {
    int templow = low;
    int pos = low;
    for (int i = low; i < high + 1; i++) {
        double comparator;
        int mult = 1;
        if (!descending) {
            mult = -1;
        }
        if (sortKind == 1) {
            comparator = vec[i].stars;
        }
        else if (sortKind == 2) {
            comparator = vec[i].rating;
        }
        else if (sortKind == 3) {
            comparator = vec[i].distance * -1;
        }
        if (!(comparator * mult > piv * mult)) {
            YelpBusiness temp = vec[i];
            vec[i] = vec[pos];
            vec[pos] = temp;
            pos++;
        }
    }
    return pos - 1;
}

void YelpDataset::quickSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending) {
    if (low < high) {
        double piv;
        if (sortKind == 1) {
            piv = vec[high].stars;
        }
        else if (sortKind == 2) {
            piv = vec[high].rating;
        }
        else if (sortKind == 3) {
            piv = vec[high].distance * -1;
        }

        //double piv = vec[high].stars;
        int pos = partition(vec, low, high, piv, sortKind, descending);

        quickSort(vec, low, pos - 1, sortKind, descending);
        quickSort(vec, pos + 1, high, sortKind, descending);
    }
}

std::vector<YelpBusiness> YelpDataset::quickSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending) {
    quickSort(vec, 0, vec.size() - 1, sortKind, descending);

    return vec;
}

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
