#include <iostream>
#include <string_view>
#include <cstdarg> // for ellipsis

int func_elipsis_int(int count, ...)
{
    int sum{0};

    std::va_list list;

    va_start(list, count);

    for (int index{0}; index < count; ++index)
    {
        sum += va_arg(list, int);
    }

    va_end(list);

    return sum;
}

double func_elipsis_average_int_sentinel(int first, ...)
{
    int sum{ first };

    std::va_list list;

    va_start(list, first);

    int count{1};

    while (true)
    {
        int arg { va_arg(list, int) };

        if ( arg == -1 )
            break;

        sum += arg;
        ++count;
    }

    va_end(list);

    return static_cast<double>(sum) / count;
}

void func_elipsis_print(std::string_view decoder, ...)
{

    std::va_list list;

    va_start(list, decoder);

    int count{1};
    for ( auto code : decoder )
    {
        switch (code)
        {
        case 'i': 
            std::cout << "arg " << count << '=' << va_arg(list, int) << '\n';
            break;
        case 'd': 
            std::cout << "arg " << count << '=' << va_arg(list, double) << '\n';
            break;
        default:
            std::cout << "Unknown arg.\n";
        }
        ++count;
    }

    va_end(list);
}


int main()
{
    std::cout << "#1 The sum of ellipsis args is: " << func_elipsis_int(5, 1, 2, 3, 4, 5) << '\n';
    func_elipsis_print("iiiddd", 1, 2, 3, 1.2, 3.4, 5.6);
    std::cout << "#2 The average of ellipsis args is: " << func_elipsis_average_int_sentinel(5, 1, 2, 3, 4, 5, 20, 2, -1) << '\n';
    return 0;
}
