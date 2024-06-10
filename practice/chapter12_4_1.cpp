#include <cmath>
#include "chapter12_4.h"

namespace SPHERICAL_COOR
{
    Spherical::Spherical()
    {
        radial_distance = polar_angle = azimuthal_angle = 0;
    }
    
    Spherical::Spherical(double r, double theta, double phi)
    {
        radial_distance = r;
        theta = std::remainder(theta, M_PI);
        if (theta < 0)
            theta += M_PI;
        polar_angle = theta;
        phi = std::remainder(phi, M_PI * 2.0);
        if (phi < 0)
            phi += M_PI;
        azimuthal_angle = phi;
    }

    Spherical::~Spherical()
    {

    }

    void Spherical::show_coor() const
    {
        std::cout << "(" << radial_distance << ", " << polar_angle << ", " << azimuthal_angle << ")" << std::endl;
    }

    void Spherical::convert_to_cartesian() const
    {
        std::cout << "(" << radial_distance * sin(polar_angle) * cos(azimuthal_angle) 
                  << ", " << radial_distance * sin(polar_angle) * sin(azimuthal_angle)
                  << ", " << radial_distance * cos(polar_angle) << ")" << std::endl;
    }

    Spherical Spherical::operator+(const Spherical & s) const
    {
        double x1 = radial_distance * sin(polar_angle) * cos(azimuthal_angle);
        double y1 = radial_distance * sin(polar_angle) * sin(azimuthal_angle);
        double z1 = radial_distance * cos(polar_angle);
        double x2 = s.radial_distance * sin(s.polar_angle) * cos(s.azimuthal_angle);
        double y2 = s.radial_distance * sin(s.polar_angle) * sin(s.azimuthal_angle);
        double z2 = s.radial_distance * cos(s.polar_angle);

        double x = x1 + x2; double y = y1 + y2; double z = z1 + z2;
        double r = sqrt(x * x + y * y + z * z);
        double theta = acos(z / r);
        double phi = atan(y / x);

        return Spherical(r, theta, phi);
    }

    Spherical Spherical::operator-(const Spherical & s) const
    {
        return *this + s.operator-();
    }

    Spherical Spherical::operator-() const
    {
        return Spherical(-radial_distance, polar_angle, azimuthal_angle);
    }

    double Spherical::operator*(const Spherical & s) const
    {
        return (radial_distance * sin(polar_angle) * cos(azimuthal_angle)) * (s.radial_distance * sin(s.polar_angle) * cos(s.azimuthal_angle)) + 
        (radial_distance * sin(polar_angle) * sin(azimuthal_angle)) * (s.radial_distance * sin(s.polar_angle) * sin(s.azimuthal_angle)) + 
        (radial_distance * cos(polar_angle)) * (s.radial_distance * cos(s.polar_angle));
    }

    Spherical Spherical::operator*(double n) const
    {
        return Spherical(radial_distance * n, polar_angle, azimuthal_angle);
    }

    Spherical operator*(double n, const Spherical & s)
    {
        return s * n;
    }

    std::ostream & operator<<(std::ostream & os, const Spherical & s)
    {
        os << "(" << s.radial_distance << ", " << s.polar_angle << ", " << s.azimuthal_angle << ")";
        return os;
    }

    std::istream & operator>>(std::istream & is, Spherical & s)
    {
        double r, theta, phi;
        is >> r >> theta >> phi;
        theta = std::remainder(theta, M_PI);
        if (theta < 0)
            theta += M_PI;
        phi = std::remainder(phi, 2.0 * M_PI);
        if (phi < 0)
            phi += M_PI;
        s = Spherical(r, theta, phi);
        return is;
    }
};
