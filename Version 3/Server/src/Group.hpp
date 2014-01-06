/* 
 * File:   Group.hpp
 * Author: darkey
 *
 * Created on 6 janvier 2014, 09:27
 */

#ifndef GROUP_HPP
#define	GROUP_HPP

class Group {
public:
    Group();
    Group(const Group& orig);
    virtual ~Group();
private:
    int number;
};

#endif	/* GROUP_HPP */

