#ifndef CONSTEXPR_FUNC_MULTIFILE_H
#define CONSTEXPR_FUNC_MULTIFILE_H

/*
If you need to use a constexpr function in multiple .cpp files, 
you can define it in a header file and use it in multiple files without an ODR violation, 
as constexpr functions are implicitly inline. However, it's important to define them 
in one place and before the point of use, similar to inline functions. Alternatively, 
you can provide only a forward declaration in the header and define the function in 
a .cpp file, but this makes it a regular runtime function, losing the compile-time advantages of constexpr.
*/

constexpr double mult(double x, double y)
{
    return x * y;
}

#endif
