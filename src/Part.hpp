#ifndef PART_HPP
#define PART_HPP

// an Object is made up by any number of these
class Part
{
public:
    virtual ~Part() = 0;

private:
    Part() = default;
};

#endif

