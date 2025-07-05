/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MVector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasr <nasr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:11:12 by nasr              #+#    #+#             */
/*   Updated: 2025/07/05 22:08:14 by nasr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MVECTOR_HPP
#define MVECTOR_HPP
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
template <typename T> 
class MVector
{
private:
    size_t _size;
    T *_vec;
public:
    MVector(int size = 0, T def = 0){
        _vec = new T[size];
        _size = size;
        for (size_t i = 0; i < _size; i++)
        {
            _vec[i] = def;
        }
        
    };
    size_t size() const {
        return _size;
    };
    MVector(MVector<T> const &M){
        delete[] _vec;
        _size = M.size();
        _size = size;
        for (size_t i = 0; i < _size; i++)
        {
            _vec[i] = M[i];
        }
    };
    T &operator[](size_t  index){
        if ( index >= _size)
            throw std::out_of_range("Index out of range");
        return _vec[index];
    };
    const T &operator[](size_t  index) const{
        if ( index >= _size)
            throw std::out_of_range("Index out of range");
        return _vec[index];
    };
    T operator*(MVector<T> const &M) const
    {
        if (_size != M.size())
            throw "deferent veector size";
        T res = 0;
        for (size_t i = 0; i < _size; i++)
        {
            res += _vec[i] * M[i];
        }
        return res;
    };
    MVector<T> &operator+(MVector<T> const &M) const 
    {
        if  (_size != M.size())
            throw "deferent veector size";
        MVector res(_size);
        for (size_t i = 0; i < _size; i++)
        {
            res[i] = _vec[i] + M[i];
        }
        return res;
    };
    MVector<T> operator-(MVector<T> const &M) const 
    {
        if  (_size != M.size())
            throw "deferent veector size";
        MVector res(_size);
        for (size_t i = 0; i < _size; i++)
        {
            res[i] = _vec[i] + M[i];
        }
        return res;
    };
    ~MVector(){
        delete[] _vec; 
    };
};
template <typename T> 
std::ostream& operator<<(std::ostream& os, const MVector<T>& obj) {
    for (size_t i = 0; i < obj.size(); i++)
    {
        if (i > 0)
            os << ',';
        os << obj[i];
    }
    return os;
};

#endif
