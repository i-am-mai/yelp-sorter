#include "YelpBusiness.h"

class YelpDataset {
private:
    //std::vector<YelpBusiness> data;
    //void loadData(std::vector<YelpBusiness>& data);

    double ufLat = 29.64833;
    double ufLng = -82.34944;
    double userLat;
    double userLng;

    void loadData(std::vector<YelpBusiness>& data, int lat, int lng);

    void merge(std::vector<YelpBusiness>& vec, int low, int mid, int high, int sortKind, bool descending);
    void mergeSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending);

    int partition(std::vector<YelpBusiness>& vec, int low, int high, double piv, int sortKind, bool descending);
    void quickSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending);

    std::vector<YelpBusiness> data;

public:
    YelpDataset();
    YelpDataset(int userLat, int userLng);
    void sortTimer(int type, int sortKind, bool descending);
    std::vector<YelpBusiness> quickSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending);
    std::vector<YelpBusiness> mergeSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending);

};
