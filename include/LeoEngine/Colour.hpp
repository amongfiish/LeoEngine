#ifndef COLOUR_HPP
#define COLOUR_HPP

namespace LeoEngine
{

    class Colour
    {
    public:
        Colour(int red, int green, int blue, int alpha)
            : red(red),
            green(green),
            blue(blue),
            alpha(alpha)
        {
        }

        int red, green, blue, alpha;
    };

}

#endif

