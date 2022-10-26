#include "regression.h"

Data regression::read_database(std::string filepath){
    try {
        Data my_data;
        std::ifstream ifile(filepath);
        if (ifile){
            size_t counter{0};
            for (std::string line; getline(ifile, line); ){
                std::string delimiter{","};
                size_t pos{0};
                std::string token;
                line.append(",");
                my_data.push_back(std::vector<double>{});
                my_data[counter].push_back(1);
                while((pos = line.find(delimiter)) != std::string::npos){
                    token = line.substr(0, pos);
                    my_data[counter].push_back(stod(token));
                    line.erase(0, pos + delimiter.length());
                }
                counter++;
            }
            return my_data;
        }
        else{
            throw std::runtime_error("Wrong filename ! try again");
        }
    }    
    
    catch(std::runtime_error e){
        Data my_data;
        throw std::runtime_error("Wrong filename ! try again");
        return my_data;
    }
}


double regression::hypothesis(std::vector<double> theta, std::vector<double> x){
    if (theta.size() == x.size()){
        double output_hyp{0};
        for (size_t i{0}; i < theta.size(); i++){
            output_hyp += theta[i] * x[i];
        }
        return output_hyp;
    }
    else{
        throw std::logic_error("this is a logic Error stating that size of x and theta not equal.");
    }
}


double regression::cost_function(Data dataset, std::vector<double> theta){
    double cost{0};
    for (int i{0}; i < dataset.size() ; i++)
    {
        std::vector<double> temp_vector;
        for (size_t j{0}; j + 1 < dataset[i].size(); j++){
            temp_vector.push_back(dataset[i][j]);
        }
        cost = cost + pow((hypothesis(theta, temp_vector) - dataset[i][4]), 2);
        temp_vector.clear();
    }
    return (cost/2);
}


std::vector<double> regression::update(Data dataset, std::vector<double> theta, double lr){
    for (int i{0}; i < dataset.size(); i++)
    {
        for (int j{0}; j + 1 < dataset[i].size(); j++)
        {
            std::vector<double> temp_vector;
            for (size_t j{0}; j + 1 < dataset[i].size(); j++){
                temp_vector.push_back(dataset[i][j]);
            }
            theta[j] = theta[j] - lr * (hypothesis(theta, temp_vector) - dataset[i][4]) * dataset[i][j];
            temp_vector.clear();
        }
    }
    return theta;
}


std::vector<double> regression::linear_regression(Data dataset, std::vector<double> init_theta, double lr){

    std::vector<double> theta;
    theta = update(dataset, init_theta, lr);
    for (size_t i{1}; i <= 10000; i++){
        std::vector<double> temp_theta = theta;
        theta = update(dataset, theta, lr);
        if (i > 9900)
            std::cout << i << "  ->  cost:  " << cost_function(dataset,theta) <<
                     "      - " << "reduced cost:" <<cost_function(dataset,temp_theta) - cost_function(dataset,theta) <<  std::endl;
    }
    return theta;
}   