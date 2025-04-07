#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <functional>

bool containsHey(std::string_view str)
{
    return str.find("Hey") != std::string_view::npos;
}

bool greater(int a, int b)
{
    return ( a > b ); // reverse order ( descend ) 
}

void doubleNumber(int& i)
{
    i *= 2;
}

int main()
{
    std::array array { 1, 2, 3, 4 };

    // std::find

    int search {3};
    int replace {4};

    auto found { std::find(array.begin(), array.end(), search) };

    if ( found == array.end() )
    {
        std::cout << "Could not found " << search << '\n';
    } 
    else
    {
        *found = replace;
    }

    for ( auto i : array )
        std::cout << i << ' ';
    std::cout << '\n';
    
    // std::find_if

    std::array<std::string_view, 6> words { "go", "not", "rain", "Ho", "Heya", "Hey" };

    auto found_if { std::find_if(words.begin(), words.end(), containsHey ) };

    if ( found_if == words.end() )
    {
        std::cout << "No Hey.\n";
    } 
    else
    {
        std::cout << "Found Hey in the " << found_if - words.begin() << "th string.\n";
    }

    // std::count or std::count_if

    auto heyCount { std::count_if(words.begin(), words.end(), containsHey ) };
    std::cout << "Counted " << heyCount << '\n';

    // std::sort()

    std::array arrayToSort { 1, 2, 3, 4, 5 };

    //std::sort(arrayToSort.begin(), arrayToSort.end(), greater );
    std::sort(arrayToSort.begin(), arrayToSort.end(), std::greater{} ); // instantiate std::greater{} from <functional> to descend order

    for ( auto i : arrayToSort )
        std::cout << i << ' ';
    std::cout << '\n';

    // std::for_each

    std::array arrayForEach { 1, 2, 3, 4, 5 };

    std::for_each(arrayForEach.begin(), arrayForEach.end(), doubleNumber); // Do smth with each element

    for ( auto i : arrayForEach )
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
