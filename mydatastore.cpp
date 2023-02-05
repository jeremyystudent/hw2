#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
#include "product.h"

using namespace std;

MyDataStore::~MyDataStore(){ 
    myProducts.clear();
    myUsers.clear();
    keywordMap.clear();
}

void MyDataStore::addProduct(Product* p){
    myProducts.insert(p);
    std::set<std::string> keywords = p->keywords();
    std::set<std::string>::iterator it;
    for(it = keywords.begin();it != keywords.end();++it){
        std::map<std::string, std::set<Product*>>::iterator it2;
        it2 = keywordMap.find(*it);
        if(it2 != keywordMap.end()){
            it2->second.insert(p);
        }else{
            std::set<Product*> temp;
            temp.insert(p);
            keywordMap.insert(std::make_pair(it2->first, temp));
        }
    }
}

void MyDataStore::addUser(User* u){
    myUsers.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    if(type == 0){
        std::vector<std::string>::iterator it;
        std::set<Product*> result = myProducts;
        for(it = terms.begin();it != terms.end();++it){
            std::map<std::string, std::set<Product*>>::iterator it2;
            it2 = keywordMap.find(*it);
            if(it2 != keywordMap.end()){
                result = setIntersection<Product*>(result, it2->second);
            }else{
                return std::vector<Product*>();
            }
        }
        return std::vector<Product*>(result.begin(), result.end());
    }else{
        std::vector<std::string>::iterator it;
        std::set<Product*> result;
        for(it = terms.begin();it != terms.end();++it){
            std::map<std::string, std::set<Product*>>::iterator it2;
            it2 = keywordMap.find(*it);
            if(it2 != keywordMap.end()){
                result = setUnion<Product*>(result, it2->second);
            }
        }
        return std::vector<Product*>(result.begin(), result.end());
        
    }
}

void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << "\n";
    typename std::set<Product*>::iterator it;
    for(it = myProducts.begin();it != myProducts.end();++it){
        (*it)->dump(ofile);
    }
    ofile << "</products>" << "\n";
    ofile << "<users>" << "\n";
    typename std::set<User*>::iterator it2;
    for(it2 = myUsers.begin();it2 != myUsers.end();++it){
        (*it)->dump(ofile);
    }
    ofile << "</users>" << endl;
}
