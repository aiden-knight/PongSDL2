struct Vector2
{
  float x;
  float y;
  
  Vector2& operator + (float d)
  {
    x+=d;
    y+=d;
    return *this;
  } 
  Vector2 operator - (float d) const {return Vector2{x-d, y-d};}
};