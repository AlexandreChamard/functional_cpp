
#pragma once

namespace fun {

template<class T>
class storage {
    char data[sizeof(T)];

public:

    T const *ptr_ref() const {
        union { void const* ap_pvoid; T const* as_ptype; } caster = { data };
        return caster.as_ptype;
    }
    T *ptr_ref() {
        union { void * ap_pvoid; T * as_ptype; } caster = { data };
        return caster.as_ptype;
    }

    T const &ref() const { return *ptr_ref(); }
    T       &ref()       { return *ptr_ref(); }
};

}