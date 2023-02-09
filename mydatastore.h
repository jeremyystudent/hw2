#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include "product.h"
#include <map>

class MyDataStore : public DataStore{
public:
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void putToCart(User* usr, Product* item);
    void buyCart(User* usr);
    std::vector<Product*> getCart(User* usr);
    User* findUsr(std::string username);

private:
    std::set<Product*> myProducts;
    std::set<User*> myUsers;
    std::map<std::string, std::set<Product*>> keywordMap;
    std::map<User*, std::vector<Product*>> myInventory;
};

#endif
