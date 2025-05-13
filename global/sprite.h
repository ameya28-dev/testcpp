#include <cstdint>
namespace Genesis {

struct Sprite {
    uint32_t X = 0, Y = 0;
};

static Sprite sprite;

namespace Sprites {
inline Sprite Grass{2, 7};
}

}  // namespace Genesis