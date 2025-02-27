#ifndef PART_PHYSICS_HPP
#define PART_PHYSICS_HPP

#include <memory>
#include "LeoEngine/Part.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/PartTransform.hpp"

namespace LeoEngine
{

    class PartPhysics : public Part
    {
    public:
        PartPhysics();
        virtual ~PartPhysics();

        void setTarget(std::shared_ptr<PartTransform> target);

        void setVelocity(double x, double y);
        void setVelocity(const Pair<double, double> &velocity);

        const Pair<double, double> &getVelocity();

        void setAcceleration(double x, double y);
        void setAcceleration(const Pair<double, double> &velocity);

        const Pair<double, double> &getAcceleration();

        bool isInMotion();

        virtual void update() override;

        virtual void reset() override;

    private:
        std::shared_ptr<PartTransform> _target;

        Pair<double, double> _velocity;
        Pair<double, double> _acceleration;
    };

}

#endif
