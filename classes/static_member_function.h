#ifndef STATIC_MEMBER_FUNCTION_H
#define STATIC_MEMBER_FUNCTION_H

class SimpleHeader
{
private:
    static inline int s_id { 1 };

public:
    static int getNextID();
};

inline int SimpleHeader::getNextID() { return s_id++; } // must be inline to avoid violating the ODR

#endif
