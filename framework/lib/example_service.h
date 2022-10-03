#pragma once

#include "interface/example.h"

namespace hidoki {
    struct example_service : public example {
        void something() final;
        static example_service* make();
    };
}
