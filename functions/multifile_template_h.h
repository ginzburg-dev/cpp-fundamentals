#ifndef MULTIFILE_TEMPLATE_H
#define MULTIFILE_TEMPLATE_H

/*
And functions implicitly instantiated from function templates are implicitly inline, 
so they can be defined in multiple files, so long as each definition is identical.
The templates themselves are not inline, as the concept of inline only applies to 
variables and functions.
*/

template <typename T, typename U>
auto max(T x, U y)
{
    return ( x > y ) ? x : y;
}

#endif
