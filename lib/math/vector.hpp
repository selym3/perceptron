#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <array> // std::array, std::size_t
#include <cmath> // std::sqrt

#define __VECTOR_IS_PRINTABLE__

#ifdef __VECTOR_IS_PRINTABLE__
#include <ostream>
#endif

template <
    std::size_t Dimensions,
    typename TypeType = double,
    typename BufferType = std::array<TypeType, Dimensions>
>
struct Vector
{

    // TYPEDEFS

    using Buffer = BufferType;
    using Type = TypeType;

    // CONSTRUCTORS

    Vector(const Buffer& buffer) :
        buffer { buffer }
    {
    }

    Vector(const Type& filler)
    {
        buffer.fill(filler);
    }

    Vector() :
        Vector(0)
    {
    }

    // OPERATIONS

    Vector& operator+=(const Vector& other)
    {
        for (int i = 0; i < size(); ++i)
            buffer[i] += other[i];
        
        return *this;
    }

    friend Vector operator+(Vector lhs, const Vector& rhs)
    {
        return lhs += rhs;
    }

    Vector& operator-=(const Vector& other)
    {
        for (int i = 0; i < size(); ++i)
            buffer[i] -= other[i];
        
        return *this;
    }

    friend Vector operator-(Vector lhs, const Vector& rhs)
    {
        return lhs -= rhs;
    }

    Vector& operator*=(const Vector& other)
    {
        for (int i = 0; i < size(); ++i)
            buffer[i] *= other[i];
        
        return *this;
    }

    friend Vector operator*(Vector lhs, const Vector& rhs)
    {
        return lhs *= rhs;
    }

    Vector& operator/=(const Vector& other)
    {
        for (int i = 0; i < size(); ++i)
            buffer[i] /= other[i];
        
        return *this;
    }

    friend Vector operator/(Vector lhs, const Vector& rhs)
    {
        return lhs /= rhs;
    }

    Type dot(const Vector& other) const
    {
        Type dot {};
        for (int i = 0; i < size(); ++i)
            dot += (buffer[i] * other.buffer[i]);

        return dot;
    }

    Type length() const
    {
        return std::sqrt((*this).dot(*this));
    }

    Type distance(const Vector& other) const
    {
        Vector difference = (*this) - other;
        Type dSquared = difference.dot(difference);
        return std::sqrt(dSquared);
    }

    // GETTERS

    std::size_t size() const
    {
        return Dimensions;
    }

    // ITERATOR OVERLOADS

    typename Buffer::iterator begin() 
    { 
        return buffer.begin(); 
    }
   
    typename Buffer::const_iterator begin() const 
    { 
        return buffer.begin(); 
    }

    typename Buffer::iterator end() 
    { 
        return buffer.end(); 
    }
   
    typename Buffer::const_iterator end() const 
    { 
        return buffer.end(); 
    }

    // SUBSCRIPT OVERLOADS

    const Type& operator[](std::size_t index) const
    {
        return buffer[index];
    }

    Type& operator[](std::size_t index) 
    {
        return buffer[index];
    }

    const Type& at(std::size_t index) const 
    { 
        buffer.at(index); 
    }
    
    Type& at(std::size_t index) 
    { 
        return buffer.at(index); 
    }


    // OSTREAM OVERLOADS

#ifdef __VECTOR_IS_PRINTABLE__
    
    friend std::ostream& operator<<(std::ostream& os, const Vector& vector)
    {
        os << "[ ";

        // print all the elements
        auto i = 0;
        for (; i < vector.size() - 1; ++i)
            os << vector[i] << ", ";
        os << vector[i];

        os << " ]";
        return os;
    }

#endif

private:

    // DATA

    Buffer buffer;

};

#endif