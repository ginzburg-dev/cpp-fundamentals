#ifndef TEMPLATE_CLASSES_H_INL
#define TEMPLATE_CLASSES_H_INL

template<typename T>
void TemplateClass<T>::inlMethod() const
{
    std::cout << "Inl method.\n";
}

#endif
