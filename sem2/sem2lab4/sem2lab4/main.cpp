#include "main.hpp"


int main(){
    {
        List testing;
        testing.push_back(Circle{Point{2,3}, 4});
        std::cout << testing << '\n';
        testing.push_back(Circle{Point{4,-8}, 10});
        std::cout << testing << '\n';
        testing.push_front(Circle{Point{2,3}, 4});
        std::cout << testing << '\n';
        testing.push_back(Circle{Point{8,3}, 20});
        std::cout << testing << '\n';
        //testing[0] = Circle{Point{23,33}, 123};
        testing.sortByInc();
        std::cout << testing << '\n';
        testing.sortByDec();
        std::cout << testing << '\n';
        iterator_list tm = testing.end();
        std::cout << testing << '\n';
        testing.insert(tm, Circle{Point{8,3}, 21});
        std::cout << testing << '\n';
        std::fstream file;
        file.open("/Users/timofejovcinnikov/Desktop/Учеба/xcode-labs/sem2lab4/sem2lab4/Text.txt");
        
        file << testing;
        
        file.close();
        List nwtesting;
        
        file.open("/Users/timofejovcinnikov/Desktop/Учеба/xcode-labs/sem2lab4/sem2lab4/Text.txt");
        file >> nwtesting;
        
        
        std::cout << "\nNwTst\n\n" << nwtesting;
        file.close();
    }
    return 0;
}
