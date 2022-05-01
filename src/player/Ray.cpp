#include "Ray.h"

void Ray::Advance(float amount) {
    position += direction * amount;  
}
