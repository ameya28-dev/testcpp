#include <iostream>
#include <unordered_map>

using std::cout, std::unordered_map, std::swap, std::string;

int main()
{
    unordered_map<string, double> umap = {{"one", 1}, {"Two", 2}, {"Three", 3}};

    umap["GeeksForGeeks"] = 10;
    umap["GeeksForGeeks"] = 20;
    umap["Contribute"] = 30;

    umap["PI"] = 3.14;
    umap["root2"] = 1.414;
    umap["root3"] = 1.732;
    umap["log10"] = 2.302;
    umap["roote"] = 1.0;

    umap.insert(std::make_pair("e", 2.718));

    cout << umap.at("GeeksForGeeks") << '\n';
    cout << (umap.find("kaafi") == umap.end()) << '\n';

    string key = "PI";
    if(umap.find(key) != umap.end()){
        cout << umap.at(key) << '\n';
    }
    else{
        cout << "Not found" << '\n';
    }

    key = "erasmus";
    if(umap.find(key) != umap.end()){
        cout << umap.at(key) << '\n';
    }
    else{
        cout << "Not found" << '\n';
    }

    cout << "Show all elements" << '\n';
    unordered_map<string, double>::iterator ptr;
    for(ptr = umap.begin(); ptr != umap.end(); ptr++){
        cout << ptr->first << '\t' << ptr->second << '\n';
    } 

    return 0;
}