#include <map>
#include <iostream>
#include <string>

// std::map can be a great object to access values by key.

int main()
{
    std::map<int, std::string> students{ { 1, "John" }, { 2, "Ann" } };
    students.insert( { 3, "Huan" } ); // Inserting element
    students[4] = "Yaffo"; // Inserting element

    std::cout << students[1] << " " << students[2] << " " << students[3] << " " << students[4] << '\n';

    // Traverse std::map version 1
    for ( const auto& i : students )
        std::cout << i.second << ' ';
    std::cout << '\n';

    // Traverse std::map version 1
    for ( auto it = students.begin(); it != students.end(); ++it )
        std::cout << it->second << ' ';
    std::cout << '\n';

    std::map<int, std::map<int, std::string>> nested_map{};
    nested_map[1][1] = "one";
    std::cout << nested_map[1][1] << '\n';

    // std::multimap allows adding multiple values for the same keys
    std::multimap<int, std::string> multimap{ { 1, "John" }, { 1, "Huan" }, { 2, "Ann" }}; 
    auto range = multimap.equal_range(1); // return pair of iterators
    for( auto it = range.first; it != range.second; ++it )
        std::cout << it->second << ' ';
    std::cout << '\n';

    return 0;
}
