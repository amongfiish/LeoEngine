#ifndef PART_TRANSFORM_HPP
#define PART_TRANSFORM_HPP

#include "LeoEngine/Part.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class PartTransform : public Part
    {
    public:
        PartTransform();
        virtual ~PartTransform();

        const Pair<double, double>& getPosition() const;

        void setPosition(double x, double y);
        void setPosition(const Pair<double, double>& position);

        void move(double deltaX, double deltaY);
        void move(const Pair<double, double>& delta);

    private:
        Pair<double, double> _position;
    };

}

#endif
