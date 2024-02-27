#ifndef SPHERICAL_COOR_H_
#define SPHERICAL_COOR_H_
#include <iostream>

namespace SPHERICAL_COOR
{
    class Spherical
    {
        private:
            double radial_distance;
            double polar_angle;
            double azimuthal_angle;

        public:
            Spherical();
            Spherical(double r, double theta, double phi);
            ~Spherical();
            void show_coor() const;
            void convert_to_cartesian() const;
            double show_radial_distance() { return radial_distance; }
            double show_polar_angle() { return polar_angle; }
            double show_azimuthal_angle() { return azimuthal_angle; }

            Spherical operator+(const Spherical & s) const;
            Spherical operator-(const Spherical & s) const;
            Spherical operator-() const;
            Spherical operator*(double n) const;
            double operator*(const Spherical & s) const;

            friend Spherical operator*(double n, const Spherical & s);
            friend std::ostream & operator<<(std::ostream & os, const Spherical & s);
            friend std::istream & operator>>(std::istream & is, Spherical & s);
    };
};



#endif