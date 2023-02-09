#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
#include "product.h"

using namespace std;

MyDataStore::~MyDataStore(){ 
    std::set<Product*>::iterator it;
    for(it = myProducts.begin();it != myProducts.end();it++){
        delete (*it);
    }
    std::set<User*>::iterator it2;
    for(it2 = myUsers.begin();it2 != myUsers.end();it2++){
        delete (*it2);
    }
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
            keywordMap.insert(std::make_pair(*it, temp));
        }
    }
}

void MyDataStore::addUser(User* u){
    myUsers.insert(u);
    std::set<Product*> temp;
    myInventory.insert(std::make_pair(u, temp));
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
    for(it2 = myUsers.begin();it2 != myUsers.end();++it2){
        (*it2)->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::putToCart(User* usr, Product* item){
    std::map<User*, std::set<Product*>>::iterator it;
    it = myInventory.find(usr);
    it->second.insert(item);
}
void MyDataStore::buyCart(User* usr){
    std::map<User*, std::set<Product*>>::iterator it;
    it = myInventory.find(usr);
    std::set<Product*>::iterator it2;
    for(it2 = it->second.begin();it2 != it->second.end();){
        double price = (*it2)->getPrice();
        int qty = (*it2)->getQty();
        if(price <= usr->getBalance() && qty >= 1){
            usr->deductAmount(price);
            (*it2)->subtractQty(1);
            it->second.erase(it2++);
        }else{
            ++it2;
        }
    }
}
std::set<Product*> MyDataStore::getCart(User* usr){
    std::map<User*, std::set<Product*>>::iterator it;
    it = myInventory.find(usr);
    std::set<Product*> cart = it->second;
    return cart;
}
User* MyDataStore::findUsr(string username){
    std::set<User*>::iterator it;
    for(it = myUsers.begin(); it != myUsers.end();++it){
        if((*it)->getName() == username){return *it;}
    }
    return NULL;
}