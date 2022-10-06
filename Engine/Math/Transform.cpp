#include "Transform.h"

bool anthemum::Transform::Write(const rapidjson::Value& value) const
{
    return true;
}

bool anthemum::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);
    READ_DATA(value, rotation);

    return true;
}
