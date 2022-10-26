#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <math.h>

using Data = std::vector<std::vector<double>>;

namespace regression{
    
    Data read_database(std::string filepath);

    double hypothesis(std::vector<double> theta, std::vector<double> x);

    double cost_function(Data dataset, std::vector<double> theta);

    std::vector<double> update(Data dataset, std::vector<double> theta, double lr);
    
    std::vector<double> linear_regression(Data dataset, std::vector<double> init_theta, double lr);
}
