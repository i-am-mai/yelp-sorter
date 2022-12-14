#include "YelpBusiness.h"

class YelpDataset {
private:
    std::vector<YelpBusiness> data;
    
    double userLat;
    double userLng;
    
    void loadData(std::vector<YelpBusiness>& data);

    void merge(std::vector<YelpBusiness>& vec, int low, int mid, int high, int sortKind, bool descending);
    void mergeSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending);

    int partition(std::vector<YelpBusiness>& vec, int low, int high, double piv, int sortKind, bool descending);
    void quickSort(std::vector<YelpBusiness>& vec, int low, int high, int sortKind, bool descending);

public:
    YelpDataset(double userLat, double userLng);
    std::vector<YelpBusiness> sortTimer(int type, int sortKind, bool descending);
    std::vector<YelpBusiness> quickSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending);
    std::vector<YelpBusiness> mergeSortCaller(std::vector<YelpBusiness> vec, int sortKind, bool descending);

};
