#include "template_classes_h.h"
#include <iostream>

int main()
{
    int length{ 10 };
    TemplateClass<int> intArray{ length };

    for (int i = 0; i < length; ++i)
        intArray[i] = i + 1;

    for (const auto& e : intArray)
        std::cout << e << '\n';

    nonTemplateFunction();
    
    intArray.inlMethod();

    return 0;
}
