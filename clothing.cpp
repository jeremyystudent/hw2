#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand):Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing(){
}

std::string Clothing::getSize() const{return size_;}
std::string Clothing::getBrand() const{return brand_;}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> result = parseStringToWords(name_);
    std::set<std::string> brand = parseStringToWords(brand_);
    result = setUnion<std::string>(result, brand);
    return result;
}
std::string Clothing::displayString() const{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}
void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
