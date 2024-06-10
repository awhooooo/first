#ifndef POLAR_COOR_H_
#define POLAR_COOR_H_
#include <string>

namespace POLAR_COOR
{
    class Polar2
    {
        private:
            double distance;
            double angle;
        protected:
            const double get_radial() const { return distance; }
            const double get_theta() const { return angle; }
        public:
            virtual void set_radial(double r) { distance = r; }
            virtual void set_theta(double theta) { angle = theta; }
            Polar2(double r = 0, double theta = 0);
            Polar2(const Polar2 & p2);
            virtual ~Polar2() {};
            virtual void view_coor() const = 0;
    };

    class Polar3 :public Polar2
    {
        private:
            double z;
        public:
            Polar3(double r = 0, double theta = 0, double z = 0);
            Polar3(const Polar2 & p2, double z);
            Polar3 & operator=(const Polar3 & p3);
            virtual ~Polar3() {};
            virtual void view_coor() const;
            void view_cartesian_coor() const;
    };

    class Polar4 :public Polar2
    {
        private:
            std::string script_type;
            char * encoding;
        public:
            Polar4(double r = 0, double theta = 0, std::string script_type = "Legacy", const char * encoding = "base58");
            Polar4(const Polar2 & p2, std::string script_type, const char * encoding);
            Polar4 & operator=(const Polar4 & p4);
            virtual ~Polar4();
            virtual void view_coor() const;

    };
};

#endif
