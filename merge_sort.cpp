#include <vector>

void merge_sort(std::vector<int>::iterator& begin, std::vector<int>::iterator& end){
    if(begin > end) return;

    std::addressof(begin);
    
    // merge_sort(begin, begin + (end-begin)/2);
}

int main(){
    std::vector<int> v {10,9,3,5,60,1,56};

    return 0;
}