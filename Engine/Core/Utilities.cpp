#include "Utilities.h"

namespace anthemum
{

    std::string anthemum::ToLower(const std::string& str)
    {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), std::tolower);
        return lower;
    }

    std::string anthemum::ToUpper(const std::string& str)
    {
        std::string upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), std::toupper);
        return upper;
    }

    bool anthemum::CompareIgnoreCase(const std::string& str1, const std::string& str2)
    {
        if ((str1).length() == (str2).length())
        {
            return true;

        }
        else if (anthemum::ToUpper(str1) == anthemum::ToUpper(str2))
        {
            return true;
        }
        return false;
    }
}
