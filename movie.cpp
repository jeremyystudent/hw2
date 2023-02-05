#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating):Product(category, name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie(){
}

std::string Movie::getGenre() const{return genre_;}
std::string Movie::getRating() const{return rating_;}

std::set<std::string> Movie::keywords() const{
    return parseStringToWords(genre_);

}
std::string Movie::displayString() const{
    stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();

}
void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}
