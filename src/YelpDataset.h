#include "YelpBusiness.h"

class YelpDataset {
private:
    std::vector<YelpBusiness> data;
    void loadData(std::vector<YelpBusiness>& data);
    
public:
    YelpDataset();
};