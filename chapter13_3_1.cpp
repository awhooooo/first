#include <string>
#include <new>
#include "chapter13_3.h"
#include <iostream>
#include <cmath>


namespace POLAR_COOR
{
    Polar2::Polar2(double r, double theta)
    {
        this->distance = r;
        theta = std::remainder(theta, M_PI * 2);
        if (theta < 0)
            theta += M_PI;
        this->angle = theta;
    }

    Polar2::Polar2(const Polar2 & p2)
    {
        this->distance = p2.distance;
        this->angle = p2.angle;
    }

    Polar3::Polar3(double r, double theta, double z): Polar2(r, theta)
    {
        this->z = z;
    }

    Polar3::Polar3(const Polar2 & p2, double z) :Polar2(p2)
    {
        this->z = z;
    }

    void Polar3::view_coor() const
    {
        std::cout << "(" << this->get_radial()
                  << ", " << this->get_theta()
                  << ", " << z << ")" << std::endl;
    }

    void Polar3::view_cartesian_coor() const
    {
        std::cout << "(" << this->get_radial() * cos(this->get_theta())
                  << ", " << this->get_radial() * sin(this->get_theta())
                  << ", " << z << ")" << std::endl;
    }

    Polar3 & Polar3::operator=(const Polar3 & p3)
    {
        if (this != &p3) // Check for self-assignment
        {
            this->set_radial(p3.get_radial());
            this->set_theta(p3.get_theta());
            this->z = p3.z;
        }
        return *this;
    }

    Polar4::Polar4(double r, double theta, std::string script_type, const char * encoding): Polar2(r, theta)
    {
        this->script_type = script_type;
        // delete [] this->encoding;
        this->encoding = new char[std::strlen(encoding) + 1];
        std::strcpy(this->encoding, encoding);
    }

    Polar4::Polar4(const Polar2 & p2, std::string script_type, const char * encoding): Polar2(p2)
    {
        this->script_type = script_type;
        // delete [] this->encoding;
        this->encoding = new char[std::strlen(encoding) + 1];
        std::strcpy(this->encoding, encoding);
    }

    void Polar4::view_coor() const
    {
        std::cout << "r = " << this->get_radial() 
                  << "\ntheta = "<< this->get_theta() 
                  << "\nscript type = " << script_type 
                  << "\nencoding = " << encoding << std::endl;
    }

    Polar4 & Polar4::operator=(const Polar4 & p4)
    {
        delete [] this->encoding;
        if (this != &p4)
        {
            this->set_radial(p4.get_radial());
            this->set_theta(p4.get_theta());
            this->script_type = p4.script_type;
            this->encoding = new char[std::strlen(p4.encoding) + 1];
            std::strcpy(this->encoding, p4.encoding);
        }
        return *this;
    }

    Polar4::~Polar4()
    {
        delete [] encoding;
    }
};
